#include "./components/IR/IR.h"
#include "./components/IR/IR.cpp"
#include "./components/movement/movement.h"
#include "./components/movement/movement.cpp"
#include "./components/colorsensor/colorsensor.h"
#include "./components/colorsensor/colorsensor.cpp"

Movement m;
IR ir;
ColorSensor c;

int ball_and_oob_same(float ballAngle) {
   // check if color sensor detects oob
    if ((c.frontDetected() == 0 && (ballAngle > 315 || ballAngle <= 45)) || 
        (c.rightDetected() == 0 && (ballAngle > 45 && ballAngle <= 135)) || 
        (c.backDetected() == 0 && (ballAngle > 135 && ballAngle <= 225)) ||
        (c.leftDetected() == 0 && (ballAngle > 225 && ballAngle <= 315)))
    {
      return true;
    }
    return false;
}
//me: hay...bale, bale: wsg twin sybau ts ts ts pmo 
void attack_w_color_sensor() {
  int speed = 165;

  float curr_ball_angle = ir.getBallAngle();
  m.move(curr_ball_angle, speed);
  
  while (ball_and_oob_same(curr_ball_angle)) {
    Serial.println("same");
    curr_ball_angle = ir.getBallAngle();
    float currOppositeBallAngle = curr_ball_angle >= 180 ? curr_ball_angle - 180 : curr_ball_angle + 180;
    m.move(currOppositeBallAngle, speed);
    delay(200);
  }
  
  Serial.println("chasing");
}


void setup() {
  Serial.begin(9600);
  ir.initIR();
  c.init();
  m.initMovement();
}

void loop() {
  // int speed = 200;
  // float ballAngle = ir.getBallAngle();
  // // Serial.print("ballAngle: ");
  // // Serial.println(ballAngle > 180 ? ballAngle - 360 : ballAngle);
  // m.move(ballAngle, speed);

  // m.debug_sees_border();
  attack_w_color_sensor();
  // m.debug();
  
  // m.debug();
  delay(50);
}





