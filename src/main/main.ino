#include "./components/IR/IR.h"
#include "./components/IR/IR.cpp"
#include "./components/movement/movement.h"
#include "./components/movement/movement.cpp"
#include "./components/colorsensor/colorsensor.h"
#include "./components/colorsensor/colorsensor.cpp"

Movement m;
IR ir;
ColorSensor c;

void setup() {
  Serial.begin(9600);
  ir.initIR();
  m.initMovement();
  c.init();
}

void loop() {
  int speed = 200;
  int oobDirection = c.getOOBDirection();
  float ballAngle = ir.getBallAngle();
  // c.debugFiltered();
  // Serial.print("oobDirection: ");
  // Serial.println(c.getOOBDirection());
  Serial.print("ballAngle: ");
  Serial.println(ballAngle > 180 ? ballAngle - 360 : ballAngle);
  // if (oobDirection != -1) {
  //   int avoidOOBDirection = oobDirection > 180 ? oobDirection - 180 : oobDirection + 180;
  //   m.move(avoidOOBDirection, speed);
  // }
  // else {
  //   m.move(ballAngle, speed);
  // }
  m.move(ballAngle, 200);
  delay(50);
}