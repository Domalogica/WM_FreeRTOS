#include "drainage.h"

uint8_t _drainage = 0;

uint8_t drainage_control(uint8_t sensor_1, uint8_t sensor_2){
  
  if(sensor_1 && sensor_2){
    _drainage = 1;
  }
  
  if(!sensor_1 && !sensor_2){
    _drainage = 0;
  }
  return _drainage;
}

