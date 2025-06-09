#include <SPI.h>
#include "colorsensor.h"

const int csPins[] = {36, 37};
const int buffer = 50;

// change these values when adjusting to new field
int greenValues[16];

void ColorSensor::init() {
  SPI.begin();
  for (int i = 0; i < NUM_CHIPS; i++) {
    // wait until chips are initialized 
    while (!chips[i].begin(csPins[i]));
  }

  for (int i = 0; i < 16; i++) {
    greenValues[i] = chips[i/8].readADC(i%8);
    
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
      Serial.print(j);
      Serial.print(": ");
      Serial.print(val);
      Serial.print("\t");
    }
  }
    Serial.println();
}

int ColorSensor::countFront() {
  int count = 0;
  if (chips[1].readADC(6) > greenValues[14] + buffer) {
    count++;
  }
  if (chips[1].readADC(7) > greenValues[15] + buffer) {
    count++;
  }
  if (chips[0].readADC(0) > greenValues[0] + buffer) {
    count++;
  }
  if (chips[0].readADC(1) > greenValues[1] + buffer) {
    count++;
  }

  return count;
}

int ColorSensor::countRight() {
  int count = 0;
  if (chips[0].readADC(2) > greenValues[2] + buffer) {
    count++;
  }
  if (chips[0].readADC(3) > greenValues[3] + buffer) {
    count++;
  }
  if (chips[0].readADC(4) > greenValues[4] + buffer) {
    count++;
  }
  if (chips[0].readADC(5) > greenValues[5] + buffer) {
    count++;
  }

  return count;
}

int ColorSensor::countBack() {
  int count = 0;
  if (chips[0].readADC(6) > greenValues[6] + buffer) {
    count++;
  }
  if (chips[0].readADC(7) > greenValues[7] + buffer) {
    count++;
  }
  if (chips[1].readADC(0) > greenValues[8] + buffer) {
    count++;
  }
  if (chips[1].readADC(1) > greenValues[9] + buffer) {
    count++;
  }

  return count;
}

int ColorSensor::countLeft() {
  int count = 0;
  if (chips[1].readADC(2) > greenValues[10] + buffer) {
    count++;
  }
  if (chips[1].readADC(3) > greenValues[11] + buffer) {
    count++;
  }
  if (chips[1].readADC(4) > greenValues[12] + buffer) {
    count++;
  }
  if (chips[1].readADC(5) > greenValues[13] + buffer) {
    count++;
  }

  return count;
}

float ColorSensor::isDetected() {
  int buffer = 100;
  int result = -1;

  // front detection
  if (countFront() >= 2) {
    result = 180;
  }
  if ((chips[1].readADC(5) > greenValues[13] + buffer || chips[1].readADC(4) > greenValues[12] + buffer) 
  && (chips[0].readADC(2) > greenValues[2] + buffer || chips[0].readADC(3) > greenValues[3] + buffer)) 
  {
    return 180;
  }

  // right detection
  if (countRight() >= 2) {
    result = 90;
  }
  if ((chips[0].readADC(1) > greenValues[1] + buffer || chips[0].readADC(0) > greenValues[0] + buffer) 
  && (chips[0].readADC(6) > greenValues[6] + buffer || chips[0].readADC(7) > greenValues[7] + buffer)) 
  {
    Serial.println("forced 90");
    return 90;
  }

  // back detection
  if (countBack() >= 1) {
    result = 0;
  }
  if ((chips[0].readADC(4) > greenValues[4] + buffer || chips[0].readADC(5) > greenValues[5] + buffer) 
  && (chips[1].readADC(2) > greenValues[10] + buffer || chips[1].readADC(3) > greenValues[11] + buffer)) {
    Serial.println("forced 0");
    return 0;
  }

  // left detection
  if (countLeft() >= 2) {
    result = 270;
  }
  if ((chips[1].readADC(6) > greenValues[14] + buffer || chips[1].readADC(7) > greenValues[15] + buffer)
  && (chips[1].readADC(0) > greenValues[8] + buffer || chips[1].readADC(1) > greenValues[9] + buffer)) 
  {
    Serial.println("forced 270");
    return 270;
  }

  //Serial.println(result);

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
