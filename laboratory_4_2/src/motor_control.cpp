#include "motor_control.h"
#include <stdio.h>

// Motor pins
int motor1pin1 = 6;
int motor1pin2 = 7;
int enablePin = 5;
int currentPower = 0; // Range: -100 to 100

void setup_motor() {
  // Configure motor pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  // Initial state: motor stopped
  setMotorPower(0);
}

void setMotorPower(int power) {
  // Constrain power to -100 to 100 range
  currentPower = constrain(power, -100, 100);
  
  // Set direction based on power sign
  if (currentPower > 0) {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
  } else if (currentPower < 0) {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  } else {
    // Stop if power is 0
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
  }
  
  // Convert percentage (0-100) to PWM (0-255)
  int pwmValue = map(abs(currentPower), 0, 100, 0, 255);
  analogWrite(enablePin, pwmValue);
  
  printf("Motor power set to: %d\n", currentPower);
}

int getCurrentPower() {
  return currentPower;
} 