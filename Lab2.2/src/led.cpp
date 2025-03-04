// led.cpp (unchanged)
#include "led.h"
#include <Arduino.h>

static int ledPin;
static bool ledState = false;

void initializeLed(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

void turnOnLed(int pin) {
    digitalWrite(pin, HIGH);
    ledState = true;
}

void turnOffLed(int pin) {
    digitalWrite(pin, LOW);
    ledState = false;
}

bool getLedState() {
    return ledState;
}