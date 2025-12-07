/*
 * input_processing.c
 *
 * Created on: Oct 10, 2025
 * Author: TRONG
 */

#include "main.h"
#include "i2c-lcd.h"
#include "input_reading.h"
#include "output_display.h"
#include "timer.h"
#include "traffic_logic.h"
#include "input_processing.h"

static enum Mode currentMode = MODE_1_NORMAL;
static enum State prevState[NO_OF_BUTTONS] = {RELEASED, RELEASED};
static enum State currState[NO_OF_BUTTONS] = {RELEASED, RELEASED};

extern int getDurationTime_RED_ms(void);
extern void setDurationTime_RED_ms(int duration);
extern int getDurationTime_YELLOW_ms(void);
extern void setDurationTime_YELLOW_ms(int duration);
extern int getDurationTime_GREEN_ms(void);
extern void setDurationTime_GREEN_ms(int duration);
extern void restartAllFromScratch(void);

int manualPhase = 0;
static int temp_duration_ms = 0;
void fsm_for_input_processing(void) {
    // 1. Read and update the status for all buttons
    for (int i = 0; i < NO_OF_BUTTONS; ++i) {
        prevState[i] = currState[i];
        if (is_button_pressed(i) == 1) {
            currState[i] = PRESSED;
        } else {
            currState[i] = RELEASED;
        }
    }

    // 2. Create a flag for each button click event to make the code easier to read
    int is_mode_button_pressed		= (currState[0] == PRESSED && prevState[0] == RELEASED);
    int is_increment_event       	= is_button_incrementing(1);

    // 3. Main logic processing based on current mode (currentMode)
    switch (currentMode) {
        case MODE_1_NORMAL:
        	flagInterruptLED_and_SEG = 1; // To turn on the normal state
        	LCD_Show_Mode(0); // Là mode auto
        	// Lấy giá trị từ timer.c và chia cho 100 để ra giây (vì chu kỳ là 10ms)
			int time1_sec = getTimer1Value() / 100;
			int time2_sec = getTimer2Value() / 100; // Sửa lỗi cũ: dùng getTimer2Value

			LCD_Show_Data(0, time1_sec, time2_sec);
            if (is_mode_button_pressed) { // If button 1 is pressed, go to edit mode RED
                currentMode = MODE_2_MANUAL;
                temp_duration_ms = getDurationTime_RED_ms();
            }
            break;
        case MODE_2_MANUAL:
			LCD_Show_Mode(1); // Luôn hiển thị tiêu đề hàng 1

			// --- 4. CHUYỂN MODE ---
			if (is_mode_button_pressed) {
				currentMode = MODE_3_RED_MODIFY;
			}
			break;
        case MODE_3_RED_MODIFY:
        	LCD_Show_Mode(2);

        	flagInterruptLED_and_SEG = 0; // To turn off the normal state
    		flagMode_RED_BLINK = 1; // Blink the led red with 2Hz

    		displayLED_RED(flagRed[0], 0); // flashing red light at 2Hz frequency
			displayLED_RED(flagRed[1], 1); // flashing red light at 2Hz frequency

			LCD_Show_Data(2, temp_duration_ms / 1000, temp_duration_ms / 1000);

            // Switch to MODE 3 if "is_mode_button_pressed"
            if (is_mode_button_pressed) {
                currentMode = MODE_4_YELLOW_MODIFY;
                flagMode_RED_BLINK = 0;
                temp_duration_ms = getDurationTime_YELLOW_ms();
            }

            // Hold down button 2
			if (is_increment_event) {
				temp_duration_ms += 1000;
				if (temp_duration_ms > 99000) temp_duration_ms = 1000;
				setDurationTime_RED_ms(getDurationTime_GREEN_ms() + getDurationTime_YELLOW_ms());
				// Nói chung là đèn đỏ để chưng thôi, chừng nào đổi 2 đèn kia mới đổi được đèn đỏ
				// Nếu muốn đỏ lên, xanh cũng lên thì bị trường hợp nếu đỏ giảm thì sao
//				setDurationTime_RED_ms(temp_duration_ms);
//				setDurationTime_GREEN_ms(getDurationTime_RED_ms() - getDurationTime_YELLOW_ms());
			}
            break;

        case MODE_4_YELLOW_MODIFY:
        	// Hiển thị mode 3 trên dòng đầu tiên lcd
        	LCD_Show_Mode(3);

        	flagInterruptLED_and_SEG = 0; // Tắt cờ của chế độ auto
            flagMode_YELLOW_BLINK = 1; // Nhấp nháy led vàng

            // Nhấp nháy 2 bên luôn
            displayLED_YELLOW(flagYellow[0], 0);
            displayLED_YELLOW(flagYellow[1], 1);

            // Hiển thị dòng 2, 2 số thời gian gian giống nhau
            LCD_Show_Data(3, temp_duration_ms / 1000, temp_duration_ms / 1000);

            // Nếu nút 1 được nhấn
            if (is_mode_button_pressed) {

            	flagMode_YELLOW_BLINK = 0; // Tắt đèn vàng đang nháy
                currentMode = MODE_5_GREEN_MODIFY; // Chuyển sang chế độ điều chỉnh đèn xanh
                temp_duration_ms = getDurationTime_GREEN_ms(); // Lấy thời gian hiện tại của đèn xanh
            }

			if (is_increment_event) { // Nếu nút 2 được nhấn
				temp_duration_ms += 1000;
				if (temp_duration_ms > 99000) temp_duration_ms = 1000;
				setDurationTime_YELLOW_ms(temp_duration_ms); // Lưu thời gian đèn vàng
				setDurationTime_RED_ms(getDurationTime_GREEN_ms() + getDurationTime_YELLOW_ms());
				// Tới đây đèn đỏ mới cập nhật
			}
            break;

        case MODE_5_GREEN_MODIFY:
        	LCD_Show_Mode(4);

        	flagInterruptLED_and_SEG = 0;
            flagMode_GREEN_BLINK = 1;

            displayLED_GREEN(flagGreen[0], 0);
            displayLED_GREEN(flagGreen[1], 1);

            LCD_Show_Data(3, temp_duration_ms / 1000, temp_duration_ms / 1000);

            if (is_mode_button_pressed) {
            	flagMode_YELLOW_BLINK = 0;
                currentMode = MODE_1_NORMAL;
                restartAllFromScratch();
                temp_duration_ms = getDurationTime_GREEN_ms();
            }

			if (is_increment_event) {
				temp_duration_ms += 1000;
				if (temp_duration_ms > 99000) temp_duration_ms = 1000;
				setDurationTime_GREEN_ms(temp_duration_ms); // Lưu thời gian đèn vàng
				setDurationTime_RED_ms(getDurationTime_GREEN_ms() + getDurationTime_YELLOW_ms());
			}
            break;

        default:
            currentMode = MODE_1_NORMAL;
            break;
    }
}
