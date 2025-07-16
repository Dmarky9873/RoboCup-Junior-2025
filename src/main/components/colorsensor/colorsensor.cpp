#include <Wire.h>
#include "colorsensor.h"

const uint8_t slaveAddress = 0x08;
const uint8_t numChannels = 16;
uint16_t analogValues[numChannels];
int buffer = 150;
uint16_t greenValues[numChannels];
// int greenValues[] = {250, 400, 450, 450, 300, 650, 500, 400, 500, 600, 400, 250, 200, 250, 200, 400};

void ColorSensor::init() {
  Wire.begin();
  updateReadings();
  while (analogValues[0] == 0) {}
  for (int i = 0; i < numChannels; i++) {
    greenValues[i] = analogValues[i];
  }
}
uint16_t* ColorSensor::getAnalogValues() {
  return analogValues;
}

int ColorSensor::countFront() {
  int count = 0;
  if (analogValues[15] > greenValues[15] + buffer) {
    count++;
  }
  if (analogValues[0] > greenValues[0] + buffer) {
    count++;
  }
  if (analogValues[1] > greenValues[1] + buffer) {
    count++;
  }

  return count;
}


int ColorSensor::countRight() {
  int count = 0;
  if (analogValues[3] > greenValues[3] + buffer) {
    count++;
  }
  if (analogValues[4] > greenValues[4] + buffer) {
    count++;
  }
  if (analogValues[5] > greenValues[5] + buffer) {
    count++;
  }

  return count;
}

int ColorSensor::countBack() {
  int count = 0;
  if (analogValues[7] > greenValues[7] + buffer) {
    count++;
  }
  if (analogValues[8] > greenValues[8] + buffer) {
    count++;
  }
  if (analogValues[9] > greenValues[9] + buffer) {
    count++;
  }

  return count;
}

int ColorSensor::countLeft() {
  int count = 0;
  if (analogValues[11] > greenValues[11] + buffer) {
    count++;
  }
  if (analogValues[12] > greenValues[12] + buffer) {
    count++;
  }
  if (analogValues[13] > greenValues[13] + buffer) {
    count++;
  }

  return count;
}

void ColorSensor::updateReadings() {
  Wire.requestFrom(slaveAddress, numChannels * 2); // 32 bytes total

  int index = 0;
  while (Wire.available() >= 2 && index < numChannels) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    analogValues[index++] = (msb << 8) | lsb;
  }
}

void ColorSensor::printReadings() {
  for (int i = 0; i < numChannels; i++) {
    Serial.print(i);
    Serial.print(": "); 
    Serial.print(analogValues[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void ColorSensor::printGreenValues() {
  for (int i = 0; i < numChannels; i++) {
    Serial.print(i);
    Serial.print(": "); 
    Serial.print(greenValues[i]);
    Serial.print("\t");
  }
  Serial.println();
}

float ColorSensor::getAvoidAngle() {

  int result = -1;

  // front detection
  if (countFront() >= 1) {
    result = 180;
  }
  if ((analogValues[14] > greenValues[14] + buffer || analogValues[13] > greenValues[13] + buffer) 
  && (analogValues[2] > greenValues[2] + buffer || analogValues[3] > greenValues[3] + buffer)) 
  {
    return 180;
  }

  // right detection
  if (countRight() >= 1) {
    result = 90;
  }
  if ((analogValues[1] > greenValues[1] + buffer || analogValues[2] > greenValues[2] + buffer) 
  && (analogValues[6] > greenValues[6] + buffer || analogValues[7] > greenValues[7] + buffer)) 
  {
    Serial.println("forced 90");
    return 90;
  }

  // back detection
  if (countBack() >= 1) {
    result = 0;
  }
  if ((analogValues[6] > greenValues[6] + buffer || analogValues[5] > greenValues[5] + buffer) 
  && (analogValues[10] > greenValues[10] + buffer || analogValues[11] > greenValues[11] + buffer)) {
    Serial.println("forced 0");
    return 0;
  }

  // left detection
  if (countLeft() >= 1) {
    result = 270;
  }
  if ((analogValues[14] > greenValues[14] + buffer || analogValues[15] > greenValues[15] + buffer)
  && (analogValues[10] > greenValues[10] + buffer || analogValues[9] > greenValues[9] + buffer)) 
  {
    Serial.println("forced 270");
    return 270;
  }

  return result;

  // float totalWeight = 0;
  // float weightedSum = 0;

  // for (int i = 0; i < numChannels; i++) {
  //   if (analogValues[i] >= greenValues[i] + buffer) {
  //     float angle = fmod(360.0 - i * (360.0 / numChannels), 360.0);
  //     weightedSum += angle;
  //     totalWeight += 1;
  //   }
  // }

  // if (totalWeight == 0) {
  //   return -1; // nothing detected
  // }

  // float averageAngle = weightedSum / totalWeight;

  // averageAngle = fmod(averageAngle + 180.0, 360.0);

  // return averageAngle;
}
