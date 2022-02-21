#ifndef SELF_FUNCTIONS_H
#define SELF_FUNCTIONS_H

#include"lvgl.h"

uint16_t pow(uint8_t num, uint8_t i);
void num2str(uint16_t num, uint8_t* str, uint8_t str_len);
uint8_t month_days(uint16_t year, uint8_t month);

#endif
