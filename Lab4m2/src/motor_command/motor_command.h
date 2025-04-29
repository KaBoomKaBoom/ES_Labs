#pragma once
#include "motor_control/motor_control.h"

class CommandParser {
public:
  CommandParser(MotorControl& control);
  void handleSerialCommand();

private:
  MotorControl& _motor;
};
