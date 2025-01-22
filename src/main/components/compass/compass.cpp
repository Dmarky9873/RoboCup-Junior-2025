#include "compass.h"

const unsigned int COMPASS_BUFF = 15;

void Compass::initialize()
{
    bno = Adafruit_BNO055(55);
    if (!bno.begin())
    {
        Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1)
            ;
    }
    bno.setExtCrystalUse(true);
}

float Compass::readCompass()
{
    sensors_event_t event;
    bno.getEvent(&event);
    int angle = event.orientation.x;
    return (angle > 180) ? angle - 360 : angle;
}

bool Compass::isBetween(int lower, int upper, int x) {
  return lower < x && x < upper;
}