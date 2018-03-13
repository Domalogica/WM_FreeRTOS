#include "reservoir.h"


void tank_control(Tank *tank){
  calc_percent(tank);
  correction(tank);
  calc_volume_tank(tank);  
}

uint8_t lever(uint8_t lower, uint8_t top){
  return (top) ? 2 : lower;
}

void correction(Tank *tank){
  if ((*tank).level == 0){
    (*tank).correction = (*tank).output - (*tank).input;
  }else 
    if((*tank).level == 1){
      if ((*tank).output > (*tank).input){
        (*tank).correction += ((*tank).output - (*tank).input) * 2 + (*tank).correction;
      }else{
       (*tank).correction = (*tank).correction;
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
  (*tank).percent = (uint8_t)((float)((*tank).max_volume /(*tank).volume) * 100);  
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
 