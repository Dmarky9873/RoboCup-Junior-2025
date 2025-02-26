#include <Pixy2I2C.h>

class Camera {
private:
  Pixy2I2C pixy;
  int32_t centerX;
  int32_t middleThreshold;
  float fov;
  int32_t frameWidth;

  const float knownWidth = 230.0;
  const float referenceDistance = 300.0;
  float focalLength;

public:
  Camera(float fieldOfView, int32_t threshold = 50)
    : fov(fieldOfView), middleThreshold(threshold) {}

  void initialize() {
    Serial.begin(115200);
    pixy.init();
    frameWidth = pixy.frameWidth;
    centerX = frameWidth / 2;
    focalLength = 0.0;

    // Continuously look for blocks and calibrate
    while (pixy.ccc.numBlocks == 0) {
      Serial.println("Waiting for a reference object...");
      pixy.ccc.getBlocks();  // Get blocks every time
      delay(500);
    }

    // Measure the detected width of the reference object
    int detectedWidth = pixy.ccc.blocks[0].m_width;
    focalLength = (detectedWidth * referenceDistance) / knownWidth;

    Serial.print("Calibrated Focal Length: ");
    Serial.println(focalLength, 2);
  }

  String detectDirection() {
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks > 0) {
      int32_t midX = pixy.ccc.blocks[0].m_x;
      if (midX > centerX - middleThreshold && midX < centerX + middleThreshold)
        return "CENTER";
      return (midX < centerX) ? "LEFT" : "RIGHT";
    }
    return "NO BLOCKS";
  }

  float findDistance() {
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks > 0) {
      int detectedWidth = pixy.ccc.blocks[0].m_width;
      if (detectedWidth > 0) {
        return (knownWidth * focalLength) / detectedWidth;
      }
    }
    return -1;
  }

  float calculateRotationAngle() {
    pixy.ccc.getBlocks();  // Continuously update the blocks
    if (pixy.ccc.numBlocks > 0) {
      int midX = pixy.ccc.blocks[0].m_x;
      float anglePerPixel = fov / frameWidth;
      return (midX - centerX) * anglePerPixel;
    }
    return 0.0;
  }

  void printStatus() {
    String direction = detectDirection();
    Serial.print("Direction: ");
    Serial.println(direction);

    if (pixy.ccc.numBlocks > 0) {
      float distance = findDistance();
      Serial.print("Distance from Object: ");
      Serial.println(distance > 0 ? String(distance, 2) + " mm" : "N/A");

      float rotationAngle = calculateRotationAngle();
      Serial.print("Rotation Angle: ");
      Serial.print(rotationAngle, 2);
      Serial.println(" degrees");
    } else {
      Serial.println("No object detected.");
    }
  }
};
