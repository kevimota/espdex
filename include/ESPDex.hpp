#pragma once

#include <Arduino.h>
#include "ESPDex_Display.hpp"
#include "ESPDex_Network.hpp"
#include "ESPDex_System.hpp"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class ESPDex {
  private:
    SPIClass spi = SPIClass();

  public:
    Display *display;
    Network *network;
    System *system;

    ESPDex();
    ~ESPDex();
    void begin();

    bool initSDCard();
};