#include <Arduino.h>
#include "Config.h"
#include "LedControl.h"

void LedControl::init() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
}

void LedControl::greenOn() {
    digitalWrite(GREEN_LED, HIGH);
}

void LedControl::greenOff() {
    digitalWrite(GREEN_LED, LOW);
}

void LedControl::redOn() {
    digitalWrite(RED_LED, HIGH);
}

void LedControl::redOff() {
    digitalWrite(RED_LED, LOW);
}
