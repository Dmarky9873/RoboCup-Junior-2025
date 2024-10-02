#include "camera.h"

Camera pixyCam;

void setup() {
  Serial.begin(9600);
}

void loop() {
  String direction = pixyCam.getObjectDirection();
  float angleToRotate = pixyCam.getRotationDistance();
  Serial.print("Angle to Rotate: ");
  Serial.print(angleToRotate);
  Serial.println(" degrees");
  Serial.println("Direction: " + direction);

  delay(100);
}
