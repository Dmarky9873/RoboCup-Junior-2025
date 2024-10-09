// scrapped class

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string.h>

#define UNKNOWN_PIN 0xFF

class Component {
public:
  /**
    * Initializes each pin in `pin_numbers[]` to their respective mode in `modes[]`
    */
  void setUp();

  /**
    * Constructor, sets private variables to params.
    *
    * @param `pin_numbers[]` integer array of pin-numbers that relate to an instance of the component class.
    * @param `modes[]` integer array where modes[n] is the mode for pin_numbers[n].
    * @param `number_of_pins` number of elements in the modes[] and pin_numbers[] arrays.
    * @param `component_name` name of this component as a string.
    */
  Component(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name) 
  : num_pins(number_of_pins), name(component_name), pin_nums(pin_numbers), mds(modes) {

  };

private:
  // TODO: Comment these
  const int num_pins;
  const String name;
  const int *pin_nums;
  const uint8_t *mds;
};

// TODO: Comment this function
void Component::setUp() {
  Serial.print("Initializing ");
  Serial.print(name);
  Serial.println("...");
  Serial.println();

  for (int i = 0; i < num_pins; i++) {
    Serial.print("Initializing pin ");
    Serial.print(pin_nums[i]);
    Serial.println();

    pinMode(pin_nums[i], mds[i]);
  }
}

#endif