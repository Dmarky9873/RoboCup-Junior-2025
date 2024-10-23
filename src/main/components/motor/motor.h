#include <Adafruit_BNO055.h>
#include "components.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor : public Component
{
public:
  /**
   * Constructor, sets private variables to params.
   *
   * @param `pin_numbers[]` integer array of pin-numbers that relate to an instance of the component class.
   * @param `modes[]` integer array where modes[n] is the mode for pin_numbers[n].
   * @param `number_of_pins` number of elements in the modes[] and pin_numbers[] arrays.
   * @param `component_name` name of this component as a string.
   *
   * @param `pin_` pin for spin.
   * @param `dir_pin_` pin for direction.
   * @param `brake_pin_` pin for brake.
   */
  Motor(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name,
        unsigned int spin_pin_, unsigned int dir_pin_, unsigned int brake_pin_);

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

private:
  unsigned int spin_pin;
  unsigned int dir_pin;
  unsigned int brake_pin;
};
