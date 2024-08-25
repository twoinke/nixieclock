
#ifndef NIXIEMULTIPLEX_H
#define NIXIEMULTIPLEX_H

class NixieMultiplexer
{
public:
  NixieMultiplexer();
  ~NixieMultiplexer();
  void IRAM_ATTR updateNixies();
  void setNixieTube(int8_t tube_nr, int8_t bcdval);

  void setEnabled(bool);
  bool getEnabled();
  void IRAM_ATTR writeByte(int8_t);
  void setTime(uint8_t hour, uint8_t min);



protected:
  volatile uint8_t tubes[4];
  bool enabled;

  int8_t dec_to_bcd(int8_t dec);

};


#endif //NIXIEMULTIPLEX_H