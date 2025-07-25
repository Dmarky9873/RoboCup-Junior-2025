#include "IR.h"
#include <limits.h>

int pins[] = {38, 39, 20, 21, 22, 23, 31, 32, 24, 25, 26, 27, 14, 15, 16, 17}; //{23, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 16, 17, 20, 21, 22};
const int NUM_IR_PINS = 16;

double readings[NUM_IR_PINS];

void IR::initIR() {
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinMode(pins[i], INPUT);
  }
}

void IR::updateReadings() {
  double minVal = INT_MAX;
  double maxVal = INT_MIN;

  for (int i = 0; i < NUM_IR_PINS; i++) {
    double pwReading = pulseIn(pins[i], HIGH, 800);
    if (pwReading != 0 && pwReading < minVal) minVal = pwReading;
    if (pwReading > maxVal) maxVal = pwReading;
  }

  if (minVal == INT_MAX || maxVal == INT_MIN) {
    for (int i = 0; i < NUM_IR_PINS; i++) {
      readings[i] = 0;
    }
  }

  double range = maxVal - minVal;
  for (int i = 0; i < NUM_IR_PINS; i++) {
    double pwReading = pulseIn(pins[i], HIGH, 800);
    if (pwReading == 0) {
      readings[i] = 0;
    }
    else {
      readings[i] = (float)(1 - ((pwReading - minVal) / range));
    }
  }
}

// float* IR::getReadingsArr() {
//   double* pwReadings = getPWsArr();
//   float* pinReadings = new float[NUM_IR_PINS];

//   double minVal = INT_MAX;
//   double maxVal = INT_MIN;

//   for (int i = 0; i < NUM_IR_PINS; i++) {
//     if (pwReadings[i] != 0 && pwReadings[i] < minVal) minVal = pwReadings[i];
//     if (pwReadings[i] > maxVal) maxVal = pwReadings[i];
//   }

//   if (minVal == INT_MAX || maxVal == INT_MIN) {
//     for (int i = 0; i < NUM_IR_PINS; i++) {
//       pinReadings[i] = 0;
//     }
//     return pinReadings;
//   }

//   double range = maxVal - minVal;
//   for (int i = 0; i < NUM_IR_PINS; i++) {
//     if (pwReadings[i] == 0) {
//       pinReadings[i] = 0;
//     }
//     else {
//       pinReadings[i] = (float)(1 - ((pwReadings[i] - minVal) / range));
//     }
//   }

//   return pinReadings;
// }

float IR::getBallAngle() {
  int n = NUM_IR_PINS;

  int dampen = 2.5;
  float weightedX = 0; 
  float weightedY = 0;
  float totalWeight = 0;

  for (int i = 0; i < n; i++) {
    float weight = readings[i] > 0.95 ? 1 : readings[i];
    float angleRad = (i * 2.0 * M_PI) / n;

    if (weight < 0.5) continue;

    float adjustedWeight = pow(weight, dampen);

    weightedX += adjustedWeight * cos(angleRad);  
    weightedY += adjustedWeight * sin(angleRad);
    totalWeight += adjustedWeight;
  }

  if (totalWeight == 0) {
      return -1; 
  }

  float normX = weightedX / totalWeight;
  float normY = weightedY / totalWeight;

  float angle = atan2(normY, normX) * (180.0 / M_PI);

  if (angle < 0) angle += 360.0;

  return angle;
}


// double* IR::getPWsArr() {
//   double* pinReadings = new double[NUM_IR_PINS];
//   for (unsigned int i = 0; i < arrayLength(pins); i++) {
//     pinReadings[i] = pulseIn(pins[i], HIGH, 800);
//   }
//   return pinReadings;
// }

// void IR::printReadingsArr() {
//   Serial.print("[ ");
//   for(int i = 0; i < NUM_IR_PINS; i++) {
//     Serial.print(readings[i]);
//     Serial.print(" ");
//   }
//   Serial.println("]");
// }

// void IR::printPWsArr() {
//   double* arr = getPWsArr();
//   Serial.print("[ ");
//   for(int i = 0; i < NUM_IR_PINS; i++) {
//     Serial.print(arr[i]);
//     Serial.print(" ");
//   }
//   Serial.println("]");
// }