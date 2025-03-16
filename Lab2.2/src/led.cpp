#include "Led.h"

Led::Led(uint8_t pin) {
    this->pin = pin;
    this->state = false;
    pinMode(pin, OUTPUT);
}

void Led::toggle() {
    state = !state;
    digitalWrite(pin, state ? HIGH : LOW);
}

void Led::turnOn() {
    state = true;
    digitalWrite(pin, HIGH);
}

void Led::turnOff() {
    state = false;
    digitalWrite(pin, LOW);
}