/*
 * input_processing.h
 *
 *  Created on: Oct 11, 2025
 *      Author: TRONG
 */
#include "main.h"
#include "input_reading.h"
#include "output_display.h"
#include "timer.h"
#include "traffic_logic.h"
#include "i2c-lcd.h"

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

enum State {
    RELEASED,
    PRESSED
};
enum Mode {
	MODE_1_NORMAL, MODE_2_MANUAL, MODE_3_RED_MODIFY, MODE_4_YELLOW_MODIFY, MODE_5_GREEN_MODIFY
};

extern int manualPhase;
void fsm_for_input_processing(void);

#endif /* INC_INPUT_PROCESSING_H_ */
