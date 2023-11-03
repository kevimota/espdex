#include "ESPDex_Network.hpp"

static Network *instance = NULL;

extern "C" void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
  instance->WiFiEvent(event, info);
}

extern "C" void WiFiEventOn() {
  WiFi.onEvent(WiFiEvent);
}

Network::Network(FuncPtrVector callback) {
  instance = this;
  ntScanTaskHandler = NULL;
  ntConnectTaskHandler = NULL;
  network_result_cb = callback;
  _networkEvent = NETWORK_DISCONNECTED;
  WiFiEventOn();
}

Network::~Network() {
}

void Network::WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
  std::string temp;

  switch (event) {
    case SYSTEM_EVENT_STA_DISCONNECTED:
      vTaskDelay(500);
      if (_networkEvent == NETWORK_CONNECTING || _networkEvent == NETWORK_CONNECTED) {
        this->network_result_cb(NETWORK_DISCONNECTED, NULL, NULL);
        _networkEvent = NETWORK_DISCONNECTED;
        WiFiScanner(false);
        vTaskDelay(10);
        WiFiScanner(true);
      }
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      vTaskDelay(500);
      temp = WiFi.localIP().toString().c_str();
      this->network_result_cb(NETWORK_CONNECTED, static_cast<void*>(&(temp)), NULL);
      _networkEvent = NETWORK_CONNECTED;
      break;
    default:
      break;
  }
}

void ntScanTask(void *pvParam) {
  int taskCount = 0;
  std::vector<String> foundWifiList;
  log_i("Heap memory free: %d", ESP.getFreeHeap());
  log_i("Scan task started!");
  while (1) {
    ++taskCount;
    foundWifiList.clear();
    int n = WiFi.scanNetworks();
    log_i("Found %d networks", n);
    vTaskDelay(10);
    for (int i = 0; i < n; ++i) {
      String item = WiFi.SSID(i) + ((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "" : " *");      
      foundWifiList.push_back(item.c_str());
      vTaskDelay(10);
    }

    instance->network_result_cb(NETWORK_SCANNING_ON, static_cast<void*>(foundWifiList.data()), &n);
    vTaskDelay(5000);

    if (taskCount >= WIFI_SCAN_ITER) {
      instance->ntScanTaskHandler = NULL;
      vTaskDelete(NULL);
    }
  }
}

void ntBeginTask(void *pvParameters) {
  log_i("Begin connection");
  WiFi.mode(WIFI_STA);
  vTaskDelay(100);
  WiFi.begin(instance->_ssid,instance->_pwd);
  instance->_networkEvent = NETWORK_CONNECTING;
  vTaskDelete(NULL);
}

void Network::WiFiCommand(Network_Event_t networkEvent, void *param) {
  switch (networkEvent) {
    case NETWORK_SCANNING_OFF:
      log_i("NETWORK_SCANNING_OFF");
      this->WiFiScanner(false);
      _networkEvent = NETWORK_SCANNING_OFF;
      break;
    case NETWORK_SCANNING_ON:
      log_i("NETWORK_SCANNING_ON");
      this->WiFiScanner(true);
      break;
    case NETWORK_CONNECTING:
      log_i("NETWORK_CONNECTING");
      this->WiFiConnector(param);
      break;
  }
}

void Network::WiFiScanner(bool isOn) {
  if (isOn) {
    xTaskCreate(ntScanTask,
                "ntScanTask",
                4096,
                NULL,
                1,
                &ntScanTaskHandler);
  } else {
    this->WiFiScannerStop();
    WiFi.disconnect();
  }
}

void Network::WiFiScannerStop() {
  if (ntScanTaskHandler != NULL) {
    vTaskDelete(ntScanTaskHandler);
    ntScanTaskHandler = NULL;
  }
}

void Network::WiFiConnector(void *param) {
  this->WiFiScannerStop();
  String networkInfo = String((char*)param);
  log_i("NetworkInfo: %s", networkInfo.c_str());
  int seperatorIdx = networkInfo.indexOf(WIFI_SSID_PW_DELIMITER);
  _ssid = networkInfo.substring(0, seperatorIdx);
  _pwd = networkInfo.substring(seperatorIdx + 2, networkInfo.length());
  log_i("ssid %s", _ssid.c_str());
  log_i("pass %s", _pwd.c_str());
  xTaskCreate(ntBeginTask, "ntBeginTask", 4096, NULL, 1, &ntConnectTaskHandler);
}