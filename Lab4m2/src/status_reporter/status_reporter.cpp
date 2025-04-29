#include "status_reporter.h"

StatusReporter::StatusReporter(MotorControl& control) : _motor(control), _lastPower(-999) {}

void StatusReporter::reportStatus() {
  int power = _motor.getPower();
  if (power != _lastPower) {
    printf("Motor power: %d \n", power);
    _lastPower = power;
  }
}

void StatusReporter::printCommandHelp() {
  printf("Motor Control Ready\n");
  printf("Available commands:\n");
  printf("  motor set [-100..100] - Set power and direction\n");
  printf("  motor stop - Stop the motor\n");
  printf("  motor max - Set to max power in current direction\n");
  printf("  motor inc - Increase power by 10%%\n");
  printf("  motor dec - Decrease power by 10%%\n");
} 