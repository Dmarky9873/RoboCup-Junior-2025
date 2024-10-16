#include <Adafruit_BNO055.h>
#include "components.h"

#ifndef MOTOR_H
#define MOTOR_H

const unsigned int COMPASS_BUFF = 13;

class Motor : public Component 
{
public: 
  /**
   * Sets the speed and direction of a motor
   * 
   * @param `s` speed of the motor (negative value indicates backwards direction).
   */
  void spin(int s);

  /**
   * Stops the spin of the wheel; brake
   */
  void brake();

  /**
   * Constructor, sets private variables to params.
   *
   * @param `pin_` pin for spin
   * @param `dir_pin_` pin for direction
   * @param `brake_pin_` pin for brake
   */
  Motor(unsigned int spin_pin_, unsigned int dir_pin_, unsigned int brake_pin_);

private:
  unsigned int spin_pin;
  unsigned int dir_pin;
  unsigned int brake_pin;
};
