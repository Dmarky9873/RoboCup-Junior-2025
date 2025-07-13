#include <Wire.h>
#include "colorsensor.h"

const uint8_t slaveAddress = 0x08;
const uint8_t numChannels = 16;
uint16_t analogValues[numChannels];
int whiteThreshold = 990;

void ColorSensor::init() {
  Wire.begin();
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

float ColorSensor::getAvoidAngle() {
  float totalWeight = 0;
  float weightedSum = 0;

  for (int i = 0; i < numChannels; i++) {
    if (analogValues[i] >= whiteThreshold) {
      float angle = fmod(360.0 - i * (360.0 / numChannels), 360.0);
      weightedSum += angle;
      totalWeight += 1;
    }
  }

  if (totalWeight == 0) {
    return -1; // nothing detected
  }

  float averageAngle = weightedSum / totalWeight;

  averageAngle = fmod(averageAngle + 180.0, 360.0);

  return averageAngle;
}
