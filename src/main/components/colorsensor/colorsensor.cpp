#include <SPI.h>
#include "colorsensor.h"

const int csPins[] = {36, 10};

// change these values when adjusting to new field
const int greenValues[] = {450, 250, 250, 250, 250, 250, 250, 250, 250, 250, 999, 250, 250, 250, 250, 500};

const float angles[] = {0, 337.5, 315, 292.5, 270, 247.5, 225, 202.5, 180, 157.5, 135, 112.5, 90, 67.5, 45, 22.5};

void ColorSensor::init() {
  SPI.begin();
  for (int i = 0; i < NUM_CHIPS; i++) {
    // wait until chips are initialized 
    while (!chips[i].begin(csPins[i]));
  }
}

void ColorSensor::printReadings() {
  for (int i = 0; i < NUM_CHIPS; i++) {
    Serial.println();
    Serial.print("Chip ");
    Serial.print(i + 1);
    Serial.println();
    for (int j = 0; j < NUM_CHANNELS; j++) {
      int val = chips[i].readADC(j);
      Serial.print("Channel ");
      Serial.print(j);
      Serial.print(": ");
      Serial.println(val);
    }
  }
}

int ColorSensor::frontDetected() {
  if (chips[1].readADC(6) > greenValues[14] + 100 || chips[1].readADC(7) > greenValues[15] + 100 || chips[0].readADC(0) > greenValues[0] + 100 || chips[0].readADC(1) > greenValues[1] + 100) {
    return 0;
  }

  return 1;
}

int ColorSensor::rightDetected() {
  if (chips[0].readADC(2) > greenValues[2] + 100 || chips[0].readADC(3) > greenValues[3] + 100 || chips[0].readADC(4) > greenValues[4] + 100 || chips[0].readADC(5) > greenValues[5] + 100) {
    return 0;
  }

  return 1;
}

int ColorSensor::backDetected() {
  if (chips[0].readADC(6) > greenValues[6] + 100 || chips[0].readADC(7) > greenValues[7] + 100 || chips[1].readADC(0) > greenValues[8] + 100 || chips[1].readADC(1) > greenValues[9] + 100) {
    return 0;
  }

  return 1;
}

int ColorSensor::leftDetected() {
  if (chips[1].readADC(2) > greenValues[10] + 100 || chips[1].readADC(3) > greenValues[11] + 100 || chips[1].readADC(4) > greenValues[12] + 100 || chips[1].readADC(5) > greenValues[13] + 100) {
    return 0;
  }

  return 1;
}

bool ColorSensor::isDetected() {
  for (int i = 0; i < NUM_CHIPS; i++) {
    for (int j = 0; j < NUM_CHANNELS; j++) {
      int val = chips[i].readADC(j);
      if (val > greenValues[i * 8 + j] + 100) {
        // Serial.print(val);
        // Serial.print(" ");
        // Serial.println(greenValues[i * 8 + j]);
        return true;
      }
    }
  }

  return false;
}