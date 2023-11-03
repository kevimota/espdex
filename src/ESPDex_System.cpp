#include "ESPDex_System.hpp"

static System *instance = NULL;

const char *geoAPI = "https://get.geojs.io/v1/ip/geo.json";
String timeAPI = "https://timeapi.io/api/TimeZone/zone?timeZone=";

const char *ntpServer0 = "time1.google.com";
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";

void systemTask(void *pvParameters)
{
  while (1)
  {
    instance->update_local_time();
    vTaskDelay(SYSTEM_UPDATE_INTERVAL);
  }
}

void get_tz(void *pvParameters)
{
  bool got_offsets = false;

  log_i("Setting the default timezone.");
  configTzTime(DEFAULT_TZ, ntpServer0, ntpServer1, ntpServer2);
  instance->requestedTimeUpdate = true;

  HTTPClient http;

  http.begin(geoAPI);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0)
  {
    String response = http.getString();
    DynamicJsonDocument doc(512); // Adjust the buffer size as needed
    DeserializationError error = deserializeJson(doc, response);

    if (error)
    {
      log_e("JSON Parsing Error: %s", error.c_str());
    }
    else
    {
      // Access the specific attribute you need
      String t = doc["timezone"];
      instance->timezone = t;
      log_i("Timezone: %s", instance->timezone.c_str());
    }
  }
  else
  {
    log_e("HTTP Request failed");
  }
  http.end();

  http.begin(timeAPI + instance->timezone);

  httpResponseCode = http.GET();

  if (httpResponseCode > 0)
  {
    String response = http.getString();
    DynamicJsonDocument doc(1500); // Adjust the buffer size as needed
    DeserializationError error = deserializeJson(doc, response);

    if (error)
    {
      log_e("JSON Parsing Error: %s", error.c_str());
    }
    else
    {
      // Access the specific attribute you need
      log_i("HTTP Response: %s", response.c_str());
    }
  }
  else
  {
    log_e("HTTP Request failed");
  }
  http.end();


  vTaskDelete(NULL);
}

System::System(FuncPtrString callback, fs::FS &sd)
{
  instance = this;
  requestedTimeUpdate = false;
  system_event_cb = callback;
  storage = &sd;

  xTaskCreate(systemTask, "systemTask", 4096, NULL, 1, NULL);
}

System::~System() {}

void System::setConfigTzTime()
{
  TaskHandle_t get_tz_handle;
  xTaskCreate(get_tz, "get_tz", 5120, NULL, 1, &get_tz_handle);
}

void System::update_local_time()
{

  if (!requestedTimeUpdate)
    return;

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    log_e("Failed to obtain time");
    return;
  }

  system_event_cb(SYS_TIME, &timeinfo);
}
