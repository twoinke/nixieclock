#include <stdint.h>
#include <Arduino.h>
#include "NixieMultiplexer.h"

NixieMultiplexer::NixieMultiplexer()
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
  enabled = true;
}

NixieMultiplexer::~NixieMultiplexer()
{

}

void NixieMultiplexer::setEnabled(bool e)
{
  enabled = e;
}

void IRAM_ATTR NixieMultiplexer::writeByte(int8_t b)
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

void IRAM_ATTR NixieMultiplexer::updateNixies()
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


int8_t IRAM_ATTR NixieMultiplexer::dec_to_bcd(int8_t dec)
{
  int8_t result=0;
  
  result |= (dec / 10) << 4;
  result |= (dec % 10) << 0;
  
  return result;
}

void IRAM_ATTR NixieMultiplexer::setNixieTube(int8_t tube_nr, int8_t bcdval)
{
  // translation table to fix mixup of nixie pins on PCB
  static int8_t trans[] = { 1,0,9,8,7,6,5,4,3,2 };
  
  tubes[tube_nr] = ((1 << tube_nr) << 4) | trans[bcdval];
}


void IRAM_ATTR NixieMultiplexer::setTime(uint8_t hour, uint8_t min)
{
  uint8_t tmp;

  tmp = dec_to_bcd(min);
  setNixieTube(3, 0x0f & tmp);
  setNixieTube(2, (tmp >> 4));


  tmp = dec_to_bcd(hour);
  setNixieTube(1, 0x0f & tmp);
  setNixieTube(0, (tmp >> 4));
}