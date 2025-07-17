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
unsigned long ballFrontStartTime = 0;
float lastBallAngle = -1;
const int frontThresholdLow = 0;
const int frontThresholdHigh = 15;
const unsigned long stuckDuration = 2500;  // ms
const int nudgeSpeed = 100;
const int nudgeDuration = 500;

void returnGoalieToWhiteLine() {
  while (c.getAvoidAngle() != 0) {
    c.updateReadings();
    m.basic_move_with_compass(180, 90);
  }
  m.basic_move_with_compass(0, 120);
  delay(300);
}


void nudge_forward_and_back() {
  m.basic_move_with_compass(0, nudgeSpeed);  // move forward
  delay(nudgeDuration);
  returnGoalieToWhiteLine();
  m.brake();
}

void attack_w_color_sensor() {
  int speed = 100;

  c.updateReadings();
  ir.updateReadings();

  float camAngle = camera.calculateRotationAngle();
  float curr_ball_angle = ir.getBallAngle();
  // Serial.println(curr_ball_angle);

  // c.updateReadings();
  // Serial.println("green:");
  // c.printGreenValues();
  // Serial.println("readings:");
  // c.printReadings();

  float avoidAngle = c.getAvoidAngle();
  // Serial.println(curr_ball_angle);

  Serial.println("green:");
  c.printGreenValues();
  Serial.println("readings:");
  c.printReadings();

  // m.basic_move_with_compass(curr_ball_angle, speed);

  if (avoidAngle != -1) {
    m.basic_move_with_compass(avoidAngle, 175);
    delay(200);
    Serial.println("oob");
  } else {
    // m.basic_move_with_compass(curr_ball_angle, speed);
    m.basic_move_with_compass(curr_ball_angle, speed);
  }
}


void setup() {
  Serial.begin(9600);
  ir.initIR();
  m.initMovement();
  cmp.initialize();
  c.init();

  camera.initialize();
}

void loop() {
  ir.updateReadings();
  float currBallAngle = ir.getBallAngle();
  // Serial.println(millis() - ballFrontStartTime);
  // Serial.println(currBallAngle);
  bool ballInFront = (currBallAngle > 345) || (currBallAngle < 15);
  c.updateReadings();
  Serial.println(c.getAvoidAngle());
  // Serial.println(ballInFront);

  // If the ball isn't seen, reset timer and brake
  if (currBallAngle == -1) {
    ballFrontStartTime = 0;
    m.brake();
    return;
  }

  // Check if ball is in front zone [0,15] or [345,360]

  if (ballInFront) {
    // Start or continue front timer
    if (ballFrontStartTime == 0) {
      ballFrontStartTime = millis();
    }

    // Only nudge if the angle hasn't changed significantly
    if (millis() - ballFrontStartTime >= stuckDuration) {
      Serial.println("Ball stuck! Nudging...");
      nudge_forward_and_back();
      ballFrontStartTime = 0;
    }

    m.brake();  // hold position while ball is in front
  } else {
    // Ball not in front — reset timer
    ballFrontStartTime = 0;

    if (currBallAngle > 15 && currBallAngle < 180) {
      m.basic_move_with_compass(90, 100);
    } else if (currBallAngle < 345 && currBallAngle >= 180) {
      m.basic_move_with_compass(270, 100);
    } else {
      m.brake();
    }
  }

  lastBallAngle = currBallAngle;
  // int speed = 100;
  // attack_w_color_sensor();
  // int speed = 100;
  // c.updateReadings();
  // if(c.getAnalogValues()[0] > 200) {
  //   m.basic_move_with_compass(180, 100);
  //   Serial.println("on line");
  //   delay(500);
  // }
  // else {
  //   m.basic_move_with_compass(0, 100);
  //   Serial.println("on field");
  // }
  // Serial.println(c.getAnalogValues()[0]);
  // c.printReadings();
  // m.basic_move_with_compass(180, 100);
  // delay(100);
  // float ballAngle = ir.getBallAngle();

  // float camAngle = camera.calculateRotationAngle();

  // int angles[] = { 0, 180, 45, 225, 90, 270, 135, 315, 180, 0, 225, 45, 270, 90, 315, 135 };

  // Serial.println(camAngle);

  // for (int i = 0; i < 16; i++) {
  //   m.basic_move_with_compass(angles[i], speed);
  //   delay(500);
  //   m.brake();
  //   delay(200);  // small pause between directions
  // }

  // m.basic_move_with_compass_and_camera(0, speed, camAngle);
  // m.basic_move_with_compass(270, speed);
  // delay(400);
  // m.basic_move_with_compass(180, speed);
  // delay(400);
  // Serial.println(c.getAvoidAngle());
  // m.rotate_motor(speed, "BR");

  // delay(100);
  // attack_w_color_sensor();
}
