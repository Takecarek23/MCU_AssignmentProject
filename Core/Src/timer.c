/*
 * timer.c
 *
 *  Created on: Oct 12, 2025
 *      Author: TRONG
 */
#include "timer.h"
#include "i2c-lcd.h"
#include "output_display.h"
#include "traffic_logic.h"

int flagInterruptLED_and_SEG = 1;
int flagRed[2]    = {0, 0};
int flagGreen[2]  = {0, 0};
int flagYellow[2] = {0, 0};

static int MAX_COUNTER = 0;
static int counter_mode_2_3_4 = 0;

int flagMode_RED_BLINK = 0;
int flagMode_GREEN_BLINK = 0;
int flagMode_YELLOW_BLINK = 0;

#define TIMER_CYCLE_MS 10

enum LightState {
    STATE_RED,
    STATE_GREEN,
    STATE_YELLOW
};

static enum LightState lightState1 = STATE_RED;
static enum LightState lightState2 = STATE_GREEN;

static int timerCounter1;
static int timerCounter2;

void restartAllFromScratch(void) {
    lightState1 = STATE_RED;
    lightState2 = STATE_GREEN;

    timerCounter1 = getDurationTime_RED_ms() / TIMER_CYCLE_MS;
    timerCounter2 = getDurationTime_GREEN_ms() / TIMER_CYCLE_MS;
}

void runTimer_LED(void) {
    if (timerCounter1 > 0) {
        timerCounter1--;
    }

    if (timerCounter1 <= 0) {
        switch (lightState1) {
            case STATE_RED:
                lightState1 = STATE_GREEN;
                timerCounter1 = getDurationTime_GREEN_ms() / TIMER_CYCLE_MS;
                break;
            case STATE_GREEN:
                lightState1 = STATE_YELLOW;
                timerCounter1 = getDurationTime_YELLOW_ms() / TIMER_CYCLE_MS;
                break;
            case STATE_YELLOW:
                lightState1 = STATE_RED;
                timerCounter1 = getDurationTime_RED_ms() / TIMER_CYCLE_MS;
                break;
        }
    }

    if (timerCounter2 > 0) {
        timerCounter2--;
    }

    if (timerCounter2 <= 0) {
        switch (lightState2) {
            case STATE_RED:
                lightState2 = STATE_GREEN;
                timerCounter2 = getDurationTime_GREEN_ms() / TIMER_CYCLE_MS;
                break;
            case STATE_GREEN:
                lightState2 = STATE_YELLOW;
                timerCounter2 = getDurationTime_YELLOW_ms() / TIMER_CYCLE_MS;
                break;
            case STATE_YELLOW:
                lightState2 = STATE_RED;
                timerCounter2 = getDurationTime_RED_ms() / TIMER_CYCLE_MS;
                break;
        }
    }

	switch (lightState1) {
		case STATE_RED:
			displayLED_RED(1, 0);
			break;
		case STATE_GREEN:
			displayLED_GREEN(1, 0);
			break;
		case STATE_YELLOW:
			displayLED_YELLOW(1, 0);
			break;
	}

	switch (lightState2) {
		case STATE_RED:
			displayLED_RED(1, 1);
			break;
		case STATE_GREEN:
			displayLED_GREEN(1, 1);
			break;
		case STATE_YELLOW:
			displayLED_YELLOW(1, 1);
			break;
	}
}
int getCycle_time_ms(void){
    return 10;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM2) {
	    button_reading();
	    if (flagInterruptLED_and_SEG == 1) {
	        runTimer_LED();

	    }
		 else {

			if (MAX_COUNTER <= 0) {
				MAX_COUNTER = 500 / getCycle_time_ms();
				counter_mode_2_3_4 = MAX_COUNTER;
			}

			if (flagMode_RED_BLINK == 1) {
				if (counter_mode_2_3_4 <= 0) {
					counter_mode_2_3_4 = MAX_COUNTER;
				} else {
					if (counter_mode_2_3_4 == MAX_COUNTER / 2) {
						flagRed[0] = 0;
						flagRed[1] = 0;
					} else if (counter_mode_2_3_4 == MAX_COUNTER) {
						flagRed[0] = 1;
						flagRed[1] = 1;
					}
					--counter_mode_2_3_4;
				}
			}

			if (flagMode_GREEN_BLINK == 1) {
				if (counter_mode_2_3_4 <= 0) {
					counter_mode_2_3_4 = MAX_COUNTER;
				} else {
					if (counter_mode_2_3_4 == MAX_COUNTER / 2) {
						flagGreen[0] = 0;
						flagGreen[1] = 0;
					} else if (counter_mode_2_3_4 == MAX_COUNTER) {
						flagGreen[0] = 1;
						flagGreen[1] = 1;
					}
					--counter_mode_2_3_4;
				}
			}

			if (flagMode_YELLOW_BLINK == 1) {
				if (counter_mode_2_3_4 <= 0) {
					counter_mode_2_3_4 = MAX_COUNTER;
				} else {
					if (counter_mode_2_3_4 == MAX_COUNTER / 2) {
						flagYellow[0] = 0;
						flagYellow[1] = 0;
					} else if (counter_mode_2_3_4 == MAX_COUNTER) {
						flagYellow[0] = 1;
						flagYellow[1] = 1;
					}
					--counter_mode_2_3_4;
				}
			}
		}
	}
}

int getTimer1Value(void) {
    return timerCounter1;
}

int getTimer2Value(void) {
    return timerCounter2;
}

