#include "compass.h"

const unsigned int COMPASS_BUFF = 15;

Compass::Compass(unsigned int spin_pin_, unsigned int dir_pin_, unsigned int brake_pin_
                 : Component(pin_numbers, modes, number_of_pins, component_name))
{

}

Compass::initialize()
{
    bno = Adafruit_BNO055(55, 0x28, &Wire2);
    if (!bno.begin())
    {
        Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1)
            ;
    }
    bno.setExtCrystalUse(true);
}

Compass::readCompass()
{
    sensors_event_t event;
    bno.getEvent(&event);
    int angle = event.orientation.x;
    return (angle > 180) ? angle - 360 : angle;
}

Compass::isBetween(int lower, int upper, int x)
{
    return lower < x && x < upper;
}

Compass::isNorth()
{
    return isBetween(COMPASS_BUFF * -1, COMPASS_BUFF, readCompass());
}