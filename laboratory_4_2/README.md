# Laboratory 4_2 - DC Motor Control System

This project implements a command-line controlled DC motor system using an Arduino and L298N motor driver, allowing for precise speed and direction control.

## Hardware Requirements

- Arduino Uno or compatible board
- L298N Motor Driver Module
- DC Motor
- External power supply for the motor (depending on motor requirements)
- Jumper wires
- Breadboard
- USB cable for programming and serial communication

## Pin Connections

- **L298N Motor Driver**:
  - IN1: Pin 6 (motor direction control)
  - IN2: Pin 7 (motor direction control)
  - ENA: Pin 5 (PWM for speed control)
  - VCC: 5V from Arduino (for logic control)
  - Motor Power: External power supply
  - GND: Common ground with Arduino

## Software Requirements

- PlatformIO or Arduino IDE
- Serial terminal (built into PlatformIO or Arduino IDE)

## Software Structure

The project is organized in a modular structure with the following components:

1. **main.cpp**: Main program with setup and loop functions
2. **motor_control.cpp/h**: DC motor control module
3. **command_processor.cpp/h**: Serial command parsing and execution
4. **uart_helpers.cpp/h**: UART and stdio utility functions

## Command Interface

The system accepts the following commands via serial:
- `motor power <value>`: Sets motor power from -100 to 100 (negative values reverse direction)
- `motor stop`: Stops the motor (equivalent to setting power to 0)
- `motor status`: Reports current motor power level
- `help`: Displays available commands

## Building and Running

1. Open the project in PlatformIO
2. Build and upload to your Arduino board
3. Open the serial monitor (9600 baud)
4. Enter commands to control the motor

## Implementation Details

- Motor power is specified as a percentage (-100% to 100%)
- Motor direction is controlled by changing the polarity of motor connections
- Speed is controlled via PWM (Pulse Width Modulation)
- Command parsing supports space-delimited arguments
- The system provides helpful error messages for invalid commands
- Serial interface operates at 9600 baud

## Practical Applications

This motor control system can be used for:
- Robotics projects
- Automated machinery control
- Remote-controlled devices
- Educational demonstrations of motor control principles 