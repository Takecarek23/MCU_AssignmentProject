## 🚦 STM32 Smart Traffic Light System

   

Hệ thống mô phỏng đèn giao thông ngã tư thông minh sử dụng vi điều khiển **STM32F103RB**. Dự án được thiết kế với kiến trúc **Finite State Machine (FSM)**, hỗ trợ đa chế độ hoạt động và khả năng tùy chỉnh thời gian thực qua giao diện người dùng.

### 🎥 Demo Dự Án

Xem video demo hoạt động chi tiết tại đây:

[![Traffic Light Demo](https://img.youtube.com/vi/pS-fQDtUg2k/0.jpg)](https://www.youtube.com/watch?v=pS-fQDtUg2k)

*(Click vào hình ảnh để xem video)*

-----

### 📑 Tính Năng Chính

Hệ thống hoạt động với 3 chế độ chính (State Machine):

1.  **MODE 1: AUTO (Tự động)**

      * Hoạt động như đèn giao thông thực tế tại ngã tư.
      * Hiển thị đếm ngược thời gian (Countdown) trên màn hình LCD.
      * Hai trụ đèn hoạt động lệch pha (Xanh - Đỏ) để điều tiết giao thông.

2.  **MODE 2: MANUAL (Thủ công)**

      * Chế độ dành cho cảnh sát giao thông điều tiết khi tắc đường.
      * Đèn sẽ **ngừng đếm ngược** và giữ nguyên trạng thái.
      * Sử dụng nút nhấn để chuyển đổi pha đèn thủ công (Đỏ -\> Xanh -\> Vàng).

3.  **MODE 3, 4, 5: TUNING (Cài đặt)**

      * Cho phép người dùng chỉnh sửa thời gian của đèn Đỏ, Xanh, Vàng.
      * Đèn đang chỉnh sửa sẽ nhấp nháy (Blink 2Hz) để báo hiệu.
      * Tự động tính toán logic thời gian (`T_Red = T_Green + T_Yellow`).

-----

### 🛠️ Phần Cứng (Hardware)

| Thành phần | Số lượng | Ghi chú |
| :--- | :--- | :--- |
| **STM32 Nucleo-F103RB** | 1 | Board mạch chính |
| **Traffic Light Module** | 2 | Loại module tiết kiệm chân (2 pins control 3 colors) |
| **LCD 1602 + I2C Module**| 1 | Hiển thị thông tin & Đếm ngược |
| **Push Buttons** | 2 | Nút nhấn nhả (Pull-up resistor) |
| **Dây nối (Jumpers)** | - | Đực-Cái, Cái-Cái |

### 🔌 Sơ Đồ Chân (Pinout Configuration)

**Lưu ý quan trọng:** Module đèn giao thông sử dụng cơ chế mã hóa 2 bit (A-B) để hiển thị 3 màu.

| Chân STM32 | Tên Label (Code) | Kết nối tới Module | Chức năng |
| :--- | :--- | :--- | :--- |
| **PB3** | `D3` | Traffic Light 1 - Pin A | Bit cao điều khiển Đèn 1 |
| **PB5** | `D4` | Traffic Light 1 - Pin B | Bit thấp điều khiển Đèn 1 |
| **PB4** | `D5` | Traffic Light 2 - Pin A | Bit cao điều khiển Đèn 2 |
| **PB10** | `D6` | Traffic Light 2 - Pin B | Bit thấp điều khiển Đèn 2 |
| **PA8** | `Button1` | Button 1 | Nút chuyển chế độ (Mode) |
| **PA9** | `Button2` | Button 2 | Nút chỉnh thời gian / Đổi đèn |
| **PB8** | `I2C1_SCL` | LCD SCL | Xung nhịp I2C |
| **PB9** | `I2C1_SDA` | LCD SDA | Dữ liệu I2C |

> **Logic Đèn (Truth Table):**
>
>   * `00` (A=0, B=0): OFF
>   * `01` (A=0, B=1): YELLOW
>   * `10` (A=1, B=0): GREEN
>   * `11` (A=1, B=1): RED

-----

### 📂 Cấu Trúc Dự Án

Dự án tuân thủ cấu trúc phân lớp để dễ dàng làm việc nhóm:

```text
Core/
├── Inc/
│   ├── input_processing.h # Máy trạng thái
│   ├── i2c-lcd.h          # Hiển thị LCD
│   ├── timer.h            # Cấu hình timer
│   ├── traffic logic.h    # Thiết lập thời gian 
│   ├── output_display.h   # Driver điều khiển LED & LCD
│   └── input_reading.h    # Driver đọc nút nhấn (Debounce)
├── Src/
│   ├── main.c             # Vòng lặp chính & Scheduler
│   ├── output_display.c   # Xử lý logic hiển thị
│   ├── input_reading.c    # Xử lý chống rung phím
│   └── ... (Các file logic FSM)
└── MCU_AssignmentProject.ioc # Cấu hình STM32CubeMX
```

-----

### 🚀 Hướng Dẫn Cài Đặt (Installation)

1.  **Clone dự án về máy:**
    ```bash
    git clone https://github.com/Takecarek23/MCU_AssignmentProject.git
    ```
2.  **Mở bằng STM32CubeIDE:**
      * File -\> Open Projects from File System...
      * Chọn thư mục vừa clone.
3.  **Cấu hình Drivers (Nếu cần):**
      * Mở file `MCU_AssignmentProject.ioc`.
      * Nhấn **Device Configuration Tool Code Generation** (hoặc Save) để IDE tự động tải thư viện HAL.
4.  **Build & Run:**
      * Nhấn biểu tượng cái búa (🔨) để biên dịch.
      * Kết nối mạch Nucleo và nạp code qua STM32CubeProgrammer.

-----

### 👥 Thành Viên Nhóm (Contributors)

Dự án được thực hiện bởi:

  * **[Nguyễn Bảo Trọng]** - *System Architect & Leader*
      * Github: [@Takecarek23](https://www.google.com/search?q=https://github.com/usernameA)
      * Role: Setup hệ thống, FSM Architecture.
  * **[Lương Ngô Phong Vinh]** - *Driver Engineer*
      * Github: [@Dahlia1337](https://github.com/Dahlia1337)
      * Role: LCD & LED Logic Control.
  * **[Phạm Quốc Việt]** - *Logic Engineer*
      * Github: [@phamquocviet4805](https://github.com/phamquocviet4805)
      * Role: Input Handling (Button Debounce) & Timer Logic.

-----

*Created with ❤️ - HCMUT*