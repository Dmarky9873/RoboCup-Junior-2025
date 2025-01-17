#include "camera.h"
Camera camera(70.0);  // Instantiate Camera with a 70-degree field of view

void setup() {
    camera.initialize();
}

void loop() {
    camera.printStatus();
}
