/*
 * output_display.c
 *
 * Created on: Dec 3, 2025
 * Author: TRONG
 */

#include "output_display.h"

void displayLED_RED(int IS_ON, int index){
    // Logic ĐỎ: A = 1, B = 1. Nếu IS_ON thì set màu theo mã, không thì tắt
    GPIO_PinState stateA = (IS_ON == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    GPIO_PinState stateB = (IS_ON == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET;

    switch(index){
        case 0: // Traffic Light 1
            HAL_GPIO_WritePin(LIGHT_PORT, TL1_PIN_A, stateA);
            HAL_GPIO_WritePin(LIGHT_PORT, TL1_PIN_B, stateB);
            break;
        case 1: // Traffic Light 2
            HAL_GPIO_WritePin(LIGHT_PORT, TL2_PIN_A, stateA);
            HAL_GPIO_WritePin(LIGHT_PORT, TL2_PIN_B, stateB);
            break;
    }
}

void displayLED_YELLOW(int IS_ON, int index){
    // Logic VÀNG: A = 0, B = 1
    // Nếu IS_ON = 0 (tắt) thì cả A và B đều về 0
    GPIO_PinState stateA = GPIO_PIN_RESET;
    GPIO_PinState stateB = (IS_ON == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET;

    switch(index){
        case 0:
            HAL_GPIO_WritePin(LIGHT_PORT, TL1_PIN_A, stateA);
            HAL_GPIO_WritePin(LIGHT_PORT, TL1_PIN_B, stateB);
            break;
        case 1:
            HAL_GPIO_WritePin(LIGHT_PORT, TL2_PIN_A, stateA);
            HAL_GPIO_WritePin(LIGHT_PORT, TL2_PIN_B, stateB);
            break;
    }
}

void displayLED_GREEN(int IS_ON, int index){
    // Logic XANH: A = 1, B = 0
    // Nếu IS_ON = 0 (tắt) thì cả A và B đều về 0
    GPIO_PinState stateA = (IS_ON == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    GPIO_PinState stateB = GPIO_PIN_RESET;

    switch(index){
        case 0:
            HAL_GPIO_WritePin(LIGHT_PORT, TL1_PIN_A, stateA);
            HAL_GPIO_WritePin(LIGHT_PORT, TL1_PIN_B, stateB);
            break;
        case 1:
            HAL_GPIO_WritePin(LIGHT_PORT, TL2_PIN_A, stateA);
            HAL_GPIO_WritePin(LIGHT_PORT, TL2_PIN_B, stateB);
            break;
    }
}



