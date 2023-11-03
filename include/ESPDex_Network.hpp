#pragma once
#include <vector>
#include <WiFi.h>
#include <defines.h>

typedef enum {
  NETWORK_DISCONNECTED,
  NETWORK_SCANNING_OFF,
  NETWORK_SCANNING_ON,
  NETWORK_CONNECTING,
  NETWORK_CONNECT_FAILURE,
  NETWORK_CONNECTED,
} Network_Event_t;

class Network {
private:
  typedef void (*FuncPtrVector)(Network_Event_t, void*, void*);
  friend void ntScanTask(void* pvParameters);
  friend void ntBeginTask(void *pvParameters);
  Network_Event_t _networkEvent;
  void WiFiScanner(bool isOn);
  void WiFiScannerStop();
  void WiFiConnector(void* param);
public:
  String _ssid, _pwd;
  std::vector<String> WiFiLog;
  TaskHandle_t ntScanTaskHandler, ntConnectTaskHandler;
  FuncPtrVector network_result_cb;
  Network(FuncPtrVector callback);
  ~Network();
  void WiFiCommand(Network_Event_t networkEvent, void* param);
  void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info);
};