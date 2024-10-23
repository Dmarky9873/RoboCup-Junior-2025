#include "components.h"

#ifndef COMPASS_H
#define COMPASS_H

class Compass : public Component {
public:
  /**
   * Constructor, sets private variables to params.
   *
   * @param `pin_` pin for spin.
   * @param `dir_pin_` pin for direction.
   * @param `brake_pin_` pin for brake.
   */
  Compass(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name);

  /**
   * Initialize pins to Adafruit_BNO055
   */
  void initialize();

  /**
   * Returns absolute (max 180 degrees) x-axis angle 
   */
  float readCompass();

  /**
   * Returns true if `x` is between `lower` and `upper` degrees 
   */
  boolean isBetween(int lower, int upper, int x);

  /**
   * Returns true if robot is pointing north 
   */
  boolean isNorth();


private: 
  Adafruit_BNO055 bno;

};