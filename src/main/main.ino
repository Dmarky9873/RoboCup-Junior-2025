#include "components/movement/movement.cpp"

Movement movement;

void setup() {
  Serial.begin(9600);
  movement.initMovement();
}

void loop() {
  movement.rotateTo(0, 50);
}