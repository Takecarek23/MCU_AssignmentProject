/*
 * i2c-lcd.h
 *
 *  Created on: Dec 3, 2025
 *      Author: TRONG
 */

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#define MODE_AUTO          0
#define MODE_MANUAL        1
#define MODE_TUNING_RED    2
#define MODE_TUNING_YELLOW 3
#define MODE_TUNING_GREEN  4

#include "stm32f1xx_hal.h"
#include "main.h"

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear_display (void);	//clear display lcd

void lcd_goto_XY (int row, int col); //set proper location on screen

// HAI HÀM MỚI
void LCD_Show_Mode(int status); // Hiển thị mode ở dòng 1

void LCD_Show_Data(int status, int val1, int val2); // Hiển thị dữ liệu ở dòng 2

#endif /* INC_I2C_LCD_H_ */
