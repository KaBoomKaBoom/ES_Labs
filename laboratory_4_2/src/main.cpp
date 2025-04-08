#include <Arduino.h>
#include "uart_helpers.h"
#include "motor_control.h"
#include "command_processor.h"

void setup() {
  // Initialize serial
  Serial.begin(9600);
  
  // Initialize stdio
  setup_uart_stdio();
  
  // Initialize motor
  setup_motor();
  
  // Print command help
  printCommandHelp();
}

void loop() {
  if (Serial.available() > 0) {
    readLine();
  }
  delay(10); // Small delay to prevent CPU overload
}
