#include "movement.h"
#include <math.h>

void Movement::initMovement() {
  compass.initialize();
  colorSensor.init();
}

bool Movement::isBetween(int lower, int upper, int x) {
  return lower < x && x < upper;
}

void Movement::debug() {
  colorSensor.printReadings();
}

void Movement::debug_sees_border() {
  if (colorSensor.isDetected()) {
    Serial.println("on the border");
  } else {
    Serial.println("no border detected");
  }
}

void Movement::brake() {
  motor_FR.brake();
  motor_BR.brake();
  motor_BL.brake();
  motor_FL.brake();
}

void Movement::rotate(int speed) {
  motor_FR.spin(speed);
  motor_BR.spin(speed);
  motor_BL.spin(speed);
  motor_FL.spin(speed);
}

void Movement::move(double theta, int maxSpeed, bool avoid) {
  if (theta == -1) {
    brake();
    return;
  }

  float reading = compass.readCompass();

  // double degrees = theta > 180 ? theta - 360 : theta;
  float maxRotation = 50;
  float min = 20;

  float spin_index = 0;

  // point north
  int MINOR_ADJUSTMENT_WINDOW = 70;
  int COMPASS_MAJOR_ADJUSTMENT_SPEED = 36;

  if (!isBetween(0 - COMPASS_BUFF, 0 + COMPASS_BUFF, reading)) {
    if (abs(reading) < MINOR_ADJUSTMENT_WINDOW) {
      // Serial.println("minor correction");
      float speed = min + (abs(reading) / 180) * (maxRotation);
      if (reading > 0) {
        speed = speed * -1;
      }
      spin_index = speed;
    } else {
      while (!isBetween(0 - COMPASS_BUFF, 0 + COMPASS_BUFF, reading)) {
        // Serial.println("major correction");
        int direction = reading > 0 ? -COMPASS_MAJOR_ADJUSTMENT_SPEED : COMPASS_MAJOR_ADJUSTMENT_SPEED;
        rotate(direction);
        reading = compass.readCompass();
      }
    }
    // Serial.println("correcting compass");
  }

  // catching ball
  if (!isBetween(0 - COMPASS_BUFF, 0 + COMPASS_BUFF, theta) && !avoid) {
    if (theta <= 180) {
      theta = theta + 30;
    } else {
      theta = theta - 30;
    }
  }

  double speeds[4] = {
    maxSpeed * sin(((theta - 90 + 40) * M_PI) / 180),  // TR
    maxSpeed * sin(((theta - 90 - 40) * M_PI) / 180),  // BR
    maxSpeed * sin(((theta + 90 + 40) * M_PI) / 180),  // BL
    maxSpeed * sin(((theta + 90 - 40) * M_PI) / 180)   // TL
  };

  // point towards ball
  // if (!compass.isBetween(degrees - COMPASS_BUFF, degrees + COMPASS_BUFF, 0)) {
  //   float speed = min + (mult *((abs(degrees) / 180) * (maxSpeed - min)));
  //   if (degrees + COMPASS_BUFF < 0) {
  //     speed = speed * -1;
  //   }
  //   spin_index = speed;
  // }

  // Serial.print("Spin Index: ");
  // Serial.println(spin_index);
  // Serial.print(" | |theta - reading|: ");
  // Serial.print(x);
  // Serial.print(" | theta: ");
  // Serial.print(theta);
  // Serial.print(" | compass reading: ");
  // Serial.println(reading);

  // Serial.println(map(speeds[0] + spin_index, 0, 300, 0, maxSpeed));

  // Serial.println(speeds[0] + spin_index);
    motor_FR.spin(map(speeds[0] + spin_index, -255, 255, -maxSpeed, maxSpeed));
  motor_BR.spin(map(speeds[1] + spin_index, -255, 255, -maxSpeed, maxSpeed));
  motor_BL.spin(map(speeds[2] + spin_index, -255, 255, -maxSpeed, maxSpeed));
  motor_FL.spin(map(speeds[3] + spin_index, -255, 255, -maxSpeed, maxSpeed));
}