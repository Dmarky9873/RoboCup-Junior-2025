#include <Wire.h>
#include "colorsensor.h"

const uint8_t slaveAddress = 0x08;
const uint8_t numChannels = 16;
uint16_t analogValues[numChannels];
int buffer = 75;
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

  int delta = analogValues[0] - greenValues[0];
  Serial.println(delta);

  // front
  if (analogValues[15] >= greenValues[15] + buffer || analogValues[0] >= greenValues[0] + buffer || analogValues[1] >= greenValues[1] + buffer) {
    return 180;
  }

  // left
  if (analogValues[3] >= greenValues[3] + buffer || analogValues[4] >= greenValues[4] + buffer || analogValues[5] >= greenValues[5] + buffer) {
    return 90;
  }

  // back
  if (analogValues[7] >= greenValues[7] + buffer || analogValues[8] >= greenValues[8] + buffer || analogValues[9] >= greenValues[9] + buffer) {
    return 0;
  }

  // right
  if (analogValues[11] >= greenValues[11] + buffer || analogValues[12] >= greenValues[12] + buffer || analogValues[13] >= greenValues[13] + buffer) {
    return 270;
  }

  return -1;

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
