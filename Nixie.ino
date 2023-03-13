
#ifndef STASSID
#define STASSID "Kamar_Taj"
#define STAPSK  "!Shamballa!"
#endif

/* Configuration of NTP */
#define MY_NTP_SERVER "de.pool.ntp.org"           
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"  

#include <ESP8266_ISR_Timer.hpp>               //https://github.com/khoih-prog/ESP8266TimerInterrupt

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

#include <ESP8266WiFi.h>
#include <time.h>
#include <coredecls.h> // optional settimeofday_cb() callback to check on server

const char *ssid     = STASSID;
const char *password = STAPSK;

time_t now;
tm tm;

// Init ESP8266 timer 1
ESP8266Timer ITimer;

// Init ESP8266_ISR_Timer
ESP8266_ISR_Timer ISR_Timer;


#define HW_TIMER_INTERVAL_MS         2L
#define TIMER_INTERVAL_1S            1000L

byte tubes[4];

void time_is_set(bool from_sntp /* <= this optional parameter can be used with ESP8266 Core 3.0.0*/) {
  Serial.print(F("time was sent! from_sntp=")); Serial.println(from_sntp);
}


uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 ()
{
  return 24 * 60 * 60 * 1000UL; // 24 hours
}


void IRAM_ATTR TimerHandler()
{
  static int8_t tube = 4;

  ISR_Timer.run();

  if (tube == 0) tube = 4;

  writeByte(tubes[--tube]);
}


void getTime()
{ 
  static byte tmp, tmp2;

  time(&now);
  localtime_r(&now, &tm);

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
  
  
  tmp = dec_to_bcd((byte)tm.tm_min);
  tmp2 = 0x0f & tmp;
  tubes[0] = ((1 << 0) << 4) | tmp2;

  tmp2 = (tmp >> 4);
  tubes[1] = ((1 << 1) << 4) | tmp2;

  tmp = dec_to_bcd((byte)tm.tm_hour);
  tmp2 = 0x0f & tmp;
  tubes[2] = ((1 << 2) << 4) | tmp2;

  tmp2 = (tmp >> 4);
  tubes[3] = ((1 << 3) << 4) | tmp2;
  
  
  //Serial.printf("[%02x:%02x:%02x:%02x]\n", tubes[0], tubes[1], tubes[2], tubes[3]);
}
  

byte dec_to_bcd(byte dec)
{
  byte result = 0;
  
  result |= (dec / 10) << 4;
  result |= (dec % 10) << 0;
  
  return result;
}

void writeByte(byte b)
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

  writeByte(0);
 
  Serial.begin(115200);
 // delay(1000);
  Serial.print("Nixie NTP Clock");

  settimeofday_cb(time_is_set); // optional: callback if time was sent
  configTime(MY_TZ, MY_NTP_SERVER); // --> Here is the IMPORTANT ONE LINER needed in your sketch!
  WiFi.hostname("Nixieclock");
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler);
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, getTime);
}

void loop() {}
