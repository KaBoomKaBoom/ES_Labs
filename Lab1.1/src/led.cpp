
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

void turnOnLed() {
    digitalWrite(ledPin, HIGH);
    ledState = true;
}

void turnOffLed() {
    digitalWrite(ledPin, LOW);
    ledState = false;
}

bool getLedState() {
    return ledState;
}