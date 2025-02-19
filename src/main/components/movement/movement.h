#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../motor/motor.cpp"
#include "../compass/compass.cpp"

class Movement {

  public:

    void initMovement();

    void brake();

    void rotateTo(int degrees);

    void move(double theta, int maxSpeed);
    
    void rotate(int speed);
  private:

    Compass compass;
    Motor motor_FR{5, 4};
    Motor motor_BR{6, 7};
    Motor motor_BL{1, 0};
    Motor motor_FL{2, 3};
    const unsigned int COMPASS_BUFF = 20;
};

#endif