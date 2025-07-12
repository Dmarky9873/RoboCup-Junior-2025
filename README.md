# RoboCup-Junior-2025

## Overview
This project is designed for the RoboCup Junior 2025 competition. It is a robotics project that integrates various sensors, actuators, and algorithms to create a robot capable of detecting, chasing, and interacting with objects in its environment. The robot is programmed using Arduino and Python, with modular components for easy development and debugging.

## Components

### 1. **Movement**
The `Movement` module controls the robot's motors and enables it to move in different directions. It uses:
- **Motors**: Four motors (`motor_BR`, `motor_FR`, `motor_BL`, `motor_FL`) are initialized with specific pins for clockwise and counter-clockwise rotation.
- **Compass**: Integrated to ensure accurate directional movement.
- **Color Sensor**: Used to detect borders and avoid obstacles.

Key functions:
- `move(theta, maxSpeed, avoid, cameraRotationAngle)`: Moves the robot in a specified direction.
- `brake()`: Stops the robot.
- `rotate(speed)`: Rotates the robot at a given speed.
- `basic_move_with_compass_and_camera(theta, maxSpeed, camAngle)`: Combines compass and camera data for precise movement.

### 2. **IR Sensor**
The `IR` module detects the angle of the ball relative to the robot using infrared sensors. It uses:
- **16 IR pins** to read signals.

Key functions:
- `getBallAngle()`: Calculates the angle of the ball.
- `getReadingsArr()`: Returns normalized readings from the IR sensors.
- `initIR()`: Initializes the IR sensors.

### 3. **Color Sensor**
The `ColorSensor` module detects colors and helps the robot avoid borders or interact with specific objects.

Key functions:
- `isDetected()`: Checks if a specific color is detected.
- `countFront()`, `countRight()`, `countBack()`, `countLeft()`: Counts the number of color detections in different directions.
- `printReadings()`: Prints sensor readings for debugging.

### 4. **Camera**
The `Camera` module uses a Pixy2 camera to detect objects and calculate angles for movement.

Key functions:
- `initialize()`: Initializes the camera.
- `calculateRotationAngle()`: Calculates the angle for rotation based on detected objects.
- `findDistance()`: Estimates the distance to detected objects.
- `printStatus()`: Prints the camera's status.

### 5. **Compass**
The `Compass` module uses an Adafruit BNO055 sensor to read the robot's orientation.

Key functions:
- `initialize()`: Initializes the compass.
- `readCompass()`: Returns the robot's orientation angle.

### 6. **Kicker**
The `Kicker` module controls the robot's kicking mechanism.

Key functions:
- `performKick()`: Activates the kicker.
- `triggerKick()`: Sets the kicker to be triggered.

### 7. **Time-of-Flight (TOF) Sensor**
The `TOF` module uses a VL53L0X sensor to measure the distance to objects.

Key functions:
- `initialize()`: Initializes the TOF sensor.
- `GetBallRange()`: Returns the distance to the ball.

### 8. **Python Scripts**
Python scripts are used for debugging and emulating sensor data.
- `ir-emulator.py`: Visualizes IR sensor data using Pygame.
- `reading_serial_monitor.py`: Reads data from the serial monitor.

## How to Use

### Setup
1. Connect all components to the Arduino board as per the pin configurations in the code.
2. Upload the `main.ino` file to the Arduino board.
3. Run Python scripts for debugging if needed.

### Initialization
In the `setup()` function:
- Initialize all sensors and modules (IR, ColorSensor, Movement, Compass, Camera).

### Main Loop
The `loop()` function contains the robot's main logic:
- Detect the ball using the IR sensor.
- Calculate the rotation angle using the camera.
- Move towards the ball using the movement module.
- Avoid borders using the color sensor.

## File Structure
```
src/
  main/
    main.ino
    components/
      camera/
        camera.h
        camera.ino
      colorsensor/
        colorsensor.cpp
        colorsensor.h
      compass/
        compass.cpp
        compass.h
      IR/
        IR.cpp
        IR.h
      kicker/
        kicker.h
      motor/
        motor.cpp
        motor.h
      movement/
        movement.cpp
        movement.h
      tof/
        tof.cpp
        tof.h
  python/
    ir-emulator.py
    reading_serial_monitor.py
```

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contributors
- **Daniel Markusson**
- **Kyle Andersen**

## Future Improvements
- Enhance the camera module for better object detection.
- Optimize movement algorithms for smoother navigation.
- Add more debugging tools in Python.

## Contact
For questions or contributions, please contact Daniel Markusson at [email@example.com].