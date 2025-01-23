#include "components/movement/movement.cpp"

Movement movement;

void setup() {
  Serial.begin(9600);
  movement.initMovement();
}

void loop() {
  // movement.rotateTo(0);
  // movement.move(0, 150);
  // delay(1500);
  float reading = movement.read(); 
  Serial.println(180 - abs(reading));
  movement.move(180 - reading, 150);
  // delay(1500);
  // delay(500);
  // movement.brake();
  // delay(500);
  // movement.move(200, 100);
  // delay(500);
  // movement.brake();
  // delay(500);
}