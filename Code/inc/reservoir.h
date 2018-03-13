#include "stdint.h"


typedef struct Tank{
  uint32_t max_volume;
  uint32_t volume;
  uint32_t input;
  uint32_t output;
  int32_t correction;
  uint8_t percent;
  uint8_t full;
  uint8_t level;  
} Tank;


void tank_control(Tank *tank);

uint8_t lever(uint8_t lower, uint8_t top);

void correction(Tank *tank);

void calc_volume_tank(Tank *tank);

void calc_percent(Tank *tank);

void check_fulling(Tank *tank);
