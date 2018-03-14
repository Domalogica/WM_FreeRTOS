#include "money.h"
#include "stdint.h"
#include "gpio.h"

// Для фиксации монет поступающих в момент сессии
uint32_t set_coins(Stats_of_money money, uint32_t value) {
  if(value <= MAX_COIN) {
    money.coins += value;
    money.cashing += value;
    return CLEAR_OR_CORRECT;
  }

 return UNCORRECT;
} 
 
// Для фиксации купюр поступающих в момент сессии
uint32_t set_papers(Stats_of_money money, uint32_t value) {
  if(value <= MAX_PAPER) {  
    money.papers += value;
    money.cashing += value;
    return CLEAR_OR_CORRECT;
  }
  return UNCORRECT;
}

// Функция для получения денег
uint32_t get_money(Stats_of_money money) {
  return (money.coins + money.papers);
}

// Функция для очистки после конца сессии
void clear_all_cash(Stats_of_money money) {
  money.coins  = CLEAR_OR_CORRECT;
  money.papers = CLEAR_OR_CORRECT;
}

// Функция для включения монетоприемника
void on_sensor_of_coin(void) {
  GPIO_SetOutputPin(COIN_PORT,  COIN_PIN);
}

// Функция для выключения монетоприемника
void off_sensor_of_coin(void) {
  GPIO_ResetOutputPin(COIN_PORT,  COIN_PIN);
}

// Функция для включения купюроприемника
void on_sensor_of_paper(void) {
  GPIO_SetOutputPin(MONEY_PORT,  MONEY_PIN);
}

// Функция для выключения купюроприемника
void off_sensor_of_paper(void) {
  GPIO_ResetOutputPin(MONEY_PORT,  MONEY_PIN);
}
