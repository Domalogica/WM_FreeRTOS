#include "stdint.h"

typedef struct Osmosis{
  uint32_t permeate;
  uint32_t ultra;
  uint32_t _permeate;
  uint32_t _ultra;
  uint32_t step;
  uint32_t len;
  uint8_t source;
  uint8_t old_source;
} Osmosis;

//main function osmosis control
void osmosis_mdg(Osmosis *osmosis);

//callback for calc input
void callback_osmosis(Osmosis *osmosis);

//output for valve ultra
uint8_t valve_ultra(Osmosis *osmosis);
//output for valve permiate
uint8_t valve_permiate(Osmosis *osmosis);
