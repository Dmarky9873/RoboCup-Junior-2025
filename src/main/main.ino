#include "./components/IR/IR.h"
#include "./components/IR/IR.cpp"

IR ir;
// int tpins[] = {16, 17, 20, 21, 22, 23, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
// int tNUM_IR_PINS = 16;

void setup() {
  Serial.begin(9600);
  // for (int i = 0; i < tNUM_IR_PINS; i++) {
  //   pinMode(tpins[i], INPUT);
  // }
  ir.initIR();
}

void loop() {
  // Serial.print("[ ");
  // for (int i = 0; i < tNUM_IR_PINS; i++) {
  //   int value = digitalRead(tpins[i]);

  //   if (value == LOW) {
  //     Serial.print("1 ");
  //   }
  //   else {
  //     Serial.print("0 ");
  //   }
  // }
  // Serial.print("]");
  // Serial.println();
  ir.printReadingsArr();
  // delay(100);
  // double pin = ir.getPWsArr()[0];
  // Serial.println(pin);
}