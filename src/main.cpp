#define TFT_BL_BRIGHTNESS 127
#define TFT_BL_FREQUENCY 12000

#include "ESPDex.hpp"

ESPDex* _ESPDex;

void initBoard() {
#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
#endif
}

void setup()
{
  Serial.begin(115200);
  initBoard();
  _ESPDex = new ESPDex();
  _ESPDex->begin();
}

void loop()
{

}
