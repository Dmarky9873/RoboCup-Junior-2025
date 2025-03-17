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

// void Movement::rotateTo(double theta, int maxSpeed) {
//   if (theta == -1)
//   {
//     brake();
//     return;
//   }

//   float reading = compass.readCompass();
//   double degrees = theta > 180 ? theta - 360 : theta;
//   float mult = 0.4;
//   float min = 60;

//   if (!compass.isBetween(degrees - COMPASS_BUFF, degrees + COMPASS_BUFF, reading)) {
//     int speed = 80;
//     if (degrees + COMPASS_BUFF < reading) {
//       speed = speed * -1;
//     }
//     Serial.println(speed);
//     motor_FR.spin(speed);
//     motor_BR.spin(speed);
//     motor_BL.spin(speed);
//     motor_FL.spin(speed);
//   }
//   else {
//     brake();
//   }
// }

void Movement::move(double theta, int maxSpeed) {
  if (theta == -1)
  {
    brake();
    return;
  }

  double speeds[4] = {
    maxSpeed * sin(((theta - 90 + 40) * M_PI) / 180),  // TR
    maxSpeed * sin(((theta - 90 - 40) * M_PI) / 180),  // BR
    maxSpeed * sin(((theta + 90 + 40) * M_PI) / 180),  // BL
    maxSpeed * sin(((theta + 90 - 40) * M_PI) / 180)   // TL
  };

  float reading = compass.readCompass();

  double degrees = theta > 180 ? theta - 360 : theta;
  float mult = 0.5;
  float min = 30;

  float spin_index = 0;

  if (!compass.isBetween(degrees - COMPASS_BUFF, degrees + COMPASS_BUFF, reading)) {
    float speed = min + (mult *((abs(degrees - reading) / 180) * (maxSpeed - min)));
    if (degrees + COMPASS_BUFF < reading) {
      speed = speed * -1;
    }
    spin_index = speed;
  }
  // Serial.print("Spin Index: ");
  // Serial.print(spin_index);
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