struct Movement {
  private:
    Motor motor_0{1, 3, 2};
    Motor motor_1{7, 9, 8};
    Motor motor_2{28, 35, 29};
    Motor motor_3{4, 6, 5};
    Motor motors[4] = {motor_0, motor_1, motor_2, motor_3};
    Compass compass;

  public:
    void initMotor() {
      compass.initialize();
    }

    void rotate(int speed) {
      for (int i = 0; i < 4; i++) {
        motors[i].spin(speed);
      }
    }

    void brake() {
      for (int i = 0; i < 4; i++) {
        motors[i].brake();
      }
    }

    void pointNorth(int baseSpeed) {
      int speed = 0;
      while (!compass.isBetween(COMPASS_BUFF * -1, COMPASS_BUFF, compass.readCompass())) {
        speed = baseSpeed - abs(abs(compass.readCompass()) - COMPASS_BUFF) * 0.3;
        rotate((compass.readCompass() > 0) ? speed : -speed);
      }
      brake();
    }

    void moveNorth(unsigned int speed) {
      pointNorth(220);
      motors[0].spin(speed);
      motors[1].spin(speed);
      motors[2].spin(-speed);
      motors[3].spin(-speed);
    }

    void moveSouth(unsigned int speed) {
      pointNorth(220);
      motors[0].spin(-speed);
      motors[1].spin(-speed);
      motors[2].spin(speed);
      motors[3].spin(speed);
    }

    void moveEast(unsigned int speed) {
      pointNorth(220);
      motors[0].spin(speed);
      motors[1].spin(-speed);
      motors[2].spin(-speed);
      motors[3].spin(speed);
    }

    void moveWest(unsigned int speed) {
      pointNorth(220);
      motors[0].spin(-speed);
      motors[1].spin(speed);
      motors[2].spin(speed);
      motors[3].spin(-speed);
    }

    void moveNorthEast(unsigned int speed) {
      pointNorth(220);
      motors[0].spin(speed);
      motors[1].brake();
      motors[2].spin(-speed);
      motors[3].brake();
    }

    void moveNorthWest(unsigned int speed) {
      pointNorth(220);
      motors[0].brake();
      motors[1].spin(speed);
      motors[2].brake();
      motors[3].spin(-speed);
    }

    void moveSouthEast(unsigned int speed) {
      pointNorth(220);
      motors[0].brake();
      motors[1].spin(-speed);
      motors[2].brake();
      motors[3].spin(speed);
    }

    void moveSouthWest(unsigned int speed) {
      pointNorth(220);
      motors[0].spin(-speed);
      motors[1].brake();
      motors[2].spin(speed);
      motors[3].brake();
    }
};