#include "movement.h"
#include <math.h>

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

// void Movement::rotateTo(int degrees, int speed) {
//   float reading = compass.readCompass();
//   while(!compass.isBetween(degrees - COMPASS_BUFF, degrees + COMPASS_BUFF, reading)) {
//     if (reading + degrees > degrees) {
//       rotate(-speed);
//     }
//     else {
//       rotate(speed);
//     }
//     reading = compass.readCompass();
//   }
//   brake();
// }

void Movement::rotateTo(int degrees, int speed) {
  float reading = compass.readCompass();

  float spin_index = 0;

  double a = 0.07;
  double b = -110;
  double c = 60;
  double d = 40;
  double e = 2.71828;
  double x = abs(degrees - reading);

  Serial.println((c / (1 + pow(e, -a * (x + b)))));


  if (!compass.isBetween(degrees - COMPASS_BUFF, degrees + COMPASS_BUFF, reading)) {
    if (reading + degrees > degrees) {
      spin_index = -(c / (1 + pow(e, -a * (x + b))) + d);
    } else {
      spin_index = ((c / (1 + pow(e, -a * (x + b)))) + d);
    }
  }
  Serial.print("Spin Index: ");
  Serial.print(spin_index);
  Serial.print(" | |degrees - reading|: ");
  Serial.print(x);
  Serial.print(" | degrees: ");
  Serial.print(degrees);
  Serial.print(" | compass reading: ");
  Serial.println(reading);

  motor_FR.spin(spin_index);
  motor_BR.spin(spin_index);
  motor_BL.spin(spin_index);
  motor_FL.spin(spin_index);
}

void Movement::move(double theta, int maxSpeed) {
  double speeds[4] = {
    maxSpeed * sin(((theta - 90 + 40) * M_PI) / 180),  // TR
    maxSpeed * sin(((theta - 90 - 40) * M_PI) / 180),  // BR
    maxSpeed * sin(((theta + 90 + 40) * M_PI) / 180),  // BL
    maxSpeed * sin(((theta + 90 - 40) * M_PI) / 180)   // TL
  };

  float reading = compass.readCompass();

  float spin_index = 0;

  double a = 0.07;
  double b = -110;
  double c = 60;
  double d = 40;
  double e = 2.71828;
  double x = abs(theta - reading);

  Serial.println((c / (1 + pow(e, -a * (x + b)))));


  if (!compass.isBetween(theta - COMPASS_BUFF, theta + COMPASS_BUFF, reading)) {
    if (reading + theta > theta) {
      spin_index = -(c / (1 + pow(e, -a * (x + b))) + d);
    } else {
      spin_index = ((c / (1 + pow(e, -a * (x + b)))) + d);
    }
  }
  Serial.print("Spin Index: ");
  Serial.print(spin_index);
  Serial.print(" | |theta - reading|: ");
  Serial.print(x);
  Serial.print(" | theta: ");
  Serial.print(theta);
  Serial.print(" | compass reading: ");
  Serial.println(reading);

  motor_FR.spin(speeds[0] + spin_index);
  motor_BR.spin(speeds[1] + spin_index);
  motor_BL.spin(speeds[2] + spin_index);
  motor_FL.spin(speeds[3] + spin_index);
}