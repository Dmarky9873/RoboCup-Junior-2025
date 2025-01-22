#include "movement.h"

void Movement::initMovement() {
  compass.initialize();
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

void Movement::rotateTo(int degrees, int speed) {
  float reading = compass.readCompass();
  while(!compass.isBetween(degrees - COMPASS_BUFF, degrees + COMPASS_BUFF, reading)) {
    if (reading + degrees > degrees) {
      rotate(-speed);
    }
    else {
      rotate(speed);
    }
    reading = compass.readCompass();
  }
  brake();
}

void Movement::move(double theta, int maxSpeed) {
  double speeds[4] = {
    maxSpeed * sin(((theta - 90 + 40) * M_PI) / 180), // TR
    maxSpeed * sin(((theta - 90 - 40) * M_PI) / 180), // BR
    maxSpeed * sin(((theta + 90 + 40) * M_PI) / 180), // BL
    maxSpeed * sin(((theta + 90 - 40) * M_PI) / 180)  // TL
  };

  motor_FR.spin(speeds[0]);
  motor_BR.spin(speeds[1]);
  motor_BL.spin(speeds[2]);
  motor_FL.spin(speeds[3]);
}