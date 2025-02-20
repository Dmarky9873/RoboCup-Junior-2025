<<<<<<< Updated upstream
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
=======
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
>>>>>>> Stashed changes
