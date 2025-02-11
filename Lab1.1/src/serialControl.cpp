// serialControl.cpp
#include "serialControl.h"
#include "led.h"
#include <Arduino.h>
#include <stdio.h>

#define BUFFER_SIZE 32

void initializeSerial(unsigned long baudRate) {
    Serial.begin(baudRate);
    while (!Serial) {
        ; // Wait for serial port to connect
    }
    
    printf("LED Control System Ready\n");
    printf("Available commands:\n");
    printf("- led on  : Turn on the LED\n");
    printf("- led off : Turn off the LED\n");
}

void processSerialCommands() {
    char command[BUFFER_SIZE];
    
    if (scanf("%31s", command) == 1) {  // Read up to 31 chars to leave room for null terminator
        char nextWord[BUFFER_SIZE];
        if (scanf("%31s", nextWord) == 1) {
            if (strcmp(command, "led") == 0) {
                if (strcmp(nextWord, "on") == 0) {
                    turnOnLed();
                    printf("Command confirmed: LED turned ON\n");
                }
                else if (strcmp(nextWord, "off") == 0) {
                    turnOffLed();
                    printf("Command confirmed: LED turned OFF\n");
                }
                else {
                    printf("Unknown LED command: %s\n", nextWord);
                }
            }
            else {
                printf("Unknown command: %s %s\n", command, nextWord);
            }
        }
    }
}