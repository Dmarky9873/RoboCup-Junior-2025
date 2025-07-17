#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Adafruit_MCP3008.h>

class ColorSensor {
  public:
    void init();
    void printReadings();
    void printGreenValues();
    void updateReadings();
    float getWarningAvoidAngle() ;
    float getAvoidAngle();
    uint16_t* getAnalogValues();
};

#endif