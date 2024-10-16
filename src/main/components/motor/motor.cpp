#include "motor.h"

Motor::Motor(unsigned int spin_pin_, unsigned int dir_pin_, unsigned int brake_pin_) {
  spin_pin(spin_pin_);
  dir_pin(dir_pin_);
  brake_pin(brake_pin_);

  pinMode(s_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(br_pin, OUTPUT);
}

Motor::spin(int s) {
  digitalWrite(br_pin, HIGH);
  if (s < 0) {
    analogWrite(s_pin, -s);
    digitalWrite(dir_pin, HIGH);
  } else {
    analogWrite(s_pin, s);
    digitalWrite(dir_pin, LOW);
  }
}

Motor::brake() {
  analogWrite(s_pin, 0);
  digitalWrite(br_pin, LOW);
}