/*
 * traffic_logic.h
 *
 *  Created on: Oct 13, 2025
 *      Author: TRONG
 */

#ifndef INC_TRAFFIC_LOGIC_H_
#define INC_TRAFFIC_LOGIC_H_

// Lấy giá trị thời gian hiện tại của mỗi đèn (tính bằng ms)
int getDurationTime_RED_ms(void);
int getDurationTime_YELLOW_ms(void);
int getDurationTime_GREEN_ms(void);

// Thiết lập giá trị thời gian mới cho mỗi đèn (tính bằng ms)
void setDurationTime_RED_ms(int duration_ms);
void setDurationTime_YELLOW_ms(int duration_ms);
void setDurationTime_GREEN_ms(int duration_ms);

// Reset lại trạng thái đèn giao thông về ban đầu sau khi cài đặt xong
void restartAllFromScratch(void);

#endif /* INC_TRAFFIC_LOGIC_H_ */

