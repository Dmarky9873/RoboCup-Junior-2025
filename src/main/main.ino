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

void attack_w_color_sensor() {
  int speed = 150;

  float camAngle = camera.calculateRotationAngle();
  float curr_ball_angle = ir.getBallAngle();
  m.move(curr_ball_angle, speed, false, camAngle);

  float colorDetected = c.isDetected();

  while (colorDetected != -1) {
    // Serial.println("oob");
    m.brake();
    m.move(colorDetected, speed, true, 0);
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
}

void loop() {
  int speed = 200;
  float ballAngle = ir.getBallAngle();

  float camAngle = camera.calculateRotationAngle();

  int angles[] = { 0, 180, 45, 225, 90, 270, 135, 315, 180, 0, 225, 45, 270, 90, 315, 135 };

  Serial.println(camAngle);

  // for (int i = 0; i < 16; i++) {
  //   m.basic_move_with_compass(angles[i], speed);
  //   delay(500);
  //   m.brake();
  //   delay(200);  // small pause between directions
  // }

  m.basic_move_with_compass_and_camera(0, speed, camAngle);
  // m.basic_move_with_compass(0, speed);




  delay(100);
  // attack_w_color_sensor();
}
