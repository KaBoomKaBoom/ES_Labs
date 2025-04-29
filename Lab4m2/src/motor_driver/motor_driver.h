#pragma once
#include <Arduino.h>

class MotorDriver {
public:
  MotorDriver(int enaPin, int dirAPin, int dirBPin);
  void setSpeed(int pwm, bool forward);
  void stop();

private:
  int _ena, _dirA, _dirB;
};
