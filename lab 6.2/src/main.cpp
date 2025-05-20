/**
 * main.cpp
 * Main program for Arduino traffic light controller
 */
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "traffic_light_controller.h"

void setup() {
    // Initialize the traffic light controller
    if (trafficLightInit() != 0) {
        // If initialization fails, we could potentially handle it here
        // For example, blink an error LED or retry
        while(1) {
            // Simple error indicator - if we reach here, something failed
            delay(500);
        }
    }
}

void loop() {
    // Not used when running FreeRTOS
    // FreeRTOS scheduler takes over after setup()
}