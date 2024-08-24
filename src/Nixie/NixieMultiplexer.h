
#ifndef NIXIEMULTIPLEX_H
#define NIXIEMULTIPLEX_H

class NixieMultiplexer
{
public:
  NixieMultiplexer();
  ~NixieMultiplexer();
  void IRAM_ATTR updateNixies();
  void IRAM_ATTR setNixieTube(int8_t tube_nr, int8_t bcdval);

  void SetEnabled(bool);
  int8_t IRAM_ATTR dec_to_bcd(int8_t dec);
  void IRAM_ATTR writeByte(int8_t);

protected:
  volatile uint8_t tubes[4];
  bool enabled;



};


#endif //NIXIEMULTIPLEX_H