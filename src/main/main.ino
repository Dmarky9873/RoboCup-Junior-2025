#include "components/camera/camera.h"

Camera camera(70);

void setup()
{
  Serial.begin(9600);
  camera.initialize();
}

void loop()
{
  camera.printStatus();
  delay(100);
  Serial.println("works");
}
