#include "Relay.h"

Relay::Relay(uint8_t pin) {
    this->pin = pin;
    this->state = false;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Relay::turnOn() {
    state = true;
    digitalWrite(pin, LOW);
}

void Relay::turnOff() {
    state = false;
    digitalWrite(pin, HIGH);
}

void Relay::toggle() {
    state = !state;
    digitalWrite(pin, state ? HIGH : LOW);
}

bool Relay::getState() {
    return state;
}