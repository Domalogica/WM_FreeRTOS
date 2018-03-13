#include "reservoir.h"


uint8_t lever(uint8_t lower, uint8_t top);
void correction(Tank *tank);
void calc_volume_tank(Tank *tank);
void calc_percent(Tank *tank);
void check_fulling(Tank *tank);
uint32_t impulse_to_litr(uint32_t impulse, float coff);



void tank_config(Tank *tank, TankConfig config){
  (*tank).input_coff = config.input_coff;
	(*tank).output_coff = config.output_coff;
	(*tank).max_volume = config.max_volume;
	(*tank).volume = config.volume;
	(*tank).correction = config.correction;  
}

uint8_t tank_control(Tank *tank, uint8_t lower, uint8_t top){
  (*tank).level ==  lever(lower, top);
  (*tank).input == impulse_to_litr((*tank)._input, (*tank).input_coff);
  (*tank).output == impulse_to_litr((*tank)._output, (*tank).output_coff);
  correction(tank);
  calc_volume_tank(tank);
  calc_percent(tank);
  check_fulling(tank);
  return (*tank).full;
}

void callback_input(Tank *tank){
  (*tank)._input++;
}

void callback_output(Tank *tank){
  (*tank)._output++;
}

uint8_t lever(uint8_t lower, uint8_t top){
  return (top) ? 2 : lower;
}

uint32_t impulse_to_litr(uint32_t impulse, float coff){
  return (uint32_t)(impulse * coff);
}

void correction(Tank *tank){
  if ((*tank).level == 0){
    (*tank).correction = (*tank).output - (*tank).input;
  }
  else if((*tank).level == 1){
      if ((*tank).output > (*tank).input){
        (*tank).correction += ((*tank).output - (*tank).input) * 2 + (*tank).correction;
      }      
    }
    else{   
      (*tank).correction += (*tank).max_volume - (*tank).volume ;
    }
  
}

void calc_volume_tank(Tank *tank){
   int32_t res = (*tank).input - (*tank).output + (*tank).correction;
  (*tank).volume =  (res >= 0) ? res : 0;
}

void calc_percent(Tank *tank){
  (*tank).percent = (float)((*tank).max_volume /(*tank).volume);
}

void check_fulling(Tank *tank){
  if ((*tank).percent <= 80){
    (*tank).full = 0;
  }
  if (!(*tank).full && (*tank).level > 1){
    (*tank).full = 1;
  }
  if ((*tank).full && (*tank).level < 1){
    (*tank).full = 0;
  }
}
