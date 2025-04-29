#include "my_digital.h"

uint8_t myDigitalRead(uint8_t pin) {
  return digitalRead(pin);
}

uint8_t myDigitalWrite(uint8_t pin, uint8_t state) {
  digitalWrite(pin, state);
  return state;
}

void myPinMode(uint8_t pin, uint8_t mode) {
  pinMode(pin, mode);
}