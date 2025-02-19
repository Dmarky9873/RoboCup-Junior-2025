#include "./components/IR/IR.h"
#include "./components/IR/IR.cpp"
#include "./components/movement/movement.h"
#include "./components/movement/movement.cpp"

Movement m;
IR ir;

void setup() {
  Serial.begin(9600);
  ir.initIR();
}

void loop() {
  m.move(ir.getBallAngle(), 200);
}