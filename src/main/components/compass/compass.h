struct Compass {
  Adafruit_BNO055 bno;

  void initialize() {
    bno = Adafruit_BNO055(55, 0x28, &Wire2);
    if (!bno.begin()) {
      Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      while(1);
    }
    bno.setExtCrystalUse(true);
  }

  float readCompass() {
    sensors_event_t event;
    bno.getEvent(&event);
    int angle = event.orientation.x;
    return (angle > 180) ? angle - 360 : angle;
  }

  boolean isBetween(int lower, int upper, int x) {
    return lower < x && x < upper;
  }

  boolean isNorth() {
    return isBetween(COMPASS_BUFF * -1, COMPASS_BUFF, readCompass());
  }
};