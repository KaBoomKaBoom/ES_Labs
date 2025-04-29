#include "motor_control.h"

MotorControl::MotorControl(MotorDriver& driver) : _driver(driver), _powerPercent(0) {}

void MotorControl::setPower(int percent) {
  _powerPercent = constrain(percent, -100, 100);
  int pwm = map(abs(_powerPercent), 0, 100, 0, 255);
  bool forward = _powerPercent >= 0;
  _driver.setSpeed(pwm, forward);
}

void MotorControl::increment(int delta) {
  setPower(_powerPercent + delta);
}

void MotorControl::stop() {
  _powerPercent = 0;
  _driver.stop();
}

int MotorControl::getPower() {
  return _powerPercent;
}

bool MotorControl::getDirection() {
  return _powerPercent >= 0;
}
