/**
 * Arduino FreeRTOS Project - Button Utilities
 * 
 * This file contains utility functions for button handling,
 * including debouncing logic.
 */

 #ifndef BUTTON_UTILS_H
 #define BUTTON_UTILS_H
 
 #include <Arduino.h>
 #include "config.h"
 
 /* Function to read button state with debouncing */
 bool read_button(uint8_t pin);
 
 #endif /* BUTTON_UTILS_H */