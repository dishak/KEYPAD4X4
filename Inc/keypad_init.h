/*
 * keypad_init.h
 *
 */

#ifndef KEYPAD_INIT_H_
#define KEYPAD_INIT_H_
#include "STM32fxx_gpio.h"

#define KEYPAD_GPIO_PORT GPIOB
void KEYPAD_PINS_CONFIG(void);
 uint8_t DETECT_KEY_PRESS(void);
 int find_element(void);
#endif /* KEYPAD_INIT_H_ */
