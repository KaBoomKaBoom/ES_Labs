#include "motor_driver.h"
#include "my_digital/my_digital.h"
#include "analog_reader/analog_reader.h"


MotorDriver::MotorDriver(int enaPin, int dirAPin, int dirBPin) {
  _ena = enaPin;
  _dirA = dirAPin;
  _dirB = dirBPin;
  myPinMode(_ena, OUTPUT);
  myPinMode(_dirA, OUTPUT);
  myPinMode(_dirB, OUTPUT);
}

void MotorDriver::setSpeed(int pwm, bool forward) {
  myAnalogWrite(_ena, constrain(pwm, 0, 255));
  myDigitalWrite(_dirA, forward ? LOW : HIGH);
  myDigitalWrite(_dirB, forward ? HIGH : LOW);
}

void MotorDriver::stop() {
  myAnalogWrite(_ena, 0);
  myDigitalWrite(_dirA, LOW);
  myDigitalWrite(_dirB, LOW);
}
