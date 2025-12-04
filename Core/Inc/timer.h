/*
 * timer.h
 *
 *  Created on: Oct 12, 2025
 *      Author: TRONG
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

extern int flagInterruptLED_and_SEG;
extern int flagRed[2];
extern int flagGreen[2];
extern int flagYellow[2];

extern int flagMode_RED_BLINK;
extern int flagMode_GREEN_BLINK;
extern int flagMode_YELLOW_BLINK;

void runTimer_LED(void);
int getCycle_time_ms(void);
void button_reading(void);

int getTimer1Value(void);
int getTimer2Value(void);

#endif /* INC_TIMER_H_ */
