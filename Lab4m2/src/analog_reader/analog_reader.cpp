#include "analog_reader.h"

int myAnalogReader(uint8_t pin) {
  return analogRead(pin);
}

void myAnalogWrite(uint8_t pin, int val) {
  return analogWrite(pin, val);
}