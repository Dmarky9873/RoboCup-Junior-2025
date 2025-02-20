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
    Motor motor_BL{4, 5}; 
    Motor motor_FR{7, 6};
    Motor motor_FL{0, 1};
    Motor motor_BR{3, 2};
    const unsigned int COMPASS_BUFF = 20;
};

#endif