/*
 * input_reading.c
 *
 * Created on: Dec 3, 2025
 * Author: TRONG
 */
#include "input_reading.h"

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] =
    {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] =
    {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

uint16_t arrayPIN[NO_OF_BUTTONS] = {
    Button1_Pin,
    Button2_Pin
};

#define INITIAL_HOLD_DELAY      100
#define SUBSEQUENT_HOLD_DELAY   10

static uint8_t flagForButtonPressed[NO_OF_BUTTONS];

static int button_hold_counter[NO_OF_BUTTONS];

void button_reading(void) {
    for (int i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOA, arrayPIN[i]);
        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
        	if (buttonBuffer[i] != debounceButtonBuffer1[i]) {
				buttonBuffer[i] = debounceButtonBuffer1[i];
				// If the button has just been pressed
				if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
					flagForButtonPressed[i] = 1;
					button_hold_counter[i] = INITIAL_HOLD_DELAY; // Load the counter for the first wait
				}
			} else { // Unchanged state
				if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
					// If holding the button, continue to decrement the counter
					if (button_hold_counter[i] > 0) {
						button_hold_counter[i]--;
					}
				}
			}
        }
    }
}

unsigned char is_button_pressed(uint8_t index) {
    //if (index >= NO_OF_BUTTONS) return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_incrementing(uint8_t index) {
    //if(index >= NO_OF_BUTTONS) return 0;

    // 1. Returns the first click event
    if (flagForButtonPressed[index] == 1) {
        flagForButtonPressed[index] = 0;
        return 1;
    }

    // 2. Returns the event when the override has been held long enough
    if (buttonBuffer[index] == BUTTON_IS_PRESSED && button_hold_counter[index] == 0) {
    	// Reload the counter for the next increment
        button_hold_counter[index] = SUBSEQUENT_HOLD_DELAY;
        return 1;
    }

    return 0;
}

