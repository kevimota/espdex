#pragma once

#include <Arduino.h>
#include <vector>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <TAMC_GT911.h>
#include "defines.h"
#include "lvgl.h"
#include "FS.h"
#include "SD.h"
#include "ArduinoJson.h"
#include "esp_task_wdt.h"

#define COLOR_NORMAL 0xBCBCB0
#define COLOR_POISON 0xAB5BA0
#define COLOR_PSYCHIC 0xF562B0
#define COLOR_GRASS 0x8DD651
#define COLOR_GROUND 0xEAC956
#define COLOR_ICE 0x95F1FE
#define COLOR_FIRE 0xFA5542
#define COLOR_ROCK 0xCDBD72
#define COLOR_DRAGON 0x8775FD
#define COLOR_WATER 0x57AEFE
#define COLOR_BUG 0xC1D221
#define COLOR_DARK 0x866350
#define COLOR_FIGHTING 0xA75643
#define COLOR_GHOST 0x7773D4
#define COLOR_STEEL 0xC4C2DA
#define COLOR_FLYING 0x79A4FF
#define COLOR_ELECTRIC 0xFCE53F
#define COLOR_FAIRY 0xF8ADFF

typedef enum {
  WIFI_OFF,
  WIFI_ON
} Menu_Event_t;

class Display
{
  private:
    TaskHandle_t lvgl_task_handle;

    Arduino_ESP32RGBPanel *bus;
    Arduino_RPi_DPI_RGBPanel *gfx;

    TAMC_GT911 *ts;
    int touch_last_x = 0, touch_last_y = 0;

    void initLVGL();
    typedef void (*FuncPtrInt)(Menu_Event_t, void *);

    lv_obj_t *ui_Main_Screen;
    lv_obj_t *ui_TopPanel;
    lv_obj_t *ui_TimeLabel;
    lv_obj_t *ui_Titleimg;
    lv_obj_t *ui_WiFiLabel;
    lv_obj_t *ui_DateLabel;
    lv_obj_t *ui_Content;
    lv_obj_t *ui_gen_roller;
    lv_obj_t *ui_pkm_sel;
    lv_obj_t *ui_list_pkm;
    lv_obj_t *ui_btn_next_page;
    lv_obj_t *ui_btn_prev_page;
    lv_obj_t *ui_page_label;
    lv_obj_t *ui_BasePopup;
    lv_obj_t *ui_BasePopupTitle;
    lv_obj_t *ui_BasePopupMsg;
    lv_obj_t *ui_BasePopupCloseBtn;
    lv_obj_t *ui_Loading;
    lv_obj_t *ui_pkm_data;
    lv_obj_t *ui_pkm_title;
    lv_obj_t *ui_pkm_img;
    lv_obj_t *ui_pkm_genus;
    lv_obj_t *ui_pkm_types;
    lv_obj_t *ui_pkm_desc;
    lv_obj_t *ui_pkm_size;
    lv_obj_t *ui_pkm_hp_value;
    lv_obj_t *ui_pkm_atk_value;
    lv_obj_t *ui_pkm_def_value;
    lv_obj_t *ui_pkm_spe_atk_value;
    lv_obj_t *ui_pkm_spe_def_value;
    lv_obj_t *ui_pkm_spd_value;
    lv_obj_t *ui_pkm_bar_hp;
    lv_obj_t *ui_pkm_bar_atk;
    lv_obj_t *ui_pkm_bar_def;
    lv_obj_t *ui_pkm_bar_spe_atk;
    lv_obj_t *ui_pkm_bar_spe_def;
    lv_obj_t *ui_pkm_bar_spd;
    lv_obj_t *ui_pkm_height;
    lv_obj_t *ui_pkm_weight;
    lv_obj_t *ui_btn_type1;
    lv_obj_t *ui_btn_type2;
    lv_obj_t *ui_pkm_type1;    
    lv_obj_t *ui_pkm_shadow_type1;
    lv_obj_t *ui_pkm_type2;    
    lv_obj_t *ui_pkm_shadow_type2;

    lv_obj_t *ui_WiFiPanel;
    lv_obj_t *ui_wifi_switch;
    lv_obj_t *ui_WiFiPanelCloseBtn;
    lv_obj_t *ui_wifi_status_label;
    lv_obj_t *ui_WiFiList;
    lv_obj_t *ui_WiFiMBox;
    lv_obj_t *ui_WiFiMBoxTitle;
    lv_obj_t *ui_WiFiMBoxPassword;
    lv_obj_t *ui_WiFiMBoxConnectBtn;
    lv_obj_t *ui_WiFiMBoxCloseBtn;
    lv_obj_t *ui_Focused_Obj;
    lv_obj_t *ui_keyboard;
    lv_obj_t *ui_WiFiIPLabel;

    int page = 0;
    int n_elem = 9;
    int n_pages = 0;
    int number_pkm = 0;
    int pkm_size;
    void init_pkm();
    std::vector<String> pkm_per_page();
    String get_pkm_name(int number);

    void ui_main();
    void ui_wifi_page();
    void ui_prep_popup_box();
    void ui_prep_loading();

  public:
    FuncPtrInt menu_event_cb;
    SemaphoreHandle_t bin_sem;
    fs::FS *storage;

    void show_loading_popup(bool isOn);
    void ui_popup_open(String title, String msg);

    void ui_event_callback(lv_event_t *e);
    void ui_wifi_event_callback(lv_event_t *e);
    void textarea_event_callback(lv_event_t *e);
    void update_pkm_list();
    void update_pkm_data();
    void update_pkm_type(String type1, String type2);
    int get_color_type(String type);
    void update_ui_network(void *data1, void *data2);
    void update_WiFi_label(void *data1);
    void update_time(void *timeStruct);

    void init_tft();
    void init_ts();
    bool touch_has_signal();
    bool touch_touched();
    bool touch_released();

    int get_display_width();
    int get_display_height();

    void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
    void my_touch_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

    void lv_port_sem_take(void);
    void lv_port_sem_give(void);

    DynamicJsonDocument *doc;

    Display(FuncPtrInt callback, fs::FS &sd);
    ~Display();
};