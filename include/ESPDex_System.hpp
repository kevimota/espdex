#pragma once
#include <Arduino.h>
#include "time.h"
#include "defines.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "FS.h"

typedef enum {
  SYS_TIME,
  SYS_SD_NOT_FOUND
} System_Event_t;

class System {
private:
  typedef void (*FuncPtrString)(System_Event_t, void*);
  WiFiClientSecure *client;

public:
  FuncPtrString system_event_cb;
  fs::FS *storage;

  System(FuncPtrString callback, fs::FS &sd);
  ~System();

  long gmtOffset_sec;
  int daylightOffset_sec;
  String timezone;
  bool requestedTimeUpdate;

  void setConfigTzTime();
  void update_local_time();
};