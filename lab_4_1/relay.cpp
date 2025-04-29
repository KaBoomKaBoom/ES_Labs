#include <Arduino.h>

#define RELAY_PIN 8  // Relay pin

void relay_init() {
    pinMode(RELAY_PIN, OUTPUT);
}

void toggle_relay(bool state) {
    if (state) {
        digitalWrite(RELAY_PIN, LOW);
    } else {
        digitalWrite(RELAY_PIN, HIGH);
    }
}