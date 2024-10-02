#ifndef CAMERA_H
#define CAMERA_H

#include <SPI.h>
#include <Pixy2.h>

class Camera {
  private:
    Pixy2 pixy;
    int32_t centerX;
    int32_t middleThreshold;
    float fov;
    int32_t frameWidth;

  public:
    Camera() {
      pixy.init();
      frameWidth = pixy.frameWidth;
      centerX = frameWidth / 2;
      middleThreshold = 50;
      fov = 70.0;
    }

    String getObjectDirection() {
      int32_t blocks;
      blocks = pixy.ccc.getBlocks();

      if (blocks) {
        int32_t midX = pixy.ccc.blocks[0].m_x;

        if (midX > centerX - middleThreshold && midX < centerX + middleThreshold) {
          return "CENTER";
        } else if (midX < centerX) {
          return "LEFT";
        } else {
          return "RIGHT";
        }
      } else {
        return "NONE";
      }
    }

    float getRotationDistance() {
      int32_t blocks;
      blocks = pixy.ccc.getBlocks();

      if (blocks) {
        int32_t midX = pixy.ccc.blocks[0].m_x;
        int32_t distanceFromCenter = abs(centerX - midX);
        return ((fov / frameWidth) * distanceFromCenter) * 0.45;
      } else {
        return -1;
      }
    }
};

#endif // CAMERA_H
