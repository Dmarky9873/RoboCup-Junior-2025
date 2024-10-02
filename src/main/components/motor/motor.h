#include <Adafruit_BNO055.h>

const unsigned int COMPASS_BUFF = 13;

struct Motor {
  unsigned int s_pin;
  unsigned int dir_pin;
  unsigned int br_pin;

  Motor(unsigned int pin_, unsigned int dir_pin_, unsigned int br_pin_)
      : s_pin(pin_), dir_pin(dir_pin_), br_pin(br_pin_) {
    pinMode(s_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(br_pin, OUTPUT);
  }

  void spin(int s) {
    digitalWrite(br_pin, HIGH);
    if (s < 0) {
      analogWrite(s_pin, -s);
      digitalWrite(dir_pin, HIGH);
    } else {
      analogWrite(s_pin, s);
      digitalWrite(dir_pin, LOW);
    }
  }

  void brake() {
    analogWrite(s_pin, 0);
    digitalWrite(br_pin, LOW);
  }
};

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
