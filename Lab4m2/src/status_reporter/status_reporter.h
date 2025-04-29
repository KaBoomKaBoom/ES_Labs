#pragma once
#include "motor_control/motor_control.h"

class StatusReporter {
public:
  StatusReporter(MotorControl& control);
  void reportStatus();
  void printCommandHelp() ;

private:
  MotorControl& _motor;
  int _lastPower;
};
