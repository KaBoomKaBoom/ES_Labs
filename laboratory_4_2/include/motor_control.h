#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Initialize motor pins
void setup_motor();

// Set motor power (-100 to 100)
void setMotorPower(int power);

// Get current motor power
int getCurrentPower();

#endif // MOTOR_CONTROL_H 