#include "ESPDex.hpp"

static ESPDex *instance = NULL;

ESPDex::ESPDex()
{
  instance = this;
}

ESPDex::~ESPDex() {}

void displayEventHandler(Menu_Event_t event, void *param)
{
  switch (event)
  {
  case WIFI_OFF:
    instance->network->WiFiCommand(NETWORK_SCANNING_OFF, param);
    break;

  case WIFI_ON:
    if (param == NULL)
    {
      instance->network->WiFiCommand(NETWORK_SCANNING_ON, param);
    }
    else
    {
      instance->network->WiFiCommand(NETWORK_CONNECTING, param);
    }
    break;
  }
}

void networkResponse(Network_Event_t event, void* data1, void* data2) {
  switch (event) {
    case NETWORK_SCANNING_ON:
      instance->display->update_ui_network(data1, data2);
      break;

    case NETWORK_CONNECTED:
      instance->display->show_loading_popup(false);
      instance->display->ui_popup_open("WiFi",  "Connected!");
      instance->display->update_WiFi_label(data1);
      instance->system->setConfigTzTime();
      break;

    case NETWORK_CONNECT_FAILURE:
    case NETWORK_DISCONNECTED:
      instance->display->show_loading_popup(false);
      instance->display->ui_popup_open("WiFi", "Unable to connect to selected WiFi.");
      instance->display->update_WiFi_label(data1);
      break;
  }
}

void systemInfo(System_Event_t event, void* param) {
  switch (event) {
    case SYS_TIME:
      instance->display->update_time(param);
      break;
  }

}

void ESPDex::begin()
{
  initSDCard();
  void (*iptr)(Menu_Event_t, void*) = &displayEventHandler;
  display = new Display(displayEventHandler, SD);

  void (*vptr)(Network_Event_t, void*, void*) = &networkResponse;
  network = new Network(networkResponse);

  void (*sptr)(System_Event_t, void*) = &systemInfo;
  system = new System(systemInfo, SD);
}

bool ESPDex::initSDCard() {
  spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

  if (!SD.begin(SD_CS, spi, 80000000))
  {
    log_e("Card Mount Failed");
    return false;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    log_e("No SD card attached");
    return false;
  }

  if (cardType == CARD_MMC)
  {
    log_i("SD Card Type: MMC");
  }
  else if (cardType == CARD_SD)
  {
    log_i("SD Card Type: SDSC");
  }
  else if (cardType == CARD_SDHC)
  {
    log_i("SD Card Type: SDHC");
  }
  else
  {
    log_i("SD Card Type: UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  log_i("SD Card Size: %lluMB\n", cardSize);

  return true;
}