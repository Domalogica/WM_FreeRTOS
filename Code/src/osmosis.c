#include "osmos_dispeser.h"

void enable_source(Osmosis *osmosis, uint32_t ultra, uint32_t permeate){
  if ((*osmosis).source){
    if ((*osmosis)._ultra > ultra)
      (*osmosis).source = 0;  
    }
  else{
    if ((*osmosis)._permeate > permeate)
      (*osmosis).source = 1;
 }
}

void check_next_step(Osmosis *osmosis){
  if((*osmosis).old_source == !(*osmosis).source)
    (*osmosis).step++;
  
  (*osmosis).old_source = (*osmosis).source;
}

uint32_t limit_permiate(Osmosis *osmosis){
  return (*osmosis).step * (*osmosis).len * (*osmosis).permeate;  
}

uint32_t limit_ultra(Osmosis *osmosis){
  return (*osmosis).len * (*osmosis).step * (*osmosis).ultra;
}

void osmosis_mdg(Osmosis *osmosis){
  uint32_t ultra = limit_ultra(osmosis);
  uint32_t permeate = limit_permiate(osmosis);
  enable_source(osmosis, ultra, permeate);
  check_next_step(osmosis);
}

void callback_osmosis(Osmosis *osmosis){
  if ((*osmosis).source){
    (*osmosis)._ultra++;
  }
  else{
    (*osmosis)._permeate++;
  } 
}

uint8_t valve_ultra(Osmosis *osmosis){
  return (*osmosis).source);
}

uint8_t valve_permiate(Osmosis *osmosis){
  return !(*osmosis).source);
}
