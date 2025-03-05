#include "components/camera/camera.h"

Camera camera(70);

void setup()
{
  camera.initialize();
}

void loop()
{
  camera.printStatus();
  delay(100);
}
