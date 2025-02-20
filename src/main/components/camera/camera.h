#include <Pixy2I2C.h>

class Camera {
private:
  Pixy2I2C pixy;
  int32_t centerX;
  int32_t middleThreshold;
<<<<<<< Updated upstream
  float fov;  // Field of View
  int32_t frameWidth;

<<<<<<< Updated upstream
  const float knownWidth = 200.0;    // Object's real-world width in mm
  const float focalLength = 149.22;  // Effective focal length in pixels
=======
  const float knownWidth = 200.0;
  const float focalLength = 149.22;
>>>>>>> Stashed changes
=======
  float fov;
  int32_t frameWidth;

  const float knownWidth = 230.0;  // Width of the object you're measuring (mm)
  const float referenceDistance = 300.0;  // Distance to reference object (mm)
  float focalLength;
>>>>>>> Stashed changes

public:
  Camera(float fieldOfView, int32_t threshold = 50)
    : fov(fieldOfView), middleThreshold(threshold) {}

  void initialize() {
    Serial.begin(115200);
    pixy.init();
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    frameWidth = pixy.frameWidth;  // Assume Pixy2 has this member or define manually
=======
    frameWidth = pixy.frameWidth;
>>>>>>> Stashed changes
=======
    frameWidth = pixy.frameWidth;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
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
=======
      int32_t midX = pixy.ccc.blocks[0].m_x;
      if (midX > centerX - middleThreshold && midX < centerX + middleThreshold)
        return "CENTER";
      return (midX < centerX) ? "LEFT" : "RIGHT";
>>>>>>> Stashed changes
    }
    return "NO BLOCKS";
  }

<<<<<<< Updated upstream
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

=======
  float findDistance() {
    pixy.ccc.getBlocks();  // Always get blocks to update the state
    if (pixy.ccc.numBlocks > 0) {
      int detectedWidth = pixy.ccc.blocks[0].m_width;
      if (detectedWidth > 0) {
        return (knownWidth * focalLength) / detectedWidth;  // Distance calculation
      }
    }
    return -1;  // No valid block detected
  }

  float calculateRotationAngle() {
    pixy.ccc.getBlocks();  // Continuously update the blocks
    if (pixy.ccc.numBlocks > 0) {
      int midX = pixy.ccc.blocks[0].m_x;
      float anglePerPixel = fov / frameWidth;
      return (midX - centerX) * anglePerPixel;
    }
    return 0.0;  // No rotation angle if no blocks are detected
  }

>>>>>>> Stashed changes
  void printStatus() {
    String direction = detectDirection();
    Serial.print("Direction: ");
    Serial.println(direction);

<<<<<<< Updated upstream
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
=======
    if (pixy.ccc.numBlocks > 0) {
      float distance = findDistance();
      Serial.print("Distance from Object: ");
      Serial.println(distance > 0 ? String(distance, 2) + " mm" : "N/A");
>>>>>>> Stashed changes

      float rotationAngle = calculateRotationAngle();
      Serial.print("Rotation Angle: ");
      Serial.print(rotationAngle, 2);
      Serial.println(" degrees");
    } else {
      Serial.println("No object detected.");
    }
  }
};
