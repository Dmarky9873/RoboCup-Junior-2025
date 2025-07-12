# RoboCup-Junior-2025

## What is RoboCup Junior?

RoboCup Junior is an international robotics competition that encourages students to design, build, and program autonomous robots to complete specific challenges. In the Soccer division, robots must detect, chase, and kick a ball into a goal while avoiding opponents and staying within the field boundaries. It’s a fast-paced, dynamic event that tests engineering, coding, and problem-solving skills under real-time constraints.

This repository contains the codebase for our custom-built soccer-playing robot, developed for the RoboCup Junior 2025 season. The robot is designed to navigate the field intelligently, track a ball, avoid boundaries, and interact with objects using a combination of sensors, motors, and algorithms.

## Overview

The robot is programmed using Arduino (C++) for embedded control and Python for simulation and debugging. The architecture is modular to allow for fast iteration and easier testing of individual components like movement, vision, and sensors.

⸻

## Hardware Components

### 1. Movement

Controls the robot’s motion using four omnidirectional motors in an X configuration.
	•	Motors: Each wheel has two control pins for direction.
	•	Compass: Ensures the robot maintains orientation.
	•	Color Sensor: Detects the field’s white boundary to prevent out-of-bounds errors.

#### Key functions:
	•	move(theta, maxSpeed, avoid, cameraRotationAngle)
	•	brake()
	•	rotate(speed)
	•	basic_move_with_compass_and_camera(theta, maxSpeed, camAngle)

⸻

### 2. IR Sensor

Tracks the angle of the ball using a ring of 16 IR receivers mounted under the robot.

#### Key functions:
	•	getBallAngle()
	•	getReadingsArr()
	•	initIR()

⸻

### 3. Color Sensor

Reads field surface color to detect white boundary lines.

#### Key functions:
	•	isDetected()
	•	countFront(), countRight(), countBack(), countLeft()
	•	printReadings()

⸻

### 4. Camera

Uses a Pixy2 camera over SPI to track visual objects like the goal.

#### Key functions:
	•	initialize()
	•	calculateRotationAngle()
	•	findDistance()
	•	printStatus()

⸻

### 5. Compass

An Adafruit BNO055 IMU is used for absolute orientation.

#### Key functions:
	•	initialize()
	•	readCompass()

⸻

### 6. Kicker

Triggers a solenoid or mechanical mechanism to kick the ball.

Key functions:
	•	performKick()
	•	triggerKick()

⸻

#### 7. Time-of-Flight (TOF) Sensor

Uses a VL53L0X laser distance sensor to detect proximity (e.g., ball distance).

Key functions:
	•	initialize()
	•	GetBallRange()

⸻

### 8. Python Tools

Used for debugging and visualization.
	•	ir-emulator.py: Simulates IR input using Pygame.
	•	reading_serial_monitor.py: Parses serial data from the Arduino.

⸻

## How to Use

### Setup
	1.	Wire all components according to the wiring diagram (see src/main).
	2.	Upload main.ino to the Teensy board via the Arduino IDE.
	3.	Launch Python scripts (optional) for debugging and visualization.

### Initialization (setup())
	•	Initializes all modules: IR, Color Sensor, Compass, Camera, Motors.

### Main Loop (loop())
	1.	Use IR to locate the ball.
	2.	Use the camera to orient toward the goal.
	3.	Move accordingly while checking for white boundary lines.
	4.	Kick when aligned with the ball and goal.

⸻

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

⸻

## License

This project is licensed under the MIT License. See the LICENSE file for details.

⸻

## Contributors
  - Daniel Markusson
  - Kyle Andersen
  - Jacky Zhang

⸻

## Future Improvements
	•	Improve object recognition and opponent tracking with the Pixy2.
	•	Add kicker and dribbler to improve performance.
	•	Develop a visual dashboard for real-time game data.

⸻

## Contact

For questions, contact Daniel Markusson at [markussondan@gmail.com].
