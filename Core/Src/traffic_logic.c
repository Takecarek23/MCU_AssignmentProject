#include "traffic_logic.h"

// Giá trị khởi tạo ban đầu (Đỏ: 5s, Vàng: 2s, Xanh: 3s)
static int duration_red_ms = 5000;
static int duration_yellow_ms = 2000;
static int duration_green_ms = 3000;

// --- THỰC THI CÁC HÀM GETTER ---
int getDurationTime_RED_ms(void) {
    return duration_red_ms;
}
int getDurationTime_YELLOW_ms(void) {
    return duration_yellow_ms;
}
int getDurationTime_GREEN_ms(void) {
    return duration_green_ms;
}

// --- THỰC THI CÁC HÀM SETTER ---
void setDurationTime_RED_ms(int duration_ms) {
    duration_red_ms = duration_ms;
}
void setDurationTime_YELLOW_ms(int duration_ms) {
    duration_yellow_ms = duration_ms;
}
void setDurationTime_GREEN_ms(int duration_ms) {
    duration_green_ms = duration_ms;
}

// Hàm restartAllFromScratch sẽ được thực hiện trong timer.c
// vì nó cần truy cập vào các biến trạng thái static của timer.
