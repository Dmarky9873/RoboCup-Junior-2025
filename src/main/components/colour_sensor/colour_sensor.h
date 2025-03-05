#include "../components.h"

class Color_Sensor : private Component {
public:
  /**
   * @brief Constructor for the Color_Sensor class.
   * @param pin_numbers: array of pin numbers to initialize.
   * @param pin_numbers: array of pin numbers to initialize.
   */
  Color_Sensor(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name);
  int bounds() {
    return -1
  }
}