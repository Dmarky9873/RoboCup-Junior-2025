#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../motor/motor.cpp"
#include "../compass/compass.cpp"
#include "../colorsensor/colorsensor.h"

class Movement {

  public:
    void initMovement();
    void debug();
    void brake();
    void move(double theta, int maxSpeed);
    void rotate(int speed);
    void debug_sees_border();
    bool is_on_border();

  private:
    Compass compass;
    ColorSensor colorSensor;
    Motor motor_BL{3, 2}; 
    Motor motor_FR{0, 1};
    Motor motor_FL{7, 6};
    Motor motor_BR{4, 5};
    const unsigned int COMPASS_BUFF = 15;

};

#endif