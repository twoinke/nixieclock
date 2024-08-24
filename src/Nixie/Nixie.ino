
#include <FS.h>

#define UPDATE_HOST "api.github.com"
#define UPDATE_URL "/repos/twoinke/nixieclock/releases/latest"




#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h> 
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h> 
#include <WiFiClientSecure.h>
// #include <ESP8266HTTPUpdateServer.h>
#include <ElegantOTA.h>

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"
#include <ESP8266_ISR_Timer.hpp>               //https://github.com/khoih-prog/ESP8266TimerInterrupt

#include <time.h>
#include <coredecls.h> // optional settimeofday_cb() callback to check on server

#include "NixieMultiplexer.h"
#include "GithubOTA.h"


// config filename

#define CONFIGFILE                   "/config.bin"

// default config values
#define MY_HOSTNAME                  "nixieclock"
#define MY_NTP_SERVER                "de.pool.ntp.org"  
#define MY_TZ                        "CET-1CEST,M3.5.0/02,M10.5.0/03"  
#define RELEASE_TAG                  "v00"  

#define HRS_12 43200000UL // 12 * 60 * 60 * 1000UL; 12 hours



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

"  <p><form action=\"/api\" method=\"post\">"
"  <fieldset><legend>Check for update on startup</legend>"
"  <input type=\"radio\" name=\"update_startup\" value=\"0\" /><label>no</label>"
"  <input type=\"radio\" name=\"update_startup\" value=\"1\" checked /><label>yes</label>"
"  <input type=\"submit\" value=\"Send\" />"
"  </fieldset>"
"  </form></p>"

"  <p><form action=\"api\" method=\"post\" onSubmit=\"return confirm('Sicher?');\" ><fieldset><legend>Update</legend>"
"  <input type=\"submit\" value=\"Update\"/>"
"  <input type=\"hidden\" name=\"update\" value=\"1\" />"
"  </fieldset>"
"  </form></p>"

"  <p><a href=\"/update\">update</a></p>"

"  <p><form action=\"api\" method=\"post\" onSubmit=\"return confirm('Sicher? WLAN Zugangsdaten werden gel&ouml;scht!');\" ><fieldset><legend>Reset</legend>"
"  <input type=\"submit\" value=\"Reset\"/>"
"  <input type=\"hidden\" name=\"reset\" value=\"1\" />"
"  </fieldset>"
"  </form></p>"
"</body></html>";


String updateURL = "";

struct configStruct {
  char hostname[32];
  char ntp_server[32];
  char timezone[32];
  char release_tag[4];
  bool enabled;
  uint8_t led_mode;
  bool update_startup;
};

struct configStruct config;

time_t now;
tm tm;

NixieMultiplexer mux;


// Init ESP8266 timer 1
ESP8266Timer ITimer;

// Init ESP8266_ISR_Timer
ESP8266_ISR_Timer ISR_Timer;

WiFiManager wifiManager;

ESP8266WebServer server(WEBSERVER_PORT);
// ESP8266HTTPUpdateServer httpUpdater;


#ifdef DEBUG
void time_is_set(bool from_sntp /* <= this optional parameter can be used with ESP8266 Core 3.0.0*/) {
  Serial.print(F("time was sent! from_sntp=")); Serial.println(from_sntp);
}
#endif


uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 ()
{
  return HRS_12; 
}

void IRAM_ATTR TimerHandler()
{
  ISR_Timer.run();
  
  mux.updateNixies();
}

void IRAM_ATTR getTime()
{ 
  static int8_t cnt = 0;
  
  time(&now);
  localtime_r(&now, &tm);

  if (config.led_mode == LEDS_BLINK)
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
    mux.setNixieTube(3, cnt);
    mux.setNixieTube(2, cnt);
    mux.setNixieTube(1, cnt);
    mux.setNixieTube(0, cnt);

    cnt++;
    if (cnt == 10)
    {
      cnt = 0;
    }
    return;
  }
  
  mux.setTime((uint8_t)tm.tm_hour, (uint8_t)tm.tm_min);


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
  
  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler);
  

  mux.writeByte(0);
  mux.setNixieTube(0, 1);
  
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // init config struct with default values
  strncpy(config.ntp_server, MY_NTP_SERVER, 32);
  strncpy(config.hostname, MY_HOSTNAME, 32);
  strncpy(config.timezone, MY_TZ, 32);
  strncpy(config.release_tag, RELEASE_TAG, 4);
  config.led_mode = LEDS_ON;
  config.enabled = true;
  config.update_startup = false;
  

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
    Serial.printf("Config loaded:\nHostname: %s\nNTP Server: %s\nTimezone: %s\nRelease: %s\n", 
      config.hostname, 
      config.ntp_server, 
      config.timezone,
      config.release_tag);
  }
  else
  {
    Serial.println("failed to mount FS. Attempting to format.");
    SPIFFS.format();
    Serial.println("format done.");

    saveConfig(CONFIGFILE);

  }

  if (config.led_mode == LEDS_ON)
  {
    digitalWrite(D8, true); // LEDs
  }

  mux.writeByte(0);
  mux.setNixieTube(1, 2);

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
  
  mux.writeByte(0);
  mux.setNixieTube(2, 3);


   //save the custom parameters to FS
  if (shouldSaveConfig) 
  {
    Serial.println("saving config");
    if (! saveConfig(CONFIGFILE))
    {
      Serial.println("Error saving config");
    }    
  }
  
  if (config.update_startup)
  {
    Serial.println("checking for online update");

    handleGithubUpdate();
  }
  
  mux.writeByte(0);
  mux.setNixieTube(3, 4);

  WiFi.hostname(config.hostname);

#ifdef DEBUG
  settimeofday_cb(time_is_set); // optional: callback if time was sent
#endif
  configTime(config.timezone, config.ntp_server); // --> Here is the IMPORTANT ONE LINER needed in your sketch!

  if (!MDNS.begin(config.hostname))
  {
    Serial.println("Error setting up mDNS responder");  
  }
  
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, getTime);

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/api", handleAPI);
  
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"


  ESPhttpUpdate.onStart(beginOTAUpdate);
  ElegantOTA.onStart(beginOTAUpdate);

  ElegantOTA.onProgress(onOTAProgress);
  ESPhttpUpdate.onProgress(onOTAProgress);

  ElegantOTA.onEnd(onOTAEnd);
  ESPhttpUpdate.onEnd(onOTAEnd2);

  ElegantOTA.begin(&server);

  // httpUpdater.setup(&server);
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started"); 



}



void updateFromGithub() 
{
  
}




void beginOTAUpdate()
{
  Serial.println("update process started.");
  // OTA will fail with HW timers enabled
  ISR_Timer.disableAll();
  Serial.println("HW timers disabled.");

  mux.writeByte(0);
  pinMode(D0, INPUT);  
  pinMode(D1, INPUT);  
  pinMode(D2, INPUT);  
  pinMode(D3, INPUT);  
  pinMode(D4, INPUT);  
  pinMode(D5, INPUT);  
  pinMode(D6, INPUT);  
  pinMode(D7, INPUT);  
  pinMode(D8, INPUT); 
}

void onOTAProgress(size_t current, size_t final)
{
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void onOTAEnd2()
{
  onOTAEnd(true);
}
void onOTAEnd(bool success)
{
  // Log when OTA has finished
  if (success) {
    Serial.println("OTA update finished successfully!");
    return;
  } 

  Serial.println("There was an error during OTA update!");
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
    config.led_mode = server.arg("led_mode").toInt();
    if (config.led_mode == LEDS_OFF || config.led_mode == LEDS_ON || config.led_mode == LEDS_BLINK)
    {
      if (config.led_mode > 0)
      {
        digitalWrite(D8, true); // LEDs
      }
      else
      {
        digitalWrite(D8, false); // LEDs
      }

      Serial.printf("LEDs: %d\n", config.led_mode);
      saveConfig(CONFIGFILE);
    }   

  }
  else if(server.hasArg("enabled"))
  {
    tmp = server.arg("enabled").toInt();

    if (tmp == 0)
    {
      config.enabled = false;
      mux.writeByte(0);
      Serial.printf("Enabled: %d\n", config.enabled);
    }
    else
    {
      config.enabled = 1;
      Serial.printf("Enabled: %d\n", config.enabled);
    }
    mux.setEnabled(config.enabled);
    saveConfig(CONFIGFILE);

  }
  else if(server.hasArg("update_startup"))
  {
    tmp = server.arg("update_startup").toInt();

    if (tmp == 0)
    {
      config.update_startup = false;
      Serial.printf("Enabled: %d\n", config.update_startup);
    }
    else
    {
      config.update_startup = true;
      Serial.printf("Enabled: %d\n", config.update_startup);
    }

    saveConfig(CONFIGFILE);

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
    handleGithubUpdate();
  }

  server.sendHeader("Location","/");
  server.send(303);  
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
void handleGithubUpdate()
{
  GithubOTA gh_updater(UPDATE_HOST, UPDATE_URL);

  if (! gh_updater.checkUpdate(config.release_tag))
  {
    server.send(404, "text/plain", "No Update found");
    return;
  }

  if (gh_updater.doUpdate())
  {
    strncpy(config.release_tag, gh_updater.release_tag.c_str(), 4);

    if (! saveConfig(CONFIGFILE))
    {
      Serial.println("Error saving config");
      return;
    }  
    Serial.println("config saved. Restarting.. ");

    ESP.restart();
  }
}
