#include "drainage.h"

uint8_t _drainage = 0;

uint8_t drainage_control(Drainage *drainage, uint8_t sensor_1, uint8_t sensor_2){
  
  if(sensor_1 && sensor_2){
    (*drainage).pump = 1;
  }
  
  if(!sensor_1 && !sensor_2){
    (*drainage).pump = 0;
  }
  
  return (*drainage).pump;
}
