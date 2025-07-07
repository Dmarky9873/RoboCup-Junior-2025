#include "WString.h"
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
    void move(double theta, int maxSpeed, bool avoid, float cameraRotationAngle);
    void rotate(int speed);
    void debug_sees_border();
    bool is_on_border();
    void rotate_motor(int speed, String motor);

  private:
    Compass compass;
    ColorSensor colorSensor;

    // 1
    Motor motor_BR{1, 2}; // good
    Motor motor_FR{4, 3}; // good
    Motor motor_BL{6, 5}; // good
    Motor motor_FL{8, 7}; // good

    // //2 (fries in the bag)
    // Motor motor_BL{0, 1}; 
    // Motor motor_FR{3, 2};
    // Motor motor_FL{4, 5};
    // Motor motor_BR{7, 6};

    bool isBetween(int lower, int upper, int x);
    const unsigned int COMPASS_BUFF = 5;

};

#endif