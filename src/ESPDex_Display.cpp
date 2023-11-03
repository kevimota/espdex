#include "ESPDex_Display.hpp"

static Display *instance = NULL;
LV_FONT_DECLARE(ui_arone16);
LV_FONT_DECLARE(ui_arone18);
LV_FONT_DECLARE(ui_arone24);

String readFile(fs::FS &fs, const char* path) {
  File file = fs.open(path, FILE_READ);
  if (!file) {

    file.close();
    return "";
  }
  String temp = "";
  while (file.available()) {
    temp += file.readStringUntil('\n');
  }

  file.close();
  return temp;
}

static void *fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode)
{
  esp_task_wdt_reset();
  const char *flags = "";

  if (mode == LV_FS_MODE_WR)
    flags = FILE_WRITE;
  else if (mode == LV_FS_MODE_RD)
    flags = FILE_READ;
  else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
    flags = FILE_WRITE;

  File f = instance->storage->open(path, flags);
  if (!f) {
    Serial.println("Failed to open file!");
    return NULL;
  }

  File *lf = new File{ f };

  //make sure at the beginning
  //fp->seek(0);

  return (void *)lf;
}
/**
 * Close an opened file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p)
{
  esp_task_wdt_reset();
  File *fp = (File *)file_p;

  fp->close();

  delete (fp); // when close
  return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable.
 * @param buf pointer to a memory block where to store the read data
 * @param btr number of Bytes To Read
 * @param br the real number of read bytes (Byte Read)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br)
{
  esp_task_wdt_reset();
  File *fp = (File *)file_p;

  *br = fp->read((uint8_t *)buf, btr);

  return (int32_t)(*br) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open )
 * @param pos the new position of read write pointer
 * @param whence only LV_SEEK_SET is supported
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence)
{
  esp_task_wdt_reset();
  File *fp = (File *)file_p;

  SeekMode mode;
  if (whence == LV_FS_SEEK_SET)
    mode = SeekSet;
  else if (whence == LV_FS_SEEK_CUR)
    mode = SeekCur;
  else if (whence == LV_FS_SEEK_END)
    mode = SeekEnd;

  fp->seek(pos, mode);

  return LV_FS_RES_OK;
}

/**
 * Give the position of the read write pointer
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable.
 * @param pos_p pointer to to store the result
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p)
{
  esp_task_wdt_reset();
  File *fp = (File *)file_p;

  *pos_p = (uint32_t)fp->position();

  return LV_FS_RES_OK;
}

Display::Display(FuncPtrInt callback, fs::FS &sd)
{
  instance = this;
  storage = &sd;
  init_pkm();

  ts = new TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));
  init_ts();

  bus = new Arduino_ESP32RGBPanel(
      GFX_NOT_DEFINED, GFX_NOT_DEFINED, GFX_NOT_DEFINED,
      TFT_DE, TFT_VSYNC, TFT_HSYNC, TFT_PCLK,
      TFT_R0, TFT_R1, TFT_R2, TFT_R3, TFT_R4,
      TFT_G0, TFT_G1, TFT_G2, TFT_G3, TFT_G4, TFT_G5,
      TFT_B0, TFT_B1, TFT_B2, TFT_B3, TFT_B4);

  gfx = new Arduino_RPi_DPI_RGBPanel(
      bus,
      TFT_WIDTH, TFT_HSYNC_POL, TFT_HSYNC_FRONT, TFT_HSYNC_PULSE, TFT_HSYNC_BACK,
      TFT_HEIGHT, TFT_VSYNC_POL, TFT_VSYNC_FRONT, TFT_VSYNC_PULSE, TFT_VSYNC_BACK,
      TFT_PCLK_NEG, TFT_SPEED_PREF, TFT_AUTO_FLUSH);
  init_tft();
  menu_event_cb = callback;

}

Display::~Display()
{
  delete ts;
  delete bus;
  delete gfx;
}

void Display::init_pkm() {
  doc = new DynamicJsonDocument(35000);
  String pkm_list = readFile(*storage, "/pkm_list.json");
  deserializeJson(*doc, pkm_list.c_str());
  JsonArray pkm_array = doc->as<JsonArray>();
  pkm_size = pkm_array.size();
  
  n_pages = pkm_size/n_elem;
  if (pkm_size % n_elem != 0) n_pages += 1;

  log_i("Pkm size: %d", pkm_size);
  log_i("Number of pages: %d", n_pages);
  
}

std::vector<String> Display::pkm_per_page()
{
  JsonArray pkm_array = doc->as<JsonArray>();
  int s = n_elem * page;

  std::vector<String> result;
  for (int i = s; i < s + n_elem; i++)
  {
    if (i >= pkm_size)
      break;
    else {
      String name = pkm_array[i].as<String>();
      name[4] = ' ';
      name.replace("_", ":");
      log_i("%s", name.c_str());
      result.push_back(name);
    }
  }

  return result;
}

String Display::get_pkm_name(int number)
{
  JsonArray pkm_array = doc->as<JsonArray>();
  if (number < 0 || number >= pkm_size)
  {
    log_i("Invalid pkm number: %d", number);
    return "";
  }
  else
  {
    String pkm = pkm_array[number].as<String>();
    pkm = pkm.substring(5);
    log_i("Pkm number %d: %s", number, pkm.c_str());
    return pkm;
  }
}

void Display::init_tft()
{
  gfx->begin();
  gfx->fillScreen(BLACK);
  this->initLVGL();
}

void Display::init_ts()
{
  ts->begin();
  ts->setRotation(TOUCH_GT911_ROTATION);
}

bool Display::touch_has_signal()
{
  return true;
}

bool Display::touch_touched()
{
  ts->read();
  if (ts->isTouched)
  {
    touch_last_x = map(ts->points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y = map(ts->points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
    return true;
  }
  else
  {
    return false;
  }
}

bool Display::touch_released()
{
  return true;
}

void Display::my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

void Display::my_touch_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

extern "C" void my_disp_flush_thunk(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
  instance->my_disp_flush(drv, area, color_p);
}

extern "C" void my_touch_read_thunk(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  instance->my_touch_read(indev_driver, data);
}

extern "C" void ui_event_callback_thunk(lv_event_t *e)
{
  instance->ui_event_callback(e);
}

extern "C" void ui_wifi_event_callback_thunk(lv_event_t *e)
{
  instance->ui_wifi_event_callback(e);
}

extern "C" void textarea_event_callback_thunk(lv_event_t *e) {
  instance->textarea_event_callback(e);
}

void update_ui_task(void *pvParameters)
{
  while (1)
  {
    xSemaphoreTake(instance->bin_sem, portMAX_DELAY);
    lv_timer_handler();
    xSemaphoreGive(instance->bin_sem);
    vTaskDelay(5);
  }
}

void Display::initLVGL()
{
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t *disp_draw_buf;
  static uint32_t screenWidth = this->get_display_width();
  static uint32_t screenHeight = this->get_display_height();

  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  lv_init();

  lv_group_set_default(lv_group_create());
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 4);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  disp_drv.hor_res = TFT_WIDTH;
  disp_drv.ver_res = TFT_HEIGHT;
  disp_drv.flush_cb = my_disp_flush_thunk;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touch_read_thunk;
  lv_indev_drv_register(&indev_drv);

  static lv_fs_drv_t fs_drv; /*Needs to be static or global*/
  lv_fs_drv_init(&fs_drv);   /*Basic initialization*/

  fs_drv.letter = 'S';   /*An uppercase letter to identify the drive */
  fs_drv.cache_size = 0; /*Cache size for reading in bytes. 0 to not cache.*/

  fs_drv.open_cb = fs_open;
  fs_drv.close_cb = fs_close;
  fs_drv.read_cb = fs_read;
  //fs_drv.write_cb = fs_write;
  fs_drv.seek_cb = fs_seek;
  fs_drv.tell_cb = fs_tell;

  /* fs_drv.dir_close_cb = fs_dir_close;
  fs_drv.dir_open_cb = fs_dir_open;
  fs_drv.dir_read_cb = fs_dir_read; */

  lv_fs_drv_register(&fs_drv); /*Finally register the drive*/

  lv_disp_t *dispp = lv_disp_get_default();
  lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_DEEP_PURPLE), lv_palette_main(LV_PALETTE_TEAL), true, &ui_arone16);
  lv_disp_set_theme(dispp, theme);

  bin_sem = xSemaphoreCreateMutex();
  ui_main();
  ts->reset();
  ui_prep_popup_box();
  ts->reset();
  ui_prep_loading();
  ts->reset();
  xTaskCreatePinnedToCore(update_ui_task,
                          "update_ui_task",
                          15000,
                          NULL,
                          5,
                          &lvgl_task_handle,
                          0);

  
  update_pkm_data();
}

void Display::ui_main()
{
  ui_Main_Screen = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_Main_Screen, LV_OBJ_FLAG_SCROLLABLE);

  ui_TopPanel = lv_obj_create(ui_Main_Screen);
  lv_obj_set_width(ui_TopPanel, 800);
  lv_obj_set_height(ui_TopPanel, 45);
  lv_obj_set_align(ui_TopPanel, LV_ALIGN_TOP_MID);
  lv_obj_clear_flag(ui_TopPanel, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_TopPanel, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(ui_TopPanel, 1, LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_BOTTOM);
  lv_obj_set_style_border_color(ui_TopPanel, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_TopPanel, ui_event_callback_thunk, LV_EVENT_CLICKED, NULL);

  ui_WiFiLabel = lv_label_create(ui_TopPanel);
  lv_obj_set_width(ui_WiFiLabel, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_WiFiLabel, LV_SIZE_CONTENT);
  lv_obj_set_x(ui_WiFiLabel, -10);
  lv_obj_set_y(ui_WiFiLabel, 0);
  lv_obj_set_align(ui_WiFiLabel, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_WiFiLabel, LV_SYMBOL_WARNING);
  lv_obj_set_style_text_color(ui_WiFiLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_WiFiLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_WiFiLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_WiFiIPLabel = lv_label_create(ui_TopPanel);
  lv_obj_set_width(ui_WiFiIPLabel, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_WiFiIPLabel, LV_SIZE_CONTENT);
  lv_obj_set_x(ui_WiFiIPLabel, 25);
  lv_obj_set_y(ui_WiFiIPLabel, 0);
  lv_obj_set_align(ui_WiFiIPLabel, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_WiFiIPLabel, "");
  lv_obj_set_style_text_font(ui_WiFiIPLabel, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  LV_IMG_DECLARE(ESPDex_title);
  ui_Titleimg = lv_img_create(ui_TopPanel);
  lv_img_set_zoom(ui_Titleimg, 160);
  lv_img_set_src(ui_Titleimg, &ESPDex_title);
  lv_obj_set_align(ui_Titleimg, LV_ALIGN_CENTER);

  ui_TimeLabel = lv_label_create(ui_TopPanel);
  lv_obj_set_width(ui_TimeLabel, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_TimeLabel, LV_SIZE_CONTENT);
  lv_obj_set_x(ui_TimeLabel, 10);
  lv_obj_set_y(ui_TimeLabel, 0);
  lv_obj_set_align(ui_TimeLabel, LV_ALIGN_BOTTOM_RIGHT);
  lv_label_set_text(ui_TimeLabel, "");
  lv_obj_set_style_text_color(ui_TimeLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_TimeLabel, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_DateLabel = lv_label_create(ui_TopPanel);
  lv_obj_set_width(ui_DateLabel, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_DateLabel, LV_SIZE_CONTENT);
  lv_obj_set_x(ui_DateLabel, 10);
  lv_obj_set_y(ui_DateLabel, 0);
  lv_obj_set_align(ui_DateLabel, LV_ALIGN_TOP_RIGHT);
  lv_label_set_text(ui_DateLabel, "");
  lv_obj_set_style_text_color(ui_DateLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_DateLabel, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_Content = lv_obj_create(ui_Main_Screen);
  lv_obj_set_width(ui_Content, 800);
  lv_obj_set_height(ui_Content, 480 - 50);
  lv_obj_set_align(ui_Content, LV_ALIGN_BOTTOM_MID);
  lv_obj_clear_flag(ui_Content, LV_OBJ_FLAG_SCROLLABLE);

  ui_list_pkm = lv_list_create(ui_Content);
  lv_obj_set_width(ui_list_pkm, 280);
  lv_obj_set_height(ui_list_pkm, 370);
  lv_obj_set_y(ui_list_pkm, -20);
  lv_obj_set_align(ui_list_pkm, LV_ALIGN_TOP_RIGHT);
  lv_obj_set_style_text_align(ui_list_pkm, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_clear_flag(ui_list_pkm, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_text_font(ui_list_pkm, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  update_pkm_list();

  ui_btn_next_page = lv_btn_create(ui_Main_Screen);
  lv_obj_set_width(ui_btn_next_page, 90);
  lv_obj_set_height(ui_btn_next_page, 40);
  lv_obj_set_x(ui_btn_next_page, -20);
  lv_obj_set_y(ui_btn_next_page, -10);
  lv_obj_set_align(ui_btn_next_page, LV_ALIGN_BOTTOM_RIGHT);
  lv_obj_add_event_cb(ui_btn_next_page, ui_event_callback_thunk, LV_EVENT_CLICKED, NULL);

  lv_obj_t *ui_btn_next_label = lv_label_create(ui_btn_next_page);
  lv_obj_set_width(ui_btn_next_label, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_btn_next_label, LV_SIZE_CONTENT);
  lv_obj_set_align(ui_btn_next_label, LV_ALIGN_CENTER);
  lv_label_set_text(ui_btn_next_label, "Next");
  lv_obj_set_style_text_font(ui_btn_next_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_btn_prev_page = lv_btn_create(ui_Main_Screen);
  lv_obj_set_x(ui_btn_prev_page, -210);
  lv_obj_set_y(ui_btn_prev_page, -10);
  lv_obj_set_width(ui_btn_prev_page, 90);
  lv_obj_set_height(ui_btn_prev_page, 40);
  lv_obj_set_align(ui_btn_prev_page, LV_ALIGN_BOTTOM_RIGHT);
  lv_obj_add_event_cb(ui_btn_prev_page, ui_event_callback_thunk, LV_EVENT_CLICKED, NULL);

  lv_obj_t *ui_btn_prev_label = lv_label_create(ui_btn_prev_page);
  lv_obj_set_width(ui_btn_prev_label, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_btn_prev_label, LV_SIZE_CONTENT);
  lv_obj_set_align(ui_btn_prev_label, LV_ALIGN_CENTER);
  lv_label_set_text(ui_btn_prev_label, "Prev");
  lv_obj_set_style_text_font(ui_btn_prev_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_page_label = lv_label_create(ui_Main_Screen);
  lv_obj_set_width(ui_page_label, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_page_label, LV_SIZE_CONTENT);
  lv_obj_set_x(ui_page_label, -125);
  lv_obj_set_y(ui_page_label, -20);
  lv_obj_set_align(ui_page_label, LV_ALIGN_BOTTOM_RIGHT);
  lv_label_set_text_fmt(ui_page_label, "%03d / %03d", page + 1, n_pages);
  lv_obj_set_style_text_font(ui_page_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_data = lv_obj_create(ui_Content);
  lv_obj_set_width(ui_pkm_data, 490);
  lv_obj_set_height(ui_pkm_data, 480 - 50);
  lv_obj_set_x(ui_pkm_data, -20);
  lv_obj_set_y(ui_pkm_data, 20);
  lv_obj_set_align(ui_pkm_data, LV_ALIGN_BOTTOM_LEFT);
  lv_obj_set_flex_flow(ui_pkm_data, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(ui_pkm_data,  LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  ui_pkm_title = lv_label_create(ui_pkm_data);
  lv_label_set_text(ui_pkm_title, "");
  lv_obj_set_style_text_font(ui_pkm_title, &ui_arone24, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_genus = lv_label_create(ui_pkm_data);
  lv_label_set_text(ui_pkm_genus, "");
  lv_obj_set_style_text_font(ui_pkm_genus, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  static lv_style_t style_container;
  lv_style_init(&style_container);
  lv_style_set_border_side(&style_container, LV_BORDER_SIDE_NONE);
  lv_style_set_border_opa(&style_container, LV_OPA_TRANSP);
  lv_style_set_border_width(&style_container, 0);
  lv_style_set_outline_width(&style_container, 0);

  static lv_obj_t *pkm_img_container = lv_obj_create(ui_pkm_data);
  lv_obj_add_style(pkm_img_container, &style_container, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(pkm_img_container, lv_pct(100));
  lv_obj_set_height(pkm_img_container, LV_SIZE_CONTENT);

  ui_pkm_img = lv_img_create(pkm_img_container);
  lv_obj_center(ui_pkm_img);

  ui_pkm_height = lv_label_create(pkm_img_container);
  lv_obj_align(ui_pkm_height, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_set_width(ui_pkm_height, lv_pct(25));
  lv_label_set_text(ui_pkm_height, "");
  lv_obj_set_style_text_align(ui_pkm_height, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_set_style_text_font(ui_pkm_height, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_weight = lv_label_create(pkm_img_container);
  lv_obj_align(ui_pkm_weight, LV_ALIGN_TOP_RIGHT, 0, 20);
  lv_obj_set_width(ui_pkm_weight, lv_pct(25));
  lv_label_set_text(ui_pkm_weight, "");
  lv_obj_set_style_text_align(ui_pkm_weight, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_set_style_text_font(ui_pkm_weight, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_btn_type1 = lv_btn_create(pkm_img_container);
  lv_obj_clear_flag(ui_btn_type1, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_set_height(ui_btn_type1, 35);
  lv_obj_set_width(ui_btn_type1, lv_pct(25));
  lv_obj_set_style_border_width(ui_btn_type1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_btn_type1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_btn_type1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_align(ui_btn_type1, LV_ALIGN_RIGHT_MID, 0, -20);

  ui_btn_type2 = lv_btn_create(pkm_img_container);
  lv_obj_clear_flag(ui_btn_type2, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_set_height(ui_btn_type2, 35);
  lv_obj_set_width(ui_btn_type2, lv_pct(25));
  lv_obj_set_style_border_width(ui_btn_type2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_btn_type2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_btn_type2, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_align(ui_btn_type2, LV_ALIGN_RIGHT_MID, 0, 20);

  ui_pkm_shadow_type1 = lv_label_create(ui_btn_type1);
  ui_pkm_shadow_type2 = lv_label_create(ui_btn_type2);
  
  ui_pkm_type1 = lv_label_create(ui_btn_type1);
  lv_label_set_text(ui_pkm_type1, "");
  lv_obj_center(ui_pkm_type1);
  lv_obj_set_style_text_font(ui_pkm_type1, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_type2 = lv_label_create(ui_btn_type2);
  lv_label_set_text(ui_pkm_type2, "");
  lv_obj_center(ui_pkm_type2);
  lv_obj_set_style_text_font(ui_pkm_type2, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);
  
  lv_label_set_text(ui_pkm_shadow_type1, "");
  lv_obj_set_style_text_font(ui_pkm_shadow_type1, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_pkm_shadow_type1, LV_OPA_70, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_pkm_shadow_type1, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_label_set_text(ui_pkm_shadow_type2, "");
  lv_obj_set_style_text_font(ui_pkm_shadow_type2, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_pkm_shadow_type2, LV_OPA_70, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_pkm_shadow_type2, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);
  
  ui_pkm_desc = lv_label_create(ui_pkm_data);
  lv_obj_set_width(ui_pkm_desc, lv_pct(90));
  lv_obj_set_height(ui_pkm_desc, LV_SIZE_CONTENT);
  lv_obj_set_style_text_align(ui_pkm_desc, LV_TEXT_ALIGN_CENTER, 0);  
  lv_label_set_text(ui_pkm_desc, "");
  lv_obj_set_style_text_font(ui_pkm_desc, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *label_bs = lv_label_create(ui_pkm_data);
  lv_label_set_text(label_bs, "Base Stats");
  lv_obj_set_style_text_font(label_bs, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *base_hp_obj = lv_obj_create(ui_pkm_data);
  lv_obj_add_style(base_hp_obj, &style_container, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(base_hp_obj, lv_pct(95));
  lv_obj_set_height(base_hp_obj, LV_SIZE_CONTENT);

  static lv_style_t style_bar_hp;
  lv_style_init(&style_bar_hp);
  lv_style_set_bg_opa(&style_bar_hp, LV_OPA_COVER);
  lv_style_set_bg_color(&style_bar_hp, lv_palette_main(LV_PALETTE_RED));
  ui_pkm_bar_hp = lv_bar_create(base_hp_obj);
  lv_bar_set_range(ui_pkm_bar_hp, 0, 255);
  lv_obj_add_style(ui_pkm_bar_hp, &style_bar_hp, LV_PART_INDICATOR);
  lv_obj_align(ui_pkm_bar_hp, LV_ALIGN_BOTTOM_MID, 0, 0);

  static lv_obj_t *hp_label = lv_label_create(base_hp_obj);
  lv_obj_set_width(hp_label, LV_SIZE_CONTENT);
  lv_obj_set_height(hp_label, LV_SIZE_CONTENT);
  lv_label_set_text(hp_label, "HP");
  lv_obj_align_to(hp_label, ui_pkm_bar_hp, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_font(hp_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_hp_value = lv_label_create(base_hp_obj);
  lv_obj_set_width(ui_pkm_hp_value, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_pkm_hp_value, LV_SIZE_CONTENT);
  lv_label_set_text(ui_pkm_hp_value, "");
  lv_obj_align_to(ui_pkm_hp_value, ui_pkm_bar_hp, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
  lv_obj_set_style_text_font(ui_pkm_hp_value, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *base_atk_obj = lv_obj_create(ui_pkm_data);
  lv_obj_add_style(base_atk_obj, &style_container, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(base_atk_obj, lv_pct(95));
  lv_obj_set_height(base_atk_obj, LV_SIZE_CONTENT);

  static lv_style_t style_bar_atk;
  lv_style_init(&style_bar_atk);
  lv_style_set_bg_opa(&style_bar_atk, LV_OPA_COVER);
  lv_style_set_bg_color(&style_bar_atk, lv_palette_main(LV_PALETTE_ORANGE));
  ui_pkm_bar_atk = lv_bar_create(base_atk_obj);
  lv_bar_set_range(ui_pkm_bar_atk, 0, 255);
  lv_obj_add_style(ui_pkm_bar_atk, &style_bar_atk, LV_PART_INDICATOR);
  lv_obj_center(ui_pkm_bar_atk);

  static lv_obj_t *atk_label = lv_label_create(base_atk_obj);
  lv_obj_set_width(atk_label, LV_SIZE_CONTENT);
  lv_obj_set_height(atk_label, LV_SIZE_CONTENT);
  lv_label_set_text(atk_label, "Attack");
  lv_obj_align_to(atk_label, ui_pkm_bar_atk, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_font(atk_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_atk_value = lv_label_create(base_atk_obj);
  lv_obj_set_width(ui_pkm_atk_value, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_pkm_atk_value, LV_SIZE_CONTENT);
  lv_label_set_text(ui_pkm_atk_value, "");
  lv_obj_align_to(ui_pkm_atk_value, ui_pkm_bar_atk, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
  lv_obj_set_style_text_font(ui_pkm_atk_value, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *base_def_obj = lv_obj_create(ui_pkm_data);
  lv_obj_add_style(base_def_obj, &style_container, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(base_def_obj, lv_pct(95));
  lv_obj_set_height(base_def_obj, LV_SIZE_CONTENT);

  static lv_style_t style_bar_def;
  lv_style_init(&style_bar_def);
  lv_style_set_bg_opa(&style_bar_def, LV_OPA_COVER);
  lv_style_set_bg_color(&style_bar_def, lv_palette_main(LV_PALETTE_YELLOW));
  ui_pkm_bar_def = lv_bar_create(base_def_obj);
  lv_bar_set_range(ui_pkm_bar_def, 0, 255);
  lv_obj_add_style(ui_pkm_bar_def, &style_bar_def, LV_PART_INDICATOR);
  lv_obj_center(ui_pkm_bar_def);

  static lv_obj_t *def_label = lv_label_create(base_def_obj);
  lv_obj_set_width(def_label, LV_SIZE_CONTENT);
  lv_obj_set_height(def_label, LV_SIZE_CONTENT);
  lv_label_set_text(def_label, "Defense");
  lv_obj_align_to(def_label, ui_pkm_bar_def, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_font(def_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_def_value = lv_label_create(base_def_obj);
  lv_obj_set_width(ui_pkm_def_value, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_pkm_def_value, LV_SIZE_CONTENT);
  lv_label_set_text(ui_pkm_def_value, "");
  lv_obj_align_to(ui_pkm_def_value, ui_pkm_bar_def, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
  lv_obj_set_style_text_font(ui_pkm_def_value, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *base_spe_atk_obj = lv_obj_create(ui_pkm_data);
  lv_obj_add_style(base_spe_atk_obj, &style_container, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(base_spe_atk_obj, lv_pct(95));
  lv_obj_set_height(base_spe_atk_obj, LV_SIZE_CONTENT);

  static lv_style_t style_bar_spe_atk;
  lv_style_init(&style_bar_spe_atk);
  lv_style_set_bg_opa(&style_bar_spe_atk, LV_OPA_COVER);
  lv_style_set_bg_color(&style_bar_spe_atk, lv_palette_main(LV_PALETTE_BLUE));
  ui_pkm_bar_spe_atk = lv_bar_create(base_spe_atk_obj);
  lv_bar_set_range(ui_pkm_bar_spe_atk, 0, 255);
  lv_obj_add_style(ui_pkm_bar_spe_atk, &style_bar_spe_atk, LV_PART_INDICATOR);
  lv_obj_center(ui_pkm_bar_spe_atk);

  static lv_obj_t *spe_atk_label = lv_label_create(base_spe_atk_obj);
  lv_obj_set_width(spe_atk_label, LV_SIZE_CONTENT);
  lv_obj_set_height(spe_atk_label, LV_SIZE_CONTENT);
  lv_label_set_text(spe_atk_label, "Sp. Attack");
  lv_obj_align_to(spe_atk_label, ui_pkm_bar_spe_atk, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_font(spe_atk_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_spe_atk_value = lv_label_create(base_spe_atk_obj);
  lv_obj_set_width(ui_pkm_spe_atk_value, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_pkm_spe_atk_value, LV_SIZE_CONTENT);
  lv_label_set_text(ui_pkm_spe_atk_value, "");
  lv_obj_align_to(ui_pkm_spe_atk_value, ui_pkm_bar_spe_atk, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
  lv_obj_set_style_text_font(ui_pkm_spe_atk_value, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *base_spe_def_obj = lv_obj_create(ui_pkm_data);
  lv_obj_add_style(base_spe_def_obj, &style_container, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(base_spe_def_obj, lv_pct(95));
  lv_obj_set_height(base_spe_def_obj, LV_SIZE_CONTENT);

  static lv_style_t style_bar_spe_def;
  lv_style_init(&style_bar_spe_def);
  lv_style_set_bg_opa(&style_bar_spe_def, LV_OPA_COVER);
  lv_style_set_bg_color(&style_bar_spe_def, lv_palette_main(LV_PALETTE_GREEN));
  ui_pkm_bar_spe_def = lv_bar_create(base_spe_def_obj);
  lv_bar_set_range(ui_pkm_bar_spe_def, 0, 255);
  lv_obj_add_style(ui_pkm_bar_spe_def, &style_bar_spe_def, LV_PART_INDICATOR);
  lv_obj_center(ui_pkm_bar_spe_def);

  static lv_obj_t *spe_def_label = lv_label_create(base_spe_def_obj);
  lv_obj_set_width(spe_def_label, LV_SIZE_CONTENT);
  lv_obj_set_height(spe_def_label, LV_SIZE_CONTENT);
  lv_label_set_text(spe_def_label, "Sp. Defense");
  lv_obj_align_to(spe_def_label, ui_pkm_bar_spe_def, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_font(spe_def_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_spe_def_value = lv_label_create(base_spe_def_obj);
  lv_obj_set_width(ui_pkm_spe_def_value, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_pkm_spe_def_value, LV_SIZE_CONTENT);
  lv_label_set_text(ui_pkm_spe_def_value, "");
  lv_obj_align_to(ui_pkm_spe_def_value, ui_pkm_bar_spe_def, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
  lv_obj_set_style_text_font(ui_pkm_spe_def_value, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *base_spd_obj = lv_obj_create(ui_pkm_data);
  lv_obj_add_style(base_spd_obj, &style_container, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(base_spd_obj, lv_pct(95));
  lv_obj_set_height(base_spd_obj, LV_SIZE_CONTENT);

  static lv_style_t style_bar_spd;
  lv_style_init(&style_bar_spd);
  lv_style_set_bg_opa(&style_bar_spd, LV_OPA_COVER);
  lv_style_set_bg_color(&style_bar_spd, lv_palette_main(LV_PALETTE_PINK));
  ui_pkm_bar_spd = lv_bar_create(base_spd_obj);
  lv_bar_set_range(ui_pkm_bar_spd, 0, 255);
  lv_obj_add_style(ui_pkm_bar_spd, &style_bar_spd, LV_PART_INDICATOR);
  lv_obj_center(ui_pkm_bar_spd);

  static lv_obj_t *spd_label = lv_label_create(base_spd_obj);
  lv_obj_set_width(spd_label, LV_SIZE_CONTENT);
  lv_obj_set_height(spd_label, LV_SIZE_CONTENT);
  lv_label_set_text(spd_label, "Speed");
  lv_obj_align_to(spd_label, ui_pkm_bar_spd, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_font(spd_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_pkm_spd_value = lv_label_create(base_spd_obj);
  lv_obj_set_width(ui_pkm_spd_value, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_pkm_spd_value, LV_SIZE_CONTENT);
  lv_label_set_text(ui_pkm_spd_value, "");
  lv_obj_align_to(ui_pkm_spd_value, ui_pkm_bar_spd, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
  lv_obj_set_style_text_font(ui_pkm_spd_value, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_wifi_page();

  lv_disp_load_scr(ui_Main_Screen);
}

void Display::ui_prep_popup_box()
{
  ui_BasePopup = lv_obj_create(lv_scr_act());
  lv_obj_set_height(ui_BasePopup, 200);
  lv_obj_set_width(ui_BasePopup, lv_pct(50));
  lv_obj_set_align(ui_BasePopup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_BasePopup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_BasePopup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_BasePopup, 196, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_BasePopupTitle = lv_label_create(ui_BasePopup);
  lv_obj_set_width(ui_BasePopupTitle, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_BasePopupTitle, LV_SIZE_CONTENT);
  lv_label_set_text(ui_BasePopupTitle, "");
  lv_obj_set_style_text_color(ui_BasePopupTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_BasePopupTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_BasePopupTitle, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_BasePopupMsg = lv_label_create(ui_BasePopup);
  lv_obj_set_width(ui_BasePopupMsg, 350);
  lv_obj_set_height(ui_BasePopupMsg, 110);
  lv_obj_set_x(ui_BasePopupMsg, 0);
  lv_obj_set_y(ui_BasePopupMsg, 30);
  lv_label_set_text(ui_BasePopupMsg, "");
  lv_obj_set_align(ui_BasePopupMsg, LV_ALIGN_CENTER);
  lv_obj_set_style_text_color(ui_BasePopupMsg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_BasePopupMsg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_BasePopupMsg, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_BasePopupCloseBtn = lv_btn_create(ui_BasePopup);
  lv_obj_set_width(ui_BasePopupCloseBtn, 50);
  lv_obj_set_height(ui_BasePopupCloseBtn, 34);
  lv_obj_set_align(ui_BasePopupCloseBtn, LV_ALIGN_BOTTOM_RIGHT);
  lv_obj_add_flag(ui_BasePopupCloseBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
  lv_obj_clear_flag(ui_BasePopupCloseBtn, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_shadow_width(ui_BasePopupCloseBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_spread(ui_BasePopupCloseBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_ofs_x(ui_BasePopupCloseBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_ofs_y(ui_BasePopupCloseBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_BasePopupCloseBtn, ui_event_callback_thunk, LV_EVENT_CLICKED, NULL);

  lv_obj_t *ui_BaseOkBtnLabel = lv_label_create(ui_BasePopupCloseBtn);
  lv_obj_set_width(ui_BaseOkBtnLabel, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_BaseOkBtnLabel, LV_SIZE_CONTENT);
  lv_obj_set_align(ui_BaseOkBtnLabel, LV_ALIGN_CENTER);
  lv_label_set_text(ui_BaseOkBtnLabel, "OK");
  lv_obj_set_style_text_font(ui_BaseOkBtnLabel, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_add_flag(ui_BasePopup, LV_OBJ_FLAG_HIDDEN);
  lv_obj_move_background(ui_BasePopup);
  
}

void Display::ui_wifi_page()
{
  ui_WiFiPanel = lv_obj_create(ui_Main_Screen);
  lv_obj_set_size(ui_WiFiPanel, 400, gfx->height() - 80);
  lv_obj_align(ui_WiFiPanel, LV_ALIGN_TOP_LEFT, 10, 50);
  lv_obj_add_flag(ui_WiFiPanel, LV_OBJ_FLAG_HIDDEN);

  ui_wifi_switch = lv_switch_create(ui_WiFiPanel);
  lv_obj_align(ui_wifi_switch, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_add_event_cb(ui_wifi_switch, ui_wifi_event_callback_thunk, LV_EVENT_VALUE_CHANGED, NULL);

  lv_obj_t *ui_WiFiPanelLabel = lv_label_create(ui_WiFiPanel);
  lv_label_set_text(ui_WiFiPanelLabel, "WiFi");
  lv_obj_align(ui_WiFiPanelLabel, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_font(ui_WiFiPanelLabel, &ui_arone24, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_wifi_status_label = lv_label_create(ui_WiFiPanel);
  lv_obj_align(ui_wifi_status_label, LV_ALIGN_TOP_MID, 0, 30);
  lv_label_set_text(ui_wifi_status_label, "WiFi Off.");
  lv_obj_set_style_text_font(ui_wifi_status_label, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_WiFiList = lv_list_create(ui_WiFiPanel);
  lv_obj_align(ui_WiFiList, LV_ALIGN_BOTTOM_LEFT, 0, 0);
  lv_obj_set_height(ui_WiFiList, lv_pct(80));
  lv_obj_set_width(ui_WiFiList, lv_pct(80));
  lv_obj_set_style_text_font(ui_WiFiList, &ui_arone18, LV_PART_MAIN | LV_PART_MAIN);
  lv_obj_add_flag(ui_WiFiList, LV_OBJ_FLAG_HIDDEN);

  ui_WiFiPanelCloseBtn = lv_btn_create(ui_WiFiPanel);
  lv_obj_set_size(ui_WiFiPanelCloseBtn, 50, 40);
  lv_obj_align(ui_WiFiPanelCloseBtn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_add_event_cb(ui_WiFiPanelCloseBtn, ui_wifi_event_callback_thunk, LV_EVENT_CLICKED, NULL);

  lv_obj_t *ui_CloseBtnlabel = lv_label_create(ui_WiFiPanelCloseBtn);
  lv_label_set_text(ui_CloseBtnlabel, "OK");
  lv_obj_set_style_text_font(ui_CloseBtnlabel, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_center(ui_CloseBtnlabel);

  ui_WiFiMBox = lv_obj_create(ui_Main_Screen);
  lv_obj_set_size(ui_WiFiMBox, gfx->width() - 400, gfx->height() - 240);
  lv_obj_align(ui_WiFiMBox, LV_ALIGN_CENTER, 0, -50);
  lv_obj_add_flag(ui_WiFiMBox, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag(ui_WiFiMBox, LV_OBJ_FLAG_CLICK_FOCUSABLE);
  
  ui_WiFiMBoxTitle = lv_label_create(ui_WiFiMBox);
  lv_label_set_text(ui_WiFiMBoxTitle, "Connect to: ");
  lv_obj_set_size(ui_WiFiMBoxTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_align(ui_WiFiMBoxTitle, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_text_font(ui_WiFiMBoxTitle, &ui_arone18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_WiFiMBoxPassword = lv_textarea_create(ui_WiFiMBox);
  lv_textarea_set_cursor_click_pos(ui_WiFiMBoxPassword, false);
  lv_textarea_set_cursor_pos(ui_WiFiMBoxPassword, 0);
  lv_textarea_set_text_selection(ui_WiFiMBoxPassword, false);
  lv_obj_set_size(ui_WiFiMBoxPassword, gfx->width() - 450, 50);
  lv_obj_center(ui_WiFiMBoxPassword);
  lv_textarea_set_password_mode(ui_WiFiMBoxPassword, true);
  lv_textarea_set_placeholder_text(ui_WiFiMBoxPassword, "Password?");
  lv_textarea_set_max_length(ui_WiFiMBoxPassword, 64);
  lv_obj_set_style_text_font(ui_WiFiMBoxPassword, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_WiFiMBoxPassword, textarea_event_callback_thunk, LV_EVENT_FOCUSED, NULL);
  lv_obj_add_event_cb(ui_WiFiMBoxPassword, textarea_event_callback_thunk, LV_EVENT_DEFOCUSED, NULL);

  ui_keyboard = lv_keyboard_create(ui_Main_Screen);
  lv_keyboard_set_textarea(ui_keyboard, NULL);
  lv_obj_add_event_cb(ui_keyboard, ui_wifi_event_callback_thunk, LV_EVENT_READY, NULL);
  lv_obj_add_flag(ui_keyboard, LV_OBJ_FLAG_HIDDEN);

  ui_WiFiMBoxConnectBtn = lv_btn_create(ui_WiFiMBox);
  lv_obj_add_event_cb(ui_WiFiMBoxConnectBtn, ui_wifi_event_callback_thunk, LV_EVENT_CLICKED, NULL);
  lv_obj_align(ui_WiFiMBoxConnectBtn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_t *btnLabel = lv_label_create(ui_WiFiMBoxConnectBtn);
  lv_label_set_text(btnLabel, "Connect");
  lv_obj_center(btnLabel);
  lv_obj_set_style_text_font(btnLabel, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_WiFiMBoxCloseBtn = lv_btn_create(ui_WiFiMBox);
  lv_obj_add_event_cb(ui_WiFiMBoxCloseBtn, ui_wifi_event_callback_thunk, LV_EVENT_ALL, NULL);
  lv_obj_align(ui_WiFiMBoxCloseBtn, LV_ALIGN_BOTTOM_LEFT, 0, 0);
  lv_obj_t *btnLabel2 = lv_label_create(ui_WiFiMBoxCloseBtn);
  lv_label_set_text(btnLabel2, "Cancel");
  lv_obj_center(btnLabel2);
  lv_obj_set_style_text_font(ui_WiFiMBoxCloseBtn, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_add_flag(ui_WiFiMBox, LV_OBJ_FLAG_HIDDEN);
}

void Display::ui_popup_open(String title, String msg)
{
  lv_port_sem_take();
  lv_obj_clear_flag(ui_BasePopup, LV_OBJ_FLAG_HIDDEN);
  lv_obj_move_foreground(ui_BasePopup);
  lv_label_set_text(ui_BasePopupTitle, title.c_str());
  lv_label_set_text(ui_BasePopupMsg, msg.c_str());
  lv_port_sem_give();
}

void Display::ui_prep_loading()
{
  ui_Loading = lv_obj_create(ui_Main_Screen);

  lv_obj_set_size(ui_Loading, 120, 140);
  lv_obj_t *loading_spinner = lv_spinner_create(ui_Loading, 1000, 60);
  lv_obj_set_size(loading_spinner, 80, 80);
  lv_obj_align(loading_spinner, LV_ALIGN_TOP_MID, 0, 0);

  lv_obj_t *loading_label = lv_label_create(ui_Loading);
  lv_label_set_text(loading_label, "Loading...");
  lv_obj_align(loading_label, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_center(ui_Loading);
  lv_obj_set_style_text_font(loading_label, &ui_arone16, LV_PART_MAIN | LV_STATE_DEFAULT);

  this->show_loading_popup(false);
}

void Display::show_loading_popup(bool isOn)
{
  lv_port_sem_take();
  if (isOn)
  {
    lv_obj_move_foreground(ui_Loading);
    lv_obj_clear_flag(ui_Loading, LV_OBJ_FLAG_HIDDEN);
  }
  else
  {
    lv_obj_move_background(ui_Loading);
    lv_obj_add_flag(ui_Loading, LV_OBJ_FLAG_HIDDEN);
  }
  lv_port_sem_give();
}

void Display::update_pkm_list()
{
  std::vector<String> pkm_list = pkm_per_page();
  int size = pkm_list.size();
  lv_obj_clean(ui_list_pkm);
  for (int i = 0; i < size; i++)
  {
    lv_obj_t *btn = lv_list_add_btn(ui_list_pkm, NULL, pkm_list[i].c_str());
    lv_obj_add_event_cb(btn, ui_event_callback_thunk, LV_EVENT_CLICKED, NULL);
    
  }
}

void Display::ui_event_callback(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);

  log_i("Event code: %d", event_code);
  log_i("target: %p", target);

  if (event_code == LV_EVENT_CLICKED)
  {
    if (target == ui_BasePopupCloseBtn)
    {
      lv_obj_add_flag(ui_BasePopup, LV_OBJ_FLAG_HIDDEN);
      lv_obj_move_background(ui_BasePopup);
    }
    else if (target == ui_btn_next_page)
    {
      page++;
      if (page >= n_pages)
      {
        page = n_pages - 1;
        return;
      }
      lv_label_set_text_fmt(ui_page_label, "%03d / %03d", page + 1, n_pages);
      update_pkm_list();
    }
    else if (target == ui_btn_prev_page)
    {
      page--;
      if (page < 0)
      {
        page = 0;
        return;
      }
      lv_label_set_text_fmt(ui_page_label, "%03d / %03d", page + 1, n_pages);
      update_pkm_list();
    }
    else if (target == ui_TopPanel)
    {
      lv_obj_clear_flag(ui_WiFiPanel, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
      String text = lv_list_get_btn_text(ui_list_pkm, target);
      number_pkm = text.substring(0, 4).toInt() - 1;
      update_pkm_data();
    }
  }
}

void Display::ui_wifi_event_callback(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);

  log_i("Event code: %d", event_code);
  log_i("target: %p", target);

  if (event_code == LV_EVENT_CLICKED)
  {
    if (target == ui_WiFiPanelCloseBtn)
    {
      lv_obj_add_flag(ui_WiFiPanel, LV_OBJ_FLAG_HIDDEN);
    }
    else if (target == ui_WiFiMBoxCloseBtn) {
      lv_obj_move_background(ui_WiFiMBox);
      lv_obj_add_flag(ui_WiFiMBox, LV_OBJ_FLAG_HIDDEN);
    }
    else if (target == ui_WiFiMBoxConnectBtn) {
      log_i("Connect to wifi");
      lv_obj_move_background(ui_WiFiMBox);
      lv_obj_add_flag(ui_WiFiMBox, LV_OBJ_FLAG_HIDDEN);
      String ssid = lv_label_get_text(ui_WiFiMBoxTitle);
      ssid = ssid.substring(12);
      String pass = lv_textarea_get_text(ui_WiFiMBoxPassword);
      log_i("ssid = %s", ssid.c_str());
      log_i("pass = %s", pass.c_str());
      String key = ssid + WIFI_SSID_PW_DELIMITER + pass;
      menu_event_cb(WIFI_ON, (void *)key.c_str());
      this->show_loading_popup(true);
      lv_textarea_set_text(ui_WiFiMBoxPassword, "");
    }
    else {
      String ssid = lv_list_get_btn_text(ui_WiFiList, target);
      if (ssid.endsWith(" *")) ssid = ssid.substring(0, ssid.length() - 2);
      log_i("Selected SSID: %s", ssid.c_str());

      lv_label_set_text_fmt(ui_WiFiMBoxTitle, "Connect to: %s", ssid.c_str());
      lv_obj_move_foreground(ui_WiFiMBox);
      lv_obj_clear_flag(ui_WiFiMBox, LV_OBJ_FLAG_HIDDEN);
    }
  }
  else if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    if (target == ui_wifi_switch)
    {
      if (lv_obj_has_state(ui_wifi_switch, LV_STATE_CHECKED))
      {
        // Power on wifi routine
        menu_event_cb(WIFI_ON, NULL);
        lv_label_set_text(ui_wifi_status_label, "WiFi On, Scanning...");
      }
      else
      {
        // Power off wifi routine
        menu_event_cb(WIFI_OFF, NULL);
        lv_label_set_text(ui_wifi_status_label, "WiFi Off");
        update_WiFi_label(NULL);
        lv_obj_add_flag(ui_WiFiList, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_WiFiList, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(ui_WiFiList, LV_OBJ_FLAG_SCROLLABLE);
      }
    }
  }
  else if (event_code == LV_EVENT_READY) {
    lv_obj_add_flag(ui_keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_keyboard_set_textarea(ui_keyboard, NULL);
  }
}

void Display::update_WiFi_label(void *data1) {
  lv_port_sem_take();
  if (data1 != NULL) {
    std::string &s = *(static_cast<std::string *>(data1));
    lv_label_set_text(ui_WiFiLabel, LV_SYMBOL_WIFI);
    lv_label_set_text(ui_WiFiIPLabel, s.c_str());
    lv_obj_add_flag(ui_WiFiPanel, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_label_set_text(ui_WiFiLabel, LV_SYMBOL_WARNING);
    lv_label_set_text(ui_WiFiIPLabel, "");
  }
  lv_port_sem_give();
}

void Display::update_pkm_data()
{
  lv_port_sem_take();
  esp_task_wdt_reset();
  JsonArray pkm_array = doc->as<JsonArray>();
  String entry_path = "/pkm_entries/" + pkm_array[number_pkm].as<String>() + ".json";
  String sprite_path = "S:/sprites/" + pkm_array[number_pkm].as<String>() + ".bin";
  String entry = readFile(*storage, entry_path.c_str());
  esp_task_wdt_reset();

  DynamicJsonDocument pkm_entry(1024);

  deserializeJson(pkm_entry, entry);
  String name = pkm_entry["name"];
  String genus = pkm_entry["genus"];
  String desc = pkm_entry["desc"];
  uint32_t hp = pkm_entry["hp"];
  uint32_t atk = pkm_entry["attack"];
  uint32_t def = pkm_entry["defense"];
  uint32_t spe_atk = pkm_entry["special-attack"];
  uint32_t spe_def = pkm_entry["special-defense"];
  uint32_t spd = pkm_entry["speed"];
  uint32_t weight_dm = pkm_entry["weight"];
  uint32_t height_dm = pkm_entry["height"];

  float weight = (float) weight_dm/10.;
  float height = (float) height_dm/10.;

  String type1;
  String type2;

  JsonArray types = pkm_entry["types"].as<JsonArray>();
  type1 = types[0].as<String>();
  if (types.size() > 1) {
    type2 = types[1].as<String>();
  }

  log_i("%s", name.c_str());
  log_i("type1: %s, type2: %s", type1.c_str(), type2.c_str());

  esp_task_wdt_reset();
  lv_img_set_src(ui_pkm_img, NULL);

  lv_label_set_text(ui_pkm_title, name.c_str());
  lv_label_set_text(ui_pkm_genus, genus.c_str());
  lv_label_set_text(ui_pkm_desc, desc.c_str());

  lv_bar_set_value(ui_pkm_bar_hp, hp, LV_ANIM_OFF);
  lv_label_set_text_fmt(ui_pkm_hp_value, "%d", hp);

  lv_bar_set_value(ui_pkm_bar_atk, atk, LV_ANIM_OFF);
  lv_label_set_text_fmt(ui_pkm_atk_value, "%d", atk);

  lv_bar_set_value(ui_pkm_bar_def, def, LV_ANIM_OFF);
  lv_label_set_text_fmt(ui_pkm_def_value, "%d", def);

  lv_bar_set_value(ui_pkm_bar_spe_atk, spe_atk, LV_ANIM_OFF);
  lv_label_set_text_fmt(ui_pkm_spe_atk_value, "%d", spe_atk);

  lv_bar_set_value(ui_pkm_bar_spe_def, spe_def, LV_ANIM_OFF);
  lv_label_set_text_fmt(ui_pkm_spe_def_value, "%d", spe_def);

  lv_bar_set_value(ui_pkm_bar_spd, spd, LV_ANIM_OFF);
  lv_label_set_text_fmt(ui_pkm_spd_value, "%d", spd);

  lv_label_set_text_fmt(ui_pkm_height, "H: %.1f m", height);
  lv_label_set_text_fmt(ui_pkm_weight, "W: %.1f kg", weight);

  update_pkm_type(type1, type2);
  esp_task_wdt_reset();

  lv_img_set_src(ui_pkm_img, sprite_path.c_str());
  esp_task_wdt_reset();
  lv_port_sem_give();
}

int Display::get_color_type(String type) {
  if (type == "normal") return COLOR_NORMAL;
  else if (type == "poison") return COLOR_POISON;
  else if (type == "psychic") return COLOR_PSYCHIC;
  else if (type == "grass") return COLOR_GRASS;
  else if (type == "ground") return COLOR_GROUND;
  else if (type == "ice") return COLOR_ICE;
  else if (type == "fire") return COLOR_FIRE;
  else if (type == "rock") return COLOR_ROCK;
  else if (type == "dragon") return COLOR_DRAGON;
  else if (type == "water") return COLOR_WATER;
  else if (type == "bug") return COLOR_BUG;
  else if (type == "dark") return COLOR_DARK;
  else if (type == "fighting") return COLOR_FIGHTING;
  else if (type == "ghost") return COLOR_GHOST;
  else if (type == "steel") return COLOR_STEEL;
  else if (type == "flying") return COLOR_FLYING;
  else if (type == "electric") return COLOR_ELECTRIC;
  else if (type == "fairy") return COLOR_FAIRY;
  else return 0x000000;
}

void Display::update_pkm_type(String type1, String type2) {
  lv_obj_clear_flag(ui_btn_type1, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_set_style_bg_color(ui_btn_type1, lv_color_hex(get_color_type(type1)), LV_PART_MAIN | LV_STATE_DEFAULT);

  if (type2 != "") {
    lv_obj_clear_flag(ui_btn_type2, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_bg_color(ui_btn_type2, lv_color_hex(get_color_type(type2)), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  else {
    lv_obj_add_flag(ui_btn_type2, LV_OBJ_FLAG_HIDDEN);
  }
  
  String type1_pr = type1;
  type1_pr[0] = toupper(type1_pr[0]);

  String type2_pr = type2;
  type2_pr[0] = toupper(type2_pr[0]);

  lv_label_set_text(ui_pkm_type1, type1_pr.c_str());
  lv_label_set_text(ui_pkm_shadow_type1, type1_pr.c_str());
  lv_label_set_text(ui_pkm_type2, type2_pr.c_str());
  lv_label_set_text(ui_pkm_shadow_type2, type2_pr.c_str());
  lv_obj_align_to(ui_pkm_shadow_type1, ui_pkm_type1, LV_ALIGN_CENTER, 2, 2);
  lv_obj_align_to(ui_pkm_shadow_type2, ui_pkm_type2, LV_ALIGN_CENTER, 2, 2);
}

void Display::update_ui_network(void *data1, void *data2)
{
  log_i("updating the network list...");

  lv_port_sem_take();
  lv_obj_clear_flag(ui_WiFiList, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_clear_flag(ui_WiFiList, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_clean(ui_WiFiList);

  int *arraySize = static_cast<int *>(data2);
  log_i("Number of networks: %d", *arraySize);

  String *strPtr = static_cast<String *>(data1);

  std::vector<String> new_wifi_list(strPtr, strPtr + *arraySize);

  if (*arraySize == 0) {
    lv_label_set_text_fmt(ui_wifi_status_label, "Scanning finished, No networks found.", *arraySize);
  }

  for (int i = 0; i < *arraySize; i++) {
    log_i("Network %d: %s", i, new_wifi_list[i].c_str());
    lv_obj_t *btn = lv_list_add_btn(ui_WiFiList, NULL, new_wifi_list[i].c_str());
    lv_obj_add_event_cb(btn, ui_wifi_event_callback_thunk, LV_EVENT_CLICKED, NULL);
  }

  lv_label_set_text_fmt(ui_wifi_status_label, "Scanning finished, %d networks found.", *arraySize);
  lv_obj_clear_flag(ui_WiFiList, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_WiFiList, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag(ui_WiFiList, LV_OBJ_FLAG_SCROLLABLE);
  lv_port_sem_give();
}

void Display::textarea_event_callback(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);

  if (code == LV_EVENT_FOCUSED) {
    lv_keyboard_set_textarea(ui_keyboard, obj);
    lv_obj_move_foreground(ui_keyboard);
    lv_obj_clear_flag(ui_keyboard, LV_OBJ_FLAG_HIDDEN);
  } else if (code == LV_EVENT_DEFOCUSED) {
    ui_Focused_Obj = NULL;
  }
}

void Display::update_time(void *timeStruct) {
  lv_port_sem_take();
  struct tm *localtime = (struct tm *)timeStruct;
  char hourMin[10];
  strftime(hourMin, 10, "%H:%M", (struct tm *)timeStruct);
  lv_label_set_text(ui_TimeLabel, hourMin);

  char date[12];
  strftime(date, 12, "%d/%m/%y", (struct tm *)timeStruct);
  lv_label_set_text(ui_DateLabel, date);
  lv_port_sem_give();
}

void Display::lv_port_sem_take(void)
{
  TaskHandle_t task = xTaskGetCurrentTaskHandle();
  if (lvgl_task_handle != task)
  {
    xSemaphoreTake(bin_sem, portMAX_DELAY);
  }
}

void Display::lv_port_sem_give(void)
{
  TaskHandle_t task = xTaskGetCurrentTaskHandle();
  if (lvgl_task_handle != task)
  {
    xSemaphoreGive(bin_sem);
  }
}

int Display::get_display_width()
{
  return gfx->width();
}

int Display::get_display_height()
{
  return gfx->height();
}
