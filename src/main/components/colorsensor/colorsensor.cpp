#include <Adafruit_MCP3008.h>
#include <SPI.h>
#include "colorsensor.h"

const int csPins[] = {36, 10};

// change these values when adjusting to new field
const int greenValues[] = {200, 150, 150, 150, 150, 150, 150, 150, 150, 150, 0, 150, 150, 150, 150, 250};
const int whiteValues[] = {950, 550, 550, 600, 500, 600, 550, 400, 450, 600, 999, 450, 650, 650, 500, 950};

const float angles[] = {0, 337.5, 315, 292.5, 270, 247.5, 225, 202.5, 180, 157.5, 135, 112.5, 90, 67.5, 45, 22.5};

void ColorSensor::init() {
  SPI.begin();
  Serial.println("START");
  for (int i = 0; i < NUM_CHIPS; i++) {
    // wait until chips are initialized 
    while (!chips[i].begin(csPins[i]));
  }
}

int* ColorSensor::getFilteredArr() {
  int* rawReadings = getReadingsArr();
  int* filteredReadings = new int[NUM_CHANNELS * NUM_CHIPS];

  for (int i = 0; i < NUM_CHIPS * NUM_CHANNELS; i++) {
    // set broken channel to value of prev channel
    if (i == 10) {
      filteredReadings[i] = filteredReadings[i - 1];
    }
    // Serial.println(map(float(rawReadings[i]), greenValues[i], whiteValues[i], 0, 1));
    if (map(float(rawReadings[i]), greenValues[i], whiteValues[i], 0, 1) > 0.5) {
      filteredReadings[i] = 1;
    }
    else {
      filteredReadings[i] = 0;
    }
  }

  return filteredReadings;
}

int* ColorSensor::getReadingsArr() {
  int* sensorReadings = new int[NUM_CHANNELS * NUM_CHIPS];

  for (int i = 0; i < NUM_CHIPS; i++) {
    for (int j = 0; j < NUM_CHANNELS; j++) {
      int val = chips[i].readADC(j);
      sensorReadings[i * 8 + j] = val;
    }
  }

  return sensorReadings;
}

void ColorSensor::debugRaw() {
  int* arr = getReadingsArr();
  Serial.print("[ ");
  for (int i = 0; i < NUM_CHIPS * NUM_CHANNELS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
  delay(100);
}

void ColorSensor::debugFiltered() {
  int* arr = getFilteredArr();
  Serial.print("[ ");
  for (int i = 0; i < NUM_CHIPS * NUM_CHANNELS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
  delay(100);
}

int ColorSensor::findArrayMidpoint(int* arr) {
  int maxLen = 0;
  int maxStart = -1;

  // find the longest string of 1s
  for (int i = 0; i < NUM_CHANNELS * NUM_CHIPS * 2; i++) {
    int start = i % (NUM_CHANNELS * NUM_CHIPS); 
    int len = 0;

    // count consecutive 1s
    while (arr[(start + len) % (NUM_CHANNELS * NUM_CHIPS)] == 1 && len < NUM_CHANNELS * NUM_CHIPS) {
      len++;
    }

    if (len > maxLen) {
      maxLen = len;
      maxStart = start;
    }

    i += len;  
  }

  if (maxLen > 0) {
    int midpoint = (maxStart + (maxLen / 2)) % (NUM_CHANNELS * NUM_CHIPS);
    return midpoint;
  }
  return -1;
}

float ColorSensor::getOOBDirection() {
  int midpoint = findArrayMidpoint(getFilteredArr());
  return midpoint != -1 ? angles[midpoint] : -1;
}