#pragma once
#include "motor_driver/motor_driver.h"

class MotorControl {
public:
  MotorControl(MotorDriver& driver);
  void setPower(int percent);
  void increment(int delta = 10);
  void stop();
  int getPower();
  bool getDirection();

private:
  MotorDriver& _driver;
  int _powerPercent; // [-100 .. 100]
};
