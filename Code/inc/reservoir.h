#include "stdint.h"

typedef struct TankConfig{
  uint32_t max_volume;
  float input_coff;
  float output_coff;
  uint32_t volume;
  int32_t correction;  
}TankConfig;


typedef struct Tank{
  float percent;
  float input_coff;
  float output_coff;
  uint32_t _input;
  uint32_t _output;
  uint32_t max_volume;
  uint32_t volume;
  uint32_t input;
  uint32_t output;
  int32_t correction;  
  uint8_t full;
  uint8_t level;  
} Tank;


//initial tank setting
void tank_config(Tank *tank, TankConfig config);

//main function tank control
uint8_t tank_control(Tank *tank, uint8_t lower, uint8_t top);

//callback function input
void callback_input(Tank *tank);

//callback function output
void callback_output(Tank *tank);
