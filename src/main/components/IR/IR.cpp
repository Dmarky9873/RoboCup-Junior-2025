#include "IR.h"

int pins[] = {23, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 16, 17, 20, 21, 22};
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

double* IR::getPWsArr() {
  double* pinReadings = new double[NUM_IR_PINS];
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinReadings[i] = pulseIn(pins[i], HIGH, 1000);
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