#include "./components/IR/IR.h"
#include "./components/IR/IR.cpp"
#include "./components/movement/movement.h"
#include "./components/movement/movement.cpp"
#include "./components/colorsensor/colorsensor.h"
#include "./components/colorsensor/colorsensor.cpp"

Movement m;
IR ir;
bool shouldStop = false;
float stopped_robot_ball_angle;

float angularDifference(float a, float b) {
  float diff = fabs(a - b);
  return (diff > 180) ? 360 - diff : diff;
}

void attack_w_color_sensor() {
  int speed = 185;
  if (m.is_on_border()) {
    shouldStop = true;
  } 

  if (!shouldStop) {
    m.move(ballAngle, speed);
  } else {
    float stopped_robot_ball_angle = ir.getBallAngle();
    float curr_ball_angle = stopped_robot_ball_angle;
    
    while (angularDifference(stopped_robot_ball_angle, curr_ball_angle) < 20) {
      curr_ball_angle = ir.getBallAngle();
      m.brake();
      delay(50);
    }
    
    shouldStop = false;
    m.move(ballAngle, speed);
    delay(300);
  }
}


void setup() {
  Serial.begin(9600);
  ir.initIR();
  m.initMovement();
}

void loop() {
  int speed = 185;
  float ballAngle = ir.getBallAngle();
  // Serial.print("ballAngle: ");
  // Serial.println(ballAngle > 180 ? ballAngle - 360 : ballAngle);
  m.move(ballAngle, speed);
  // if (m.is_on_border()) {
  //   shouldStop = true;
  // } 

  // if (!shouldStop) {
  //   m.move(ballAngle, speed);
  // } else {
  //   float stopped_robot_ball_angle = ir.getBallAngle();
  //   float curr_ball_angle = stopped_robot_ball_angle;
    
  //   while (angularDifference(stopped_robot_ball_angle, curr_ball_angle) < 20) {
  //     curr_ball_angle = ir.getBallAngle();
  //     m.brake();
  //     delay(50);
  //   }
    
  //   shouldStop = false;
  //   m.move(ballAngle, speed);
  //   delay(300);
  // }

  m.move(0, speed);

  // m.debug_sees_border();
  
  // m.debug();
  delay(50);
}





