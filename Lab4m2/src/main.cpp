#include <Arduino.h>
#include <stdio.h>
#include "motor_driver/motor_driver.h"
#include "motor_control/motor_control.h"
#include "motor_command/motor_command.h"
#include "status_reporter/status_reporter.h"

// Pini L293
#define ENA 5
#define IN1 3
#define IN2 4

MotorDriver motorDriver(ENA, IN1, IN2);
MotorControl motorControl(motorDriver);
CommandParser commandParser(motorControl);
StatusReporter statusReporter(motorControl);

FILE relay_scan;
FILE relay_print;

int stdio_getinput(FILE * stream) {
  while (!Serial.available());
  return Serial.read();
}

int stdio_print(char c, FILE * stream) {
  Serial.write(c);
  return 0;
}

void setup() {
  Serial.begin(9600);
  FILE * fpSerial = fdevopen(stdio_print, stdio_getinput);
  stdin = fpSerial;
  stdout = fpSerial;

  while (!Serial) { ; }

  Serial.begin(9600);
  printf("Control Motor DC - READY");

  statusReporter.printCommandHelp();
}

void loop() {
  commandParser.handleSerialCommand();
  statusReporter.reportStatus();
  delay(100); // Debounce și timing
}

