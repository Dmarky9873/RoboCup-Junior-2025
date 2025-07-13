#include <Wire.h>
#include "colorsensor.h"

const uint8_t slaveAddress = 0x08;
const uint8_t numChannels = 16;
uint16_t analogValues[numChannels];
// int whiteThreshold = 990;
int whiteValues[numChannels] = { 1001, 933, 1000, 980, 1007, 979, 971, 1007, 1007, 1009, 998, 1005, 991, 990, 1010, 1008 };
int greenValues[numChannels] = { 578, 421, 488, 497, 365, 711, 552, 485, 881, 887, 884, 781, 825, 795, 806, 844 };

void ColorSensor::init() {
  Wire.begin();
}

void ColorSensor::updateReadings() {
  Wire.requestFrom(slaveAddress, numChannels * 2);  // 32 bytes total

  int index = 0;
  while (Wire.available() >= 2 && index < numChannels) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    analogValues[index++] = (msb << 8) | lsb;
  }
}

void ColorSensor::printMappedValues() {
  Serial.println("Mapped Whiteness Values (0 = green, 1 = white):");

  for (int i = 0; i < numChannels; i++) {
    int value = analogValues[i];
    int green = greenValues[i];
    int white = whiteValues[i];

    float whiteness = 0.0;

    if (white != green) {
      whiteness = constrain((float)(value - green) / (white - green), 0.0, 1.0);
    }

    Serial.print(i);
    Serial.print(": ");
    Serial.print(whiteness, 2); // 2 decimal places
    Serial.print("\t");
  }

  Serial.println();
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
    int value = analogValues[i];
    int green = greenValues[i];
    int white = whiteValues[i];

    if (white == green) continue;

    float whiteness = constrain((float)(value - green) / (white - green), 0.0, 1.0);


    if (whiteness > 0.5) {
      float angle = fmod(360.0 - i * (360.0 / numChannels), 360.0);
      weightedSum += angle * whiteness;
      totalWeight += whiteness;
    }
  }


  if (totalWeight == 0) {
    return -1;  // nothing detected
  }

  float averageAngle = weightedSum / totalWeight;

  averageAngle = fmod(averageAngle + 180.0, 360.0);

  return averageAngle;
}
