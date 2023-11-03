#pragma once

//TAGS for logging
#define INFO "Info"
#define ERROR "Error"

// Display pin definition
#define TFT_BL 2
#define TFT_DE 40
#define TFT_VSYNC 41
#define TFT_HSYNC 39
#define TFT_PCLK 42
#define TFT_R0 45
#define TFT_R1 48
#define TFT_R2 47
#define TFT_R3 21
#define TFT_R4 14
#define TFT_G0 5
#define TFT_G1 6
#define TFT_G2 7
#define TFT_G3 15
#define TFT_G4 16
#define TFT_G5 4
#define TFT_B0 8
#define TFT_B1 3
#define TFT_B2 46
#define TFT_B3 9
#define TFT_B4 1

// ST7262 IPS LCD 800x480 setting
#define TFT_WIDTH 800
#define TFT_HSYNC_POL 0
#define TFT_HSYNC_FRONT 8
#define TFT_HSYNC_PULSE 4
#define TFT_HSYNC_BACK 8
#define TFT_HEIGHT 480
#define TFT_VSYNC_POL 0
#define TFT_VSYNC_FRONT 8
#define TFT_VSYNC_PULSE 4
#define TFT_VSYNC_BACK 8
#define TFT_PCLK_NEG 1
#define TFT_SPEED_PREF 14000000
#define TFT_AUTO_FLUSH true

// Touchscreen pin definition
#define TOUCH_GT911_SCL 20
#define TOUCH_GT911_SDA 19
#define TOUCH_GT911_INT -1
#define TOUCH_GT911_RST 38
#define TOUCH_GT911_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 480
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 272
#define TOUCH_MAP_Y2 0

//SD card slot pin definition
#define SD_CS 10
#define SD_MOSI 11
#define SD_SCK 12
#define SD_MISO 13

// Configurations
#define WIFI_SCAN_ITER 5
#define WIFI_SSID_PW_DELIMITER "^_"

#define SYSTEM_UPDATE_INTERVAL 1 * 1000

#define DEFAULT_TZ "CET-1CEST,M3.5.0,M10.5.0/3"