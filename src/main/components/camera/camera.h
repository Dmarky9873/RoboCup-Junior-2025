#include <Pixy2I2C.h>

class Camera {
private:
  Pixy2I2C pixy;
  int32_t centerX;
  int32_t middleThreshold;
  float fov;  // Field of View
  int32_t frameWidth;

<<<<<<< Updated upstream
  const float knownWidth = 200.0;    // Object's real-world width in mm
  const float focalLength = 149.22;  // Effective focal length in pixels
=======
  const float knownWidth = 200.0;
  const float focalLength = 149.22;
>>>>>>> Stashed changes

public:
  Camera(float fieldOfView, int32_t threshold = 50)
    : fov(fieldOfView), middleThreshold(threshold) {}

  void initialize() {
    Serial.begin(115200);
    pixy.init();
<<<<<<< Updated upstream
    frameWidth = pixy.frameWidth;  // Assume Pixy2 has this member or define manually
=======
    frameWidth = pixy.frameWidth;
>>>>>>> Stashed changes
    centerX = frameWidth / 2;
  }

  String detectDirection() {
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks > 0) {
<<<<<<< Updated upstream
      int32_t midX = pixy.ccc.blocks[0].m_x;  // X position of the first block
=======
      int32_t midX = pixy.ccc.blocks[0].m_x;
>>>>>>> Stashed changes
      if (midX > centerX - middleThreshold && midX < centerX + middleThreshold) {
        return "CENTER";
      } else if (midX < centerX) {
        return "LEFT";
      } else {
        return "RIGHT";
      }
    }
    return "NO BLOCKS";
  }

<<<<<<< Updated upstream
  float calculateRotationDistance() {
    if (pixy.ccc.numBlocks > 0) {
      int32_t midX = pixy.ccc.blocks[0].m_x;  // X position of the first block
      int32_t distanceFromCenter = abs(centerX - midX);
      return ((fov / frameWidth) * distanceFromCenter) * 0.45;
    }
    return 0.0;  // No blocks detected, no rotation distance
  }

  float calculateDistance() {
    if (pixy.ccc.numBlocks > 0) {
      int32_t blockWidth = pixy.ccc.blocks[0].m_width;  // Width of the first detected block
      if (blockWidth > 0) {
        return (knownWidth * focalLength) / blockWidth;  // Distance calculation
      }
    }
    return -1.0;  // Return -1 if no valid block width is found
=======
  float calculateDistance() {
    if (pixy.ccc.numBlocks > 0) {
      int32_t blockWidth = pixy.ccc.blocks[0].m_width;
      if (blockWidth > 0) {
        return (knownWidth * focalLength) / blockWidth;
      }
    }
    return -1.0;
>>>>>>> Stashed changes
  }

  float calculateRotationAngle() {
    if (pixy.ccc.numBlocks > 0) {
      int32_t midX = pixy.ccc.blocks[0].m_x;  // X position of the first block
      int32_t offset = midX - centerX;        // Pixels offset from the center
      float anglePerPixel = fov / frameWidth;
      return offset * anglePerPixel;  // Angle to rotate in degrees
    }
<<<<<<< Updated upstream
    return 0.0;  // No blocks detected, no angle
=======
    return 0.0;
>>>>>>> Stashed changes
  }

  void printStatus() {
    String direction = detectDirection();
    Serial.print("Direction: ");
    Serial.println(direction);

    if (direction != "NO BLOCKS") {
<<<<<<< Updated upstream
      // Calculate and print distance from the object
=======
>>>>>>> Stashed changes
      float distance = calculateDistance();
      Serial.print("Distance from Object: ");
      if (distance > 0) {
        Serial.print(distance, 2);
        Serial.println(" mm");
      } else {
        Serial.println("N/A");
      }

      float rotationAngle = calculateRotationAngle();
      Serial.print("Rotation Angle: ");
      Serial.print(rotationAngle, 2);
      Serial.println(" degrees");
    }
  }
};