class Movement {

  public:
    void initMotor();

    void rotate(int speed);

    void brake();

    void pointNorth(int baseSpeed);

    void moveNorth(unsigned int speed);

    void moveSouth(unsigned int speed);

    void moveEast(unsigned int speed);

    void moveWest(unsigned int speed);

    void moveNorthEast(unsigned int speed);

    void moveNorthWest(unsigned int speed);

    void moveSouthEast(unsigned int speed);

    void moveSouthWest(unsigned int speed);
    
  private:
    Motor motor_0{1, 3, 2};
    Motor motor_1{7, 9, 8};
    Motor motor_2{28, 35, 29};
    Motor motor_3{4, 6, 5};
    Motor motors[4];
    Compass compass;
};