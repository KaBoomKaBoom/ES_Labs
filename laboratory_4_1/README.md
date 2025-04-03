# Laboratory 3_1 - Sensor Data Acquisition with FreeRTOS

This project implements sensor data acquisition using FreeRTOS with an ultrasonic distance sensor (HC-SR04), displaying the results on both an LCD display and serial monitor.

## Hardware Requirements

- Arduino Uno or compatible board
- HC-SR04 Ultrasonic Sensor
- I2C LCD Display (16x2)
- Jumper wires
- Breadboard

## Pin Connections

- **Ultrasonic Sensor**:
  - Trigger Pin: 9
  - Echo Pin: 8
  - VCC: 5V
  - GND: GND

- **LCD Display**:
  - SDA: A4
  - SCL: A5
  - VCC: 5V
  - GND: GND

## Software Structure

The project is organized in a modular structure with the following components:

1. **UltrasonicSensor**: Handles the ultrasonic sensor initialization and distance reading
2. **LCDDisplay**: Manages the LCD display
3. **SerialIO**: Handles serial communication for debugging and reporting
4. **TaskManager**: Coordinates the FreeRTOS tasks

## FreeRTOS Tasks

- **sensorTask**: Reads distance from the ultrasonic sensor every 100ms
- **displayTask**: Updates the LCD display every 200ms
- **statusTask**: Reports system status via Serial every 500ms

## Building and Running

1. Open the project in PlatformIO
2. Build and upload to your Arduino board
3. Open the serial monitor (9600 baud) to view the system status reports

## Implementation Details

- The project demonstrates the use of FreeRTOS for multitasking
- Task scheduling uses vTaskDelayUntil() for precise timing
- Task offsets are implemented using vTaskDelay()
- Inter-task communication is handled with a queue and protected with a mutex
- System status reporting provides uptime and latest sensor values 