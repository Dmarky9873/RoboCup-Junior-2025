#include "IR.h"

int pins[] = {34, 35, 16, 17, 20, 21, 22, 23, 26, 27, 28, 29, 30, 31, 32, 33};
float angles[] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5};
int NUM_IR_PINS = 16;

void IR::initIR() {
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinMode(pins[i], INPUT);
  }
}

// int* IR::getReadingsArr() {
//   int* pinReadings = new int[NUM_IR_PINS];
//   double reading;
//   for (unsigned int i = 0; i < arrayLength(pins); i++) {
//     reading = pulseIn(pins[i], HIGH, 750);
//     // Serial.println(reading);
//     if (reading > 0.05){
//       pinReadings[i] = 1;
//     } else {
//       pinReadings[i] = 0;
//     }
//   }
//   return pinReadings;
// }

float* IR::getReadingsArr() {
  double* pwReadings = getPWsArr();
  float* pinReadings = new float[NUM_IR_PINS];

  double minVal = pwReadings[0];
  double maxVal = pwReadings[0];

  for (int i = 1; i < NUM_IR_PINS; i++) {
    if (pwReadings[i] < minVal) minVal = pwReadings[i];
    if (pwReadings[i] > maxVal) maxVal = pwReadings[i];
  }

  if (abs(minVal - maxVal) < 30) {
      for (int i = 0; i < NUM_IR_PINS; i++) {
          pinReadings[i] = 0;
      }
      return pinReadings;
  }

  double range = maxVal - minVal;
  for (int i = 0; i < NUM_IR_PINS; i++) {
      pinReadings[i] = (float)(1 - ((pwReadings[i] - minVal) / range));
  }

  return pinReadings;
}

int findLongestOnesMidpoint(float arr[], int n) {
    int maxLen = 0, maxStart = -1;
    int curLen = 0, curStart = -1;
    
    // extend array to handle circularity
    float extendedArr[2 * n];
    for (int i = 0; i < n; i++) {
        extendedArr[i] = arr[i];
        extendedArr[i + n] = arr[i];
    }
    
    // dind longest sequence of 1s in extended array
    for (int i = 0; i < 2 * n; i++) {
        if (extendedArr[i] == 1) {
            if (curLen == 0) curStart = i;
            curLen++;
        } else {
            if (curLen > maxLen) {
                maxLen = curLen;
                maxStart = curStart;
            }
            curLen = 0;
        }
    }
    
    // edge case: if last counted sequence is the longest
    if (curLen > maxLen) {
        maxLen = curLen;
        maxStart = curStart;
    }
    
    // find midpoint in original array
    int midIndex = maxStart + maxLen / 2;
    return midIndex % n;
}


float IR::getBallAngle() {
  float* arr = getReadingsArr();
  float total = 0;

  for (int i = 0; i < NUM_IR_PINS; i++) {
    total += arr[i];
  }

  if (total < 1) {
    return -1;
  }

  int index = findLongestOnesMidpoint(arr, NUM_IR_PINS);

  return angles[index];
}

double* IR::getPWsArr() {
  double* pinReadings = new double[NUM_IR_PINS];
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinReadings[i] = pulseIn(pins[i], HIGH, 500);
  }
  return pinReadings;
}

void IR::printReadingsArr() {
  float* arr = getReadingsArr();
  Serial.print("[ ");
  for(int i = 0; i < NUM_IR_PINS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
}

void IR::printPWsArr() {
  double* arr = getPWsArr();
  Serial.print("[ ");
  for(int i = 0; i < NUM_IR_PINS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
  delay(500);
}