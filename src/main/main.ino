#include "./components/IR/IR.h"
#include "./components/IR/IR.cpp"
#include "./components/movement/movement.h"
#include "./components/movement/movement.cpp"

Movement m;
IR ir;

void setup() {
  Serial.begin(9600);
  ir.initIR();
  m.initMovement();
}

void loop() {
<<<<<<< Updated upstream
  // float ballAngle = ir.getBallAngle();
  // Serial.println(ballAngle);
  // m.move(ballAngle, 200);
  // delay(50);

  m.move(0, 150);
=======
  // m.move(0, 150);
  float ballAngle = ir.getBallAngle();
  Serial.print("ballAngle: ");
  Serial.println(ballAngle > 180 ? ballAngle - 360 : ballAngle);
  m.move(ballAngle, 200);
  delay(50);
>>>>>>> Stashed changes
}