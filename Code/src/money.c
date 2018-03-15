#include "money.h"
#include "stdint.h"
#include "gpio.h"

// ��� �������� ����� ����������� � ������ ������
uint32_t set_coins(Stats_of_money money, uint32_t value) {
  if(value <= MAX_COIN) {
    money.coins += value;
    money.cashing += value;
    return CLEAR_OR_CORRECT;
  }

 return UNCORRECT;
} 
 
// ��� �������� ����� ����������� � ������ ������
uint32_t set_papers(Stats_of_money money, uint32_t value) {
  if(value <= MAX_PAPER) {  
    money.papers += value;
    money.cashing += value;
    return CLEAR_OR_CORRECT;
  }
  return UNCORRECT;
}

// ������� ��� ��������� �����
uint32_t get_money(Stats_of_money money) {
  return (money.coins + money.papers);
}

// ������� ��� ������� ����� ����� ������
void clear_all_cash(Stats_of_money money) {
  money.coins  = CLEAR_OR_CORRECT;
  money.papers = CLEAR_OR_CORRECT;
}

// ������� ��� ��������� ���������������
void on_sensor_of_coin(void) {
  GPIO_SetOutputPin(COIN_PORT,  COIN_PIN);
}

// ������� ��� ���������� ���������������
void off_sensor_of_coin(void) {
  GPIO_ResetOutputPin(COIN_PORT,  COIN_PIN);
}

// ������� ��� ��������� ���������������
void on_sensor_of_paper(void) {
  GPIO_SetOutputPin(MONEY_PORT,  MONEY_PIN);
}

// ������� ��� ���������� ���������������
void off_sensor_of_paper(void) {
  GPIO_ResetOutputPin(MONEY_PORT,  MONEY_PIN);
}
