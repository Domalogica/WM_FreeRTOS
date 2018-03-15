#ifndef MONEY_H_
#define MONEY_H_
#include "stdint.h"

#define MAX_COIN         1000
#define MAX_PAPER        10000
#define CLEAR_OR_CORRECT 0
#define UNCORRECT        -1
#define TRUE             1
#define FALSE            0

uint32_t set_coins(stats_of_money money, value);
uint32_t set_papers(stats_of_money money, value);

uint32_t get_money(stats_of_money money);
void clear_all_cash(stats_of_money money);

void on_sensor_of_paper(void);
void off_sensor_of_paper(void);

void on_sensor_of_coin(void);
void off_sensor_of_coin(void);

// typedef struct {
//   uint32_t coins;
//   uint32_t papers;
//   uint32_t cashing;
//   uint8_t  sensor_of_paper;
//   uint8_t  sensor_of_coin;
// } stats_of_money;

#define COIN_PORT       NINT_IN13_GPIO_Port             // PB3, R25, 8
#define COIN_PIN        NINT_IN13_Pin

#define MONEY_PORT      NINT_IN14_GPIO_Port             // PD7, R26, 9
#define MONEY_PIN       NINT_IN14_Pin

#endif