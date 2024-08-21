
#include <FS.h>

#define UPDATE_URL "https://api.github.com/repos/twoinke/nixieclock/releases/latest"
#define UPDATE_BINFILE "Nixie.ino.bin"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h> 
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h> 
#include <WiFiClientSecure.h>

#include <ElegantOTA.h>
#include <ArduinoJson.h>

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"
#include <ESP8266_ISR_Timer.hpp>               //https://github.com/khoih-prog/ESP8266TimerInterrupt

#include <time.h>
#include <coredecls.h> // optional settimeofday_cb() callback to check on server


// config filename

#define CONFIGFILE                   "/config.bin"

// default config values
#define MY_HOSTNAME                  "nixieclock"
#define MY_NTP_SERVER                "de.pool.ntp.org"  
#define MY_TZ                        "CET-1CEST,M3.5.0/02,M10.5.0/03"  
#define RELEASE_TAG                  "v00"  


#define SERIAL_BAUDRATE              115200
#define WEBSERVER_PORT               80

#define HW_TIMER_INTERVAL_US         500L
#define TIMER_INTERVAL_1S            1000L

#define LEDS_OFF    0
#define LEDS_ON     1
#define LEDS_BLINK  2

const char homepage[] PROGMEM = 
"<html><head><title>Nixieclock</title></head><body>"
"  <body><h1>Nixieclock</h1>"
"  <p><form action=\"/api\" method=\"post\">"
"  <fieldset><legend>Nixies</legend>"
"  <input type=\"radio\" name=\"enabled\" value=\"1\" checked /><label>On</label>"
"  <input type=\"radio\" name=\"enabled\" value=\"0\" /><label>Off</label>"
"  <input type=\"submit\" value=\"Send\" />"
"  </fieldset>"
"  </form></p>"

"  <p><form action=\"/api\" method=\"post\">"
"  <fieldset><legend>LED mode</legend>"
"  <input type=\"radio\" name=\"led_mode\" value=\"0\" /><label>off</label>"
"  <input type=\"radio\" name=\"led_mode\" value=\"1\" checked /><label>on</label>"
"  <input type=\"radio\" name=\"led_mode\" value=\"2\" checked /><label>blink</label>"
"  <input type=\"submit\" value=\"Send\" />"
"  </fieldset>"
"  </form></p>"

"  <p><form action=\"api\" method=\"post\" onSubmit=\"return confirm('Sicher? WLAN Zugangsdaten werden gel&ouml;scht!');\" ><fieldset><legend>Reset</legend>"
"  <input type=\"submit\" value=\"Reset\"/>"
"  <input type=\"hidden\" name=\"reset\" value=\"1\" />"
"  </fieldset>"
"  </form></p>"

"  <p><form action=\"api\" method=\"post\" onSubmit=\"return confirm('Sicher?');\" ><fieldset><legend>Update</legend>"
"  <input type=\"submit\" value=\"Update\"/>"
"  <input type=\"hidden\" name=\"update\" value=\"1\" />"
"  </fieldset>"
"  </form></p>"

"  <p><a href=\"/update\">update</a></p>"
"</body></html>";


String updateURL = "";

struct configStruct {
  char hostname[32];
  char ntp_server[32];
  char timezone[32];
  char release_tag[4];
};

struct configStruct config;

time_t now;
tm tm;
volatile uint8_t tubes[4];

uint8_t led_mode = LEDS_ON;

// bool leds_on = true;
// bool blink = false;
bool enabled = true;
bool update = false;

// Init ESP8266 timer 1
ESP8266Timer ITimer;

// Init ESP8266_ISR_Timer
ESP8266_ISR_Timer ISR_Timer;

WiFiManager wifiManager;

ESP8266WebServer server(WEBSERVER_PORT);


void time_is_set(bool from_sntp /* <= this optional parameter can be used with ESP8266 Core 3.0.0*/) {
  Serial.print(F("time was sent! from_sntp=")); Serial.println(from_sntp);
}

uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 ()
{
  Serial.println("sntp update delay dingens called");
  return 24 * 60 * 60 * 1000UL; // 24 hours
}

int8_t IRAM_ATTR dec_to_bcd(int8_t dec)
{
  int8_t result=0;
  
  result |= (dec / 10) << 4;
  result |= (dec % 10) << 0;
  
  return result;
}

void IRAM_ATTR writeByte(int8_t b)
{
  digitalWrite(D0, bitRead(b, 0));
  digitalWrite(D1, bitRead(b, 1));
  digitalWrite(D2, bitRead(b, 2));
  digitalWrite(D3, bitRead(b, 3));
  digitalWrite(D4, bitRead(b, 4));
  digitalWrite(D5, bitRead(b, 5));
  digitalWrite(D6, bitRead(b, 6));
  digitalWrite(D7, bitRead(b, 7));
}


void IRAM_ATTR updateNixies()
{
  static int8_t tube = 4;
  static bool toggle = true;

  if (! toggle )
  {
    toggle = true;
    writeByte(0);

    return;
  }

  if (! enabled )
  {
    return;
  }

  if (tube == 0) tube = 4;

  writeByte(tubes[--tube]);
  toggle = false;
}

void IRAM_ATTR TimerHandler()
{
  ISR_Timer.run();
  
  updateNixies();
}


void IRAM_ATTR setNixieTube(int8_t tube_nr, int8_t bcdval)
{
  // translation table to fix mixup of nixie pins on PCB
  static int8_t trans[] = { 1,0,9,8,7,6,5,4,3,2 };
  
  tubes[tube_nr] = ((1 << tube_nr) << 4) | trans[bcdval];
}

void IRAM_ATTR getTime()
{ 
  static int8_t cnt = 0;
  static int8_t tmp = 0;
  
  time(&now);
  localtime_r(&now, &tm);

  if (led_mode == LEDS_BLINK)
  {
    digitalWrite(D8, !digitalRead(D8)); 
  }
 
#ifdef DEBUG
  Serial.print("year:");
  Serial.print(tm.tm_year + 1900);  // years since 1900
  Serial.print("\tmonth:");
  Serial.print(tm.tm_mon + 1);      // January = 0 (!)
  Serial.print("\tday:");
  Serial.print(tm.tm_mday);         // day of month
  Serial.print("\thour:");
  Serial.print(tm.tm_hour);         // hours since midnight  0-23
  Serial.print("\tmin:");
  Serial.print(tm.tm_min);          // minutes after the hour  0-59
  Serial.print("\tsec:");
  Serial.print(tm.tm_sec);          // seconds after the minute  0-61*
  Serial.print("\twday");
  Serial.print(tm.tm_wday);         // days since Sunday 0-6
  if (tm.tm_isdst == 1)             // Daylight Saving Time flag
    Serial.print("\tDST");
  else
    Serial.print("\tstandard");
  Serial.println();
#endif

  // screensaver :-)
 
  if (tm.tm_hour == 0 && tm.tm_min >= 0 && tm.tm_min <= 5)
  {
    setNixieTube(3, cnt);
    setNixieTube(2, cnt);
    setNixieTube(1, cnt);
    setNixieTube(0, cnt);

    cnt++;
    if (cnt == 10)
    {
      cnt = 0;
    }
    return;
  }
  
  tmp = dec_to_bcd((int8_t)tm.tm_min);
  setNixieTube(3, 0x0f & tmp);
  setNixieTube(2, (tmp >> 4));


  tmp = dec_to_bcd((int8_t)tm.tm_hour);
  setNixieTube(1, 0x0f & tmp);
  setNixieTube(0, (tmp >> 4));

#ifdef DEBUG
  Serial.printf("[%02x:%02x:%02x:%02x]\n", tubes[0], tubes[1], tubes[2], tubes[3]);
#endif
}

//flag for saving data
bool shouldSaveConfig = false;
unsigned long ota_progress_millis = 0;


//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}



bool loadConfig(const char *filename)
{

  Serial.println("mounted file system");
  
  if (! SPIFFS.exists(filename))
  {
    Serial.println("Config file not found");

    return false; 
  } 
    
 
  File binaryConfigFile = SPIFFS.open(filename, "r");
  if (! binaryConfigFile)
  {
    Serial.println("Could not open config file");
    
    return false;
  }

  binaryConfigFile.read((byte*) &config ,sizeof(config));
  binaryConfigFile.close();

  return true;
}

bool saveConfig(const char * filename)
{   
    File binaryConfigFile = SPIFFS.open(filename, "w");
    if (! binaryConfigFile) 
    {
      Serial.println("Could not open config file for writing");
    
      return false;
    }

    binaryConfigFile.write((byte*) &config ,sizeof(config));
    binaryConfigFile.close();
    
    return true;
}



void setup() 
{   
  pinMode(D0, OUTPUT);  
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  
  pinMode(D5, OUTPUT);  
  pinMode(D6, OUTPUT);  
  pinMode(D7, OUTPUT);  
  pinMode(D8, OUTPUT); 

  writeByte(0);
  
  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler);
  
  if (led_mode == LEDS_ON)
  {
    digitalWrite(D8, true); // LEDs
  }
  writeByte(0);
  setNixieTube(0, 1);
  
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // init config struct with default values
  strncpy(config.ntp_server, MY_NTP_SERVER, 32);
  strncpy(config.hostname, MY_HOSTNAME, 32);
  strncpy(config.timezone, MY_TZ, 32);
  strncpy(config.release_tag, RELEASE_TAG, 4);
  

  Serial.begin(SERIAL_BAUDRATE);

  Serial.println();
  Serial.println("Nixie NTP Clock");
  Serial.println("2018-2024 Thomas Woinke");


  Serial.println("mounting FS...");

  if (SPIFFS.begin())
  {
    if (!loadConfig(CONFIGFILE))
    {
      Serial.println("Error loading config");
    }
    Serial.printf("Config loaded:\nHostname: %s\nNTP Server: %s\nTimezone: %s\n", config.hostname, config.ntp_server, config.timezone);
  }
  else
  {
    Serial.println("failed to mount FS. Attempting to format.");
    SPIFFS.format();
  }

  
  writeByte(0);
  setNixieTube(1, 2);

  WiFiManagerParameter custom_hostname("hostname", "Hostname", config.hostname, 32);
  WiFiManagerParameter custom_ntp_server("ntp_server", "NTP Server", config.ntp_server, 32);
  WiFiManagerParameter custom_timezone("timezone", "Time Zone", config.timezone, 32);  

  wifiManager.addParameter(&custom_hostname);
  wifiManager.addParameter(&custom_ntp_server);
  wifiManager.addParameter(&custom_timezone);
  
 
  Serial.printf("Connecting to Wifi..");

  wifiManager.autoConnect("NixieConfigAP");
  
  strncpy(config.hostname,    custom_hostname.getValue(), 32); 
  strncpy(config.ntp_server,  custom_ntp_server.getValue(), 32);
  strncpy(config.timezone,    custom_timezone.getValue(), 32);
  
  writeByte(0);
  setNixieTube(2, 3);

   //save the custom parameters to FS
  if (shouldSaveConfig) 
  {
    Serial.println("saving config");
    if (! saveConfig(CONFIGFILE))
    {
      Serial.println("Error saving config");
    }    
  }

  writeByte(0);
  setNixieTube(3, 4);


  WiFi.hostname(config.hostname);

  settimeofday_cb(time_is_set); // optional: callback if time was sent
  configTime(config.timezone, config.ntp_server); // --> Here is the IMPORTANT ONE LINER needed in your sketch!

  
  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());


  if (!MDNS.begin(config.hostname))
  {
    Serial.println("Error setting up mDNS responder");  
  }
  
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, getTime);

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/api", handleAPI);
  
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"


  initOTA();

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started"); 
  
}



void updateFromGithub() 
{
  JsonDocument doc;
  WiFiClientSecure client;

  client.setInsecure();
  if (!client.connect("api.github.com", 443)) 
  {
    Serial.println("Connection to api.github.com failed");
    return;
  }
  Serial.println("Connection established");

  client.print(String("GET ") + String(UPDATE_URL) + " HTTP/1.1\r\n" +
    "Host: api.github.com\r\n" +
    "User-Agent: NixieClock_ESP_OTA_GitHubUpdater\r\n" +
    "Connection: close\r\n\r\n");

  
  while (client.connected()) 
  {
    String response = client.readStringUntil('\n');
    if (response == "\r") 
    {
			break;
    }
  }

  String response = client.readStringUntil('\n');

  DeserializationError error = deserializeJson(doc, response);

  if (error)
  {
    Serial.println("Error parsing JSON response");
    return;
  }

  const char* release_tag;

  if (doc.containsKey("tag_name")) 
  {
    release_tag = doc["tag_name"];
    Serial.println(release_tag);
  }

  if (strcmp(release_tag, config.release_tag) != 0 && ! doc["prerelease"]) 
  {
    Serial.println("Update found.");

    JsonArray assets = doc["assets"];
    bool valid_asset = false;
    for (auto asset : assets) 
    {
      const char* asset_type = asset["content_type"];
      const char* asset_name = asset["name"];
      const char* asset_url = asset["browser_download_url"];

      Serial.printf("asset found: Name: [%s], Type: [%s], URL: [%s]\n", asset_name, asset_type, asset_url);

      if (strcmp(asset_type, "raw") == 0 && strcmp(asset_name, UPDATE_BINFILE) == 0) 
      {
        updateURL = asset_url;

        Serial.println("Update URL:" + updateURL);
        strncpy(config.release_tag, release_tag, 4);

        if (! saveConfig(CONFIGFILE))
        {
          Serial.println("Error saving config");
        }  

        return;
      }
    }
}
}

void doUpdate()
{
    ISR_Timer.disableAll();

    writeByte(0);
    pinMode(D0, INPUT);  
    pinMode(D1, INPUT);  
    pinMode(D2, INPUT);  
    pinMode(D3, INPUT);  
    // pinMode(D4, INPUT);  
    pinMode(D5, INPUT);  
    pinMode(D6, INPUT);  
    pinMode(D7, INPUT);  
    pinMode(D8, INPUT); 


    WiFiClientSecure updateClient;
    updateClient.setInsecure();



    // bool mfln = updateClient.probeMaxFragmentLength("objects.githubusercontent.com", 443, 1024);
    // if (mfln) 
    // {
      // updateClient.setBufferSizes(1024, 1024);
    // }

    ESPhttpUpdate.setLedPin(D4, LOW);
    ESPhttpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    Serial.println("Updating from " + updateURL);



    t_httpUpdate_return ret = ESPhttpUpdate.update(updateClient, updateURL);

    switch (ret) 
    {
      case HTTP_UPDATE_FAILED:
          Serial.println("Update Failed: " + ESPhttpUpdate.getLastErrorString());
          strncpy(config.release_tag, RELEASE_TAG, 4);

          if (! saveConfig(CONFIGFILE))
          {
            Serial.println("Error saving config");
          }  
          return;

      case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          return;

      case HTTP_UPDATE_OK:
          Serial.println("Update successful");
          return;
    }
}

void initOTA()
{

  ElegantOTA.onStart([]() 
  {
    Serial.println("ElegantOTA update process started.");
    // OTA will fail with HW timers enabled
    ISR_Timer.disableAll();
   
    writeByte(0);
    pinMode(D0, INPUT);  
    pinMode(D1, INPUT);  
    pinMode(D2, INPUT);  
    pinMode(D3, INPUT);  
    pinMode(D4, INPUT);  
    pinMode(D5, INPUT);  
    pinMode(D6, INPUT);  
    pinMode(D7, INPUT);  
    pinMode(D8, INPUT); 

  });

  ElegantOTA.onProgress([](size_t current, size_t final)
  {
    // Log every 1 second
    if (millis() - ota_progress_millis > 1000) {
      ota_progress_millis = millis();
      Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
    }
  });

  ElegantOTA.onEnd([](bool success)
  {
    // Log when OTA has finished
    if (success) {
      Serial.println("OTA update finished successfully!");
    } else {
      Serial.println("There was an error during OTA update!");
    }
  });

  ElegantOTA.begin(&server);

}
void loop(void)
{
  server.handleClient();                    // Listen for HTTP requests from clients
  ElegantOTA.loop();
}


void handleRoot() 
{  
  server.send(200, "text/html", homepage);   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleAPI()
{
  int tmp;

  if (server.hasArg("led_mode"))
  {
    led_mode = server.arg("led_mode").toInt();
    if (led_mode >= 0 && led_mode <=2)
    {
      if (led_mode > 0)
      {
        digitalWrite(D8, true); // LEDs
      }
      else
      {
        digitalWrite(D8, false); // LEDs
      }

      Serial.printf("LEDs: %d\n", led_mode);
    }   

  }
  else if(server.hasArg("enabled"))
  {
    tmp = server.arg("enabled").toInt();

    if (tmp == 0)
    {
      enabled = 0;
      writeByte(0);
      Serial.printf("Enabled: %d\n", enabled);
    }
    else
    {
      enabled = 1;
      Serial.printf("Enabled: %d\n", enabled);
    }
  }
  else if (server.hasArg("reset"))
  {
    if (server.arg("reset").toInt() == 1)
    {
      ISR_Timer.disableAll();
      wifiManager.resetSettings();
      ESP.restart();
    }
  }
  else if (server.hasArg("update"))
  {
      updateFromGithub();

      if (updateURL.length() > 0)
      {
        doUpdate();
      }

  }

  server.sendHeader("Location","/");
  server.send(303);  
}


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
