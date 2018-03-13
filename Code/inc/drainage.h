#include "stdint.h"

typedef struct Drainage {
  uint32_t time;
  uint8_t pump;
}Drainage;


uint8_t drainage_control(Drainage *drainage, uint8_t sensor_1, uint8_t sensor_2);
