/*
 * i2c_lcd.c
 *
 *  Created on: Dec 2, 2025
 *      Author: TRONG
 */

#include "i2c-lcd.h"
#include <stdio.h>
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD (0x21 << 1) // change this according to ur setup

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void) {
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	lcd_send_cmd (0x01); /* clear display */
	HAL_Delay(50);
	lcd_send_cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	lcd_send_cmd (0x0c); /* set display to on */
	HAL_Delay(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 1)
	{
		pos_Addr = 0x80 + row - 1 + col;
	}
	else
	{
		pos_Addr = 0x80 | (0x40 + col);
	}
	lcd_send_cmd(pos_Addr);
}

// Hàng 1 mode
void LCD_Show_Mode(int status) {
    lcd_goto_XY(1, 0);

    switch (status) {
        case MODE_AUTO:
            lcd_send_string("MODE: AUTO      ");
            break;
        case MODE_MANUAL:
            lcd_send_string("MODE: MANUAL    ");
            break;
        case MODE_TUNING_RED:
            lcd_send_string("TUNE: RED LED   ");
            break;
        case MODE_TUNING_YELLOW:
            lcd_send_string("TUNE: YELLOW LED");
            break;
        case MODE_TUNING_GREEN:
            lcd_send_string("TUNE: GREEN LED ");
            break;
        default:
            lcd_send_string("ERROR           ");
            break;
    }
}

// Hàng 2 thời gian
// status: Chế độ hiện tại
// val1: Thời gian đèn 1 (Hoặc giá trị đang chỉnh sửa)
// val2: Thời gian đèn 2 (Chỉ dùng trong Auto)
void LCD_Show_Data(int status, int val1, int val2) {
    lcd_goto_XY(2, 0);

    switch (status) {
            case MODE_AUTO:
                // Hiển thị 2 đồng hồ đếm ngược. Ví dụ: "T1:15s   T2:20s "
                // %02d nghĩa là số có 2 chữ số (vd: 05, 09)
                sprintf(buffer, "T1:%02d, T2:%02d", val1, val2);
                lcd_send_string(buffer);
                HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
                break;

            case MODE_MANUAL:
            	switch (manualPhase) {
            		case 0: lcd_send_string("MAN: RED - GREEN"); break;
            		case 1: lcd_send_string("MAN: RED - AMBER"); break;
            		case 2: lcd_send_string("MAN: GREEN - RED"); break;
            		case 3: lcd_send_string("MAN: AMBER - RED"); break;
            	}
                break;
            case MODE_TUNING_RED:
                // Hiển thị giá trị đang chỉnh. Ví dụ: "Duration: 15s   "
                sprintf(buffer, "Duration: %02d s ", val1);
                lcd_send_string(buffer);
                HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
                break;
            case MODE_TUNING_YELLOW:
                sprintf(buffer, "Duration: %02d s ", val1);
                lcd_send_string(buffer);
                break;
            case MODE_TUNING_GREEN:
                sprintf(buffer, "Duration: %02d s ", val1);
                lcd_send_string(buffer);
                break;
            default:
            	break;
        }
}



