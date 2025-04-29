#ifndef DIGITAL_H
#define DIGITAL_H
#include <Arduino.h>

uint8_t myDigitalRead(uint8_t pin);
uint8_t myDigitalWrite(uint8_t pin, uint8_t state);
void myPinMode(uint8_t pin, uint8_t mode);

#endif
