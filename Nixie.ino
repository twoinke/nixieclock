
#include <FS.h> //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h> 

#include <WiFiManager.h> 
#include <ElegantOTA.h>

#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"
#include <ESP8266_ISR_Timer.hpp>               //https://github.com/khoih-prog/ESP8266TimerInterrupt

#include <time.h>
#include <coredecls.h> // optional settimeofday_cb() callback to check on server

// default config values
#define MY_HOSTNAME   "nixieclock"
#define MY_NTP_SERVER "de.pool.ntp.org"  
#define MY_TZ         "CET-1CEST,M3.5.0/02,M10.5.0/03"  


// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#define HW_TIMER_INTERVAL_MS         5L
#define TIMER_INTERVAL_1S            1000L

struct configStruct {
  char hostname[32];
  char ntp_server[32];
  char timezone[32];
};

struct configStruct config;

time_t now;
tm tm;
int8_t tubes[4];
bool blink = false;
bool enabled = true;

// Init ESP8266 timer 1
ESP8266Timer ITimer;

// Init ESP8266_ISR_Timer
ESP8266_ISR_Timer ISR_Timer;

WiFiManager wifiManager;

ESP8266WebServer server(80);


void time_is_set(bool from_sntp /* <= this optional parameter can be used with ESP8266 Core 3.0.0*/) {
  Serial.print(F("time was sent! from_sntp=")); Serial.println(from_sntp);
}

uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 ()
{
  return 24 * 60 * 60 * 1000UL; // 24 hours
}

int8_t IRAM_ATTR dec_to_bcd(int8_t dec)
{
  int8_t result;
  
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

  
  if (! enabled)
  {
    return;
  }

  ISR_Timer.run();

  if (tube == 0) tube = 4;

  writeByte(tubes[--tube]);
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

  if (blink)
  {
    digitalWrite(D8, !digitalRead(D8)); 
  }
 
/*
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
*/
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
 
  //Serial.printf("[%02x:%02x:%02x:%02x]\n", tubes[0], tubes[1], tubes[2], tubes[3]);
}

//flag for saving data
bool shouldSaveConfig = false;

unsigned long ota_progress_millis = 0;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
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
  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, updateNixies);
  // ISR_Timer.setInterval(HW_TIMER_INTERVAL_MS * 1000, updateNixies);
  digitalWrite(D8, 0); // LEDs
  writeByte(0);
  setNixieTube(0, 1);
  

  wifiManager.setSaveConfigCallback(saveConfigCallback);

  strncpy(config.ntp_server, MY_NTP_SERVER, 32);
  strncpy(config.hostname, MY_HOSTNAME, 32);
  strncpy(config.timezone, MY_TZ, 32);

  Serial.begin(115200);
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.bin")) 
    {
      //file exists, reading and loading
      Serial.println("reading config file");
      /*
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strncpy(config.ntp_server, json["n"], 32);
          strncpy(config.hostname, json["h"], 32);
          strncpy(config.timezone, json["t"], 32);
        } else {
          Serial.println("failed to load json config");
        }
      }
      */


      File binaryConfigFile = SPIFFS.open("/config.bin", "r");
      if (binaryConfigFile)
      {
        binaryConfigFile.read((byte*) &config ,sizeof(config));
        binaryConfigFile.close();

        Serial.println(config.hostname);
        Serial.println(config.ntp_server);
        Serial.println(config.timezone);  
      }
      else
      {
        Serial.println("Could not open config file");
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read

  writeByte(0);
  setNixieTube(1, 2);



  
  
  WiFiManagerParameter custom_hostname("hostname", "Hostname", config.hostname, 32);
  WiFiManagerParameter custom_ntp_server("ntp_server", "NTP Server", config.ntp_server, 32);
  WiFiManagerParameter custom_timezone("timezone", "Time Zone", config.timezone, 32);
  

  wifiManager.addParameter(&custom_hostname);
  wifiManager.addParameter(&custom_ntp_server);
  wifiManager.addParameter(&custom_timezone);
  
 


  Serial.print("\n\nNixie NTP Clock\n\n");
  Serial.print("\n\n2018-2024 Thomas Woinke\n\n");
  
  writeByte(0);
  setNixieTube(2, 3);

  
  Serial.printf("Connecting to Wifi..");

  wifiManager.autoConnect("NixieConfigAP");
  
  strncpy(config.hostname,    custom_hostname.getValue(), 32); 
  strncpy(config.ntp_server,  custom_ntp_server.getValue(), 32);
  strncpy(config.timezone,    custom_timezone.getValue(), 32);

  

   //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    
  /*

    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["n"] = config.ntp_server;
    json["h"] = config.hostname;
    json["t"] = config.timezone;
    
    

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
  */
    
    File binaryConfigFile = SPIFFS.open("/config.bin", "w");
    if (binaryConfigFile) 
    {
      binaryConfigFile.write((byte*) &config ,sizeof(config));
      binaryConfigFile.close();
    }
    else
    {
      Serial.println("failed to open config file for writing");
    }

    //end save
  }

  writeByte(0);
  setNixieTube(3, 4);

  WiFi.hostname(config.hostname);

  settimeofday_cb(time_is_set); // optional: callback if time was sent
  configTime(config.timezone, config.ntp_server); // --> Here is the IMPORTANT ONE LINER needed in your sketch!

  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());


  if (!MDNS.begin(config.hostname))
  {
    Serial.println("Error setting up mDNS responder");  
  }
  
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, getTime);
  // ISR_Timer.run();
  

  

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/blink/", handleBlink);
  server.on("/off/", handleOff);
  server.on("/on/", handleOn);
  server.on("/reset/", handleReset);
  
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  ElegantOTA.onStart([]() 
  {
    Serial.println("ElegantOTA update process started.");
    // OTA will fail with HW timers enabled
    ISR_Timer.disableAll();
    digitalWrite(D8, 1); // LEDs
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
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started"); 
}

void loop(void)
{
  server.handleClient();                    // Listen for HTTP requests from clients
  ElegantOTA.loop();
}


void handleRoot() 
{
  String header;
  String body;
  String footer;
  String resp;
  time(&now);
  localtime_r(&now, &tm);
  char time[11];


  sprintf(time, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
  
  header = "<html><head><title>Nixieclock</title></head><body>";
  body   = "<body><h1>Nixieclock OTA</h1>";
  body  += "<p>Hostname:" + String(config.hostname) + "</p>";
  body  += "<p>The time is:" + String(time) + "</p>";
  body  += "<p><a href=\"/on/\">on</a>|<a href=\"/off/\">off</a>|<a href=\"/blink/\">blink</a></p>";
  body  += "<p><a href=\"/update\">update</a></p>";
  
  footer = "</body></html>";

  resp = header + body + footer;
  server.send(200, "text/html", resp);   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleBlink()
{
  blink = !blink;
  digitalWrite(D8, 0); // LEDs
  server.sendHeader("Location","/");
  server.send(303);  
}

void handleOff()
{
  enabled = 0;
  digitalWrite(D8, 0); // LEDs
  writeByte(0);
  server.sendHeader("Location","/");
  server.send(303);  
}

void handleOn()
{
  enabled = 1;
  server.sendHeader("Location","/");
  server.send(303);  
}

void handleReset()
{
  wifiManager.resetSettings();
  ESP.restart();
  server.sendHeader("Location","/");
  server.send(303); 
}


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
