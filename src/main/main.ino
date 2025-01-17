#include "components/motor/motor.h"
#include "components/motor/motor.cpp"

Motor motor_FR(5, 4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  motor_FR.spin(200);
}
