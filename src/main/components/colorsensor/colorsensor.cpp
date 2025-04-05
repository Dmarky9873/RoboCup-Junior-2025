#include <SPI.h>
#include "colorsensor.h"

const int csPins[] = {36, 10};

// change these values when adjusting to new field
const int greenValues[] = {150, 100, 50, 50, 100, 100, 50, 50, 100, 50, 999, 50, 100, 100, 100, 200};

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

float ColorSensor::isDetected() {
  int buffer = 50;
  int result = -1;

  // front detection
  if (chips[1].readADC(6) > greenValues[14] + buffer || chips[1].readADC(7) > greenValues[15] + buffer || chips[0].readADC(0) > greenValues[0] + buffer || chips[0].readADC(1) > greenValues[1] + buffer) {
    result = 180;
  }
  if ((chips[1].readADC(5) > greenValues[13] + buffer || chips[1].readADC(4) > greenValues[12] + buffer) 
  && (chips[0].readADC(2) > greenValues[2] + buffer || chips[0].readADC(3) > greenValues[3] + buffer)) 
  {
    return 180;
  }

  // right detection
  if (chips[0].readADC(2) > greenValues[2] + buffer || chips[0].readADC(3) > greenValues[3] + buffer || chips[0].readADC(4) > greenValues[4] + buffer || chips[0].readADC(5) > greenValues[5] + buffer) {
    result = 90;
  }
  if ((chips[0].readADC(1) > greenValues[1] + buffer || chips[0].readADC(0) > greenValues[0] + buffer) 
  && (chips[0].readADC(6) > greenValues[6] + buffer || chips[0].readADC(7) > greenValues[7] + buffer)) 
  {
    return 90;
  }

  // back detection
  if (chips[0].readADC(6) > greenValues[6] + buffer || chips[0].readADC(7) > greenValues[7] + buffer || chips[1].readADC(0) > greenValues[8] + buffer || chips[1].readADC(1) > greenValues[9] + buffer) {
    result = 0;
  }
  if ((chips[0].readADC(4) > greenValues[4] + buffer || chips[0].readADC(5) > greenValues[5] + buffer) 
  && (chips[1].readADC(2) > greenValues[10] + buffer || chips[1].readADC(3) > greenValues[11] + buffer)) {
    return 0;
  }

  // left detection
  if (chips[1].readADC(2) > greenValues[10] + buffer || chips[1].readADC(3) > greenValues[11] + buffer || chips[1].readADC(4) > greenValues[12] + buffer || chips[1].readADC(5) > greenValues[13] + buffer) {
    result = 270;
  }
  if ((chips[1].readADC(6) > greenValues[14] + buffer || chips[1].readADC(7) > greenValues[15] + buffer)
  && (chips[1].readADC(0) > greenValues[8] + buffer || chips[1].readADC(1) > greenValues[9] + buffer)) 
  {
    return 270;
  }

  Serial.println(result);

  return result;

}

// bool ColorSensor::isDetected() {
//   for (int i = 0; i < NUM_CHIPS; i++) {
//     for (int j = 0; j < NUM_CHANNELS; j++) {
//       int val = chips[i].readADC(j);
//       if (val > greenValues[i * 8 + j] + 150) {
//         // Serial.print(val);
//         // Serial.print(" ");
//         // Serial.println(greenValues[i * 8 + j]);
//         return true;
//       }
//     }
//   }