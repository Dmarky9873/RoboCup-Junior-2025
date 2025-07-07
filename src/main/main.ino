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
// void attack_w_color_sensor() {
//   int speed = 150;
//   // daniel is the goatZtyuil,mmnb ,mnbvc

//   float curr_ball_angle = ir.getBallAngle();
//   m.move(curr_ball_angle, speed, false);

//   float colorDetected = c.isDetected();

//   while (colorDetected != -1) {
//     // Serial.println("oob");
//     m.brake();
//     m.move(colorDetected, speed + 20, true);
//     delay(100);
//     colorDetected = c.isDetected();
//   }
// }


void setup() {
  Serial.begin(9600);
  ir.initIR();
  c.init();
  m.initMovement();
  cmp.initialize();

  camera.initialize();

}

void loop() {
  int speed = 180;
  float ballAngle = ir.getBallAngle();
  // // Serial.print("ballAngle: ");
  // // Serial.println(ballAngle > 180 ? ballAngle - 360 : ballAngle);
  float camAngle = camera.calculateRotationAngle();

  // Serial.print("Camera range: ");
  // Serial.print(camAngle - 7);
  // Serial.print(" - ");
  // Serial.print(camAngle + 7);
  // Serial.println(camAngle);

  //   Serial.print("reading: ");
  // Serial.print(cmp.readCompass());
  // Serial.print(" camangle: ");
  // Serial.println(camAngle);
  // m.move(ballAngle, speed, false, camAngle);
  // m.rotate_motor(100, "BR");
  m.move(camAngle, 200, false, 0);

  // Serial.println("hello");

  // ir.printReadingsArr();

  // m.move(0, 200, false);
  // m.rotate_motor(200, "BR");

  // m.debug_sees_border();
  // c.printReadings();
  // Serial.println(cmp.readCompass());
  // Serial.println(ballAngle);

  delay(100);
  // attack_w_color_sensor();
}
