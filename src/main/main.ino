#include "./components/IR/IR.h"
#include "./components/IR/IR.cpp"
#include "./components/movement/movement.h"
#include "./components/movement/movement.cpp"
#include "./components/colorsensor/colorsensor.h"
#include "./components/colorsensor/colorsensor.cpp"
#include "./components/camera/camera.h"

Movement m;
IR ir;
ColorSensor c;
Compass cmp;
Camera camera(70.0);

//me: hay...bale, bale: wsg twin sybau ts ts ts pmo
void attack_w_color_sensor() {
  int speed = 150;
  // daniel is the goatZtyuil,mmnb ,mnbvc

  float curr_ball_angle = ir.getBallAngle();
  m.move(curr_ball_angle, speed, false);

  float colorDetected = c.isDetected();

  while (colorDetected != -1) {
    // Serial.println("oob");
    m.brake();
    m.move(colorDetected, speed + 20, true);
    delay(100);
    colorDetected = c.isDetected();
  }
}


void setup() {
  Serial.begin(9600);
  ir.initIR();
  c.init();
  m.initMovement();
  cmp.initialize();

  camera.initialize();

  pinMode(30, OUTPUT);
}

void loop() {
  // int speed = 180;
  // float ballAngle = ir.getBallAngle();
  // // Serial.print("ballAngle: ");
  // // Serial.println(ballAngle > 180 ? ballAngle - 360 : ballAngle);
  // m.move(ballAngle, speed, false);

  // ir.printPWsArr();
  // Serial.println("hello");
  camera.printStatus();

  // m.move(0, 200, false);
  // m.rotate_motor(200, "BR");

  // m.debug_sees_border();
  // c.printReadings();
  // Serial.println(cmp.readCompass());

  delay(100);
  // attack_w_color_sensor();
}
