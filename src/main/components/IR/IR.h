#include "/"

class IR : public Component {
public:

  template <typename T, size_t N>
  size_t arrayLength(const T (&)(N));
  int* getReadingsArr();

  double* getPWsArr();

  void printReadingsArr();
  void printPWsArr();

  void initIR();

  /* 

  Other IR functions from 2024 are outdated 
  Since we are implementing an ADC, we are no longer limited to 0s and 1s

  TO-DO: Design an algorithm to detect where the ball is located relative to the robot
  (return a double in degrees)

  */


}