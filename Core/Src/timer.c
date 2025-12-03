/*
 * timer.c
 *
 *  Created on: Oct 12, 2025
 *      Author: TRONG
 */
#include "timer.h"

void restartAllFromScratch(void) {}

void runTimer_LED(void) {}
int getCycle_time_ms(void){
    return 10;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM2) {}
}

