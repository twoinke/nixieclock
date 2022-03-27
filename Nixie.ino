
#ifndef STASSID
#define STASSID "Kamar_Taj"
#define STAPSK  "!Shamballa!"
#endif

#include <ESP8266_ISR_Timer.hpp>               //https://github.com/khoih-prog/ESP8266TimerInterrupt

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#include <TimeLib.h>


const char *ssid     = STASSID;
const char *password = STAPSK;

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
//NTPClient timeClient(ntpUDP);

// You can specify the time server pool and the offset, (in seconds)
// additionally you can specify the update interval (in milliseconds).
//NTPClient timeClient(ntpUDP, "de.pool.ntp.org", 3600, 60000);

NTPClient timeClient(ntpUDP, "de.pool.ntp.org", 7200, 60000);

// Init ESP8266 timer 1
ESP8266Timer ITimer;

// Init ESP8266_ISR_Timer
ESP8266_ISR_Timer ISR_Timer;


#define HW_TIMER_INTERVAL_MS         4L
#define TIMER_INTERVAL_1S            1000L

byte tubes[4];

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

  tmp = dec_to_bcd((byte)timeClient.getMinutes());
  tmp2 = 0x0f & tmp;
  tubes[0] = ((1 << 0) << 4) | tmp2;

  tmp2 = (tmp >> 4);
  tubes[1] = ((1 << 1) << 4) | tmp2;

  tmp = dec_to_bcd((byte)timeClient.getHours());
  tmp2 = 0x0f & tmp;
  tubes[2] = ((1 << 2) << 4) | tmp2;

  tmp2 = (tmp >> 4);
  tubes[3] = ((1 << 3) << 4) | tmp2;
  
  
  Serial.printf("[%02x:%02x:%02x:%02x]\n", tubes[0], tubes[1], tubes[2], tubes[3]);
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
  delay(1000);
  Serial.println("Hello World!");
  
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  timeClient.update();

  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler);
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, getTime);
}

void loop() {}
