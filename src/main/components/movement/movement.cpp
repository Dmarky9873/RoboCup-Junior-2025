#include "movement.h"
#include <math.h>

void Movement::initMovement() {
  compass.initialize();
  colorSensor.init();
}

void Movement::debug() {
  colorSensor.printReadings();
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

void Movement::move(double theta, int maxSpeed) {
  if (theta == -1)
  {
    brake();
    return;
  } 

  float reading = compass.readCompass();

  // double degrees = theta > 180 ? theta - 360 : theta;
  float mult = 0.5;
  float min = 30;

  float spin_index = 0;

  // point north
  if (!compass.isBetween(0 - COMPASS_BUFF, 0 + COMPASS_BUFF, reading)) {
    float speed = min + (mult *((abs(reading) / 180) * (maxSpeed - min)));
    if (0 < reading) {
      speed = speed * -1;
    } 
    spin_index = speed;

    // // check if color sensor detects oob
    // if ((colorSensor.frontDetected() == 0 && (theta > 315 || theta <= 45)) || 
    // (colorSensor.rightDetected() == 0 && (theta > 45 && theta <= 135)) || 
    // (colorSensor.backDetected() == 0 && (theta > 135 && theta <= 225)) ||
    // (colorSensor.leftDetected() == 0 && (theta > 225 && theta <= 315)))
    // {
    //   theta = theta > 180 ? theta - 180 : theta + 180;
    // }
    // else {
    //   // add or subtract degrees from theta
    //   // to make the robot catch ball in dribbler area
    //   if (theta <= 180) {
    //     theta = theta + 30;
    //   }
    //   else {
    //     theta = theta - 30;
    //   }
    // }
    if (theta <= 180) {
      theta = theta + 30;
    }
    else {
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

  motor_FR.spin(map(speeds[0] + spin_index, -255, 255, -maxSpeed, maxSpeed));
  motor_BR.spin(map(speeds[1] + spin_index, -255, 255, -maxSpeed, maxSpeed));
  motor_BL.spin(map(speeds[2] + spin_index, -255, 255, -maxSpeed, maxSpeed));
  motor_FL.spin(map(speeds[3] + spin_index, -255, 255, -maxSpeed, maxSpeed));
}