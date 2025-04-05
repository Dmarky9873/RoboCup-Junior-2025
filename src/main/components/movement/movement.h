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
    void move(double theta, int maxSpeed, bool avoid);
    void rotate(int speed);
    void debug_sees_border();
    bool is_on_border();

  private:
    Compass compass;
    ColorSensor colorSensor;

    // 1
    // Motor motor_BL{2, 3}; 
    // Motor motor_FR{1, 0};
    // Motor motor_FL{6, 7};
    // Motor motor_BR{5, 4};

    //2 (fries in the bag)
    Motor motor_BL{0, 1}; 
    Motor motor_FR{3, 2};
    Motor motor_FL{4, 5};
    Motor motor_BR{7, 6};

    bool isBetween(int lower, int upper, int x);
    const unsigned int COMPASS_BUFF = 8;

};

#endif