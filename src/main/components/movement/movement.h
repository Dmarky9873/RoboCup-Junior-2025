#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../motor/motor.cpp"
#include "../compass/compass.cpp"

class Movement {

  public:

    void initMovement();

    void brake();

    void rotateTo(int degrees, int speed);

    void move(double theta, int maxSpeed);
    
  private:
    void rotate(int speed);

    Motor motor_FR{5, 4};
    Motor motor_BR{6, 7};
    Motor motor_BL{1, 0};
    Motor motor_FL{2, 3};
    Compass compass;
    const unsigned int COMPASS_BUFF = 13;
};

#endif