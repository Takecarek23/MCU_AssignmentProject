/*
 * input_reading.h
 *
 *  Created on: Oct 11, 2025
 *      Author: TRONG
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

void button_reading(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_incrementing(uint8_t index);

#endif /* INC_INPUT_READING_H_ */
