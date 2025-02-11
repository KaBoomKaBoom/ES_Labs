// main.cpp
#include <Arduino.h>
#include "led.h"
#include "serialControl.h"
#include "stdioRedirect.h"

#define LED_PIN 13
#define BAUD_RATE 9600

void setup() {
    initializeLed(LED_PIN);
    initializeSerial(BAUD_RATE);
    initializeStdio();  // Initialize stdio redirection
}

void loop() {
    processSerialCommands();
}

