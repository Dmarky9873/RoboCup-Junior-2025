#include "movement.h"

Movement::initMotor() {
  compass.initialize();
}

Movement::rotate(int speed) {
  for (int i = 0; i < 4; i++) {
    motors[i].spin(speed);
  }
}

Movement::brake() {
  for (int i = 0; i < 4; i++) {
    motors[i].brake();
  }
}

Movement::pointNorth(int baseSpeed) {
  int speed = 0;
  while (!compass.isBetween(COMPASS_BUFF * -1, COMPASS_BUFF, compass.readCompass())) {
    speed = baseSpeed - abs(abs(compass.readCompass()) - COMPASS_BUFF) * 0.3;
    rotate((compass.readCompass() > 0) ? speed : -speed);
  }
  brake();
}

Movement::moveNorth(unsigned int speed) {
  pointNorth(220);
  motors[0].spin(speed);
  motors[1].spin(speed);
  motors[2].spin(-speed);
  motors[3].spin(-speed);
}

Movement::moveSouth(unsigned int speed) {
  pointNorth(220);
  motors[0].spin(-speed);
  motors[1].spin(-speed);
  motors[2].spin(speed);
  motors[3].spin(speed);
}

Movement::moveEast(unsigned int speed) {
  pointNorth(220);
  motors[0].spin(speed);
  motors[1].spin(-speed);
  motors[2].spin(-speed);
  motors[3].spin(speed);
}

Movement::moveWest(unsigned int speed) {
  pointNorth(220);
  motors[0].spin(-speed);
  motors[1].spin(speed);
  motors[2].spin(speed);
  motors[3].spin(-speed);
}

Movement::moveNorthEast(unsigned int speed) {
  pointNorth(220);
  motors[0].spin(speed);
  motors[1].brake();
  motors[2].spin(-speed);
  motors[3].brake();
}

Movement::moveNorthWest(unsigned int speed) {
  pointNorth(220);
  motors[0].brake();
  motors[1].spin(speed);
  motors[2].brake();
  motors[3].spin(-speed);
}

Movement::moveSouthEast(unsigned int speed) {
  pointNorth(220);
  motors[0].brake();
  motors[1].spin(-speed);
  motors[2].brake();
  motors[3].spin(speed);
}

Movement::moveSouthWest(unsigned int speed) {
  pointNorth(220);
  motors[0].spin(-speed);
  motors[1].brake();
  motors[2].spin(speed);
  motors[3].brake();
}