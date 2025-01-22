#include "components/movement/movement.cpp"

Movement movement;

void setup() {
  Serial.begin(9600);
  movement.initMovement();
}

void loop() {
  // movement.rotateTo(0, 50);
  movement.move(20, 100);
  // delay(500);
  // movement.brake();
  // delay(500);
  // movement.move(200, 100);
  // delay(500);
  // movement.brake();
  // delay(500);
}