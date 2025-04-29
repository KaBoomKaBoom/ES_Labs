#include "serial_stdio.h"
#include <Arduino.h>
#include <stdio.h>

#define BUFFER_SIZE 32

static char commandBuffer[BUFFER_SIZE];
static int bufferIndex = 0;

// Redirect serial output to printf.
static int serialPutchar(char c, FILE* stream) {
    // Optionally convert newline to carriage return + newline for many serial monitors.
    if (c == '\n') {
        Serial.write('\r');
    }
    Serial.write(c);
    return 0;
}

// Blocking getchar function for stdio input (used by scanf, etc.)
static int serialGetchar(FILE* stream) {
    // Wait until data is available.
    while (!Serial.available()) {
        ; // busy wait (consider a timeout in a more advanced implementation)
    }
    return Serial.read();
}

void initializeStdio(unsigned long baudRate) {
    // Initialize serial communication.
    Serial.begin(baudRate);
    
    // Setup both printf and scanf redirection.
    fdevopen(&serialPutchar, &serialGetchar);
}

void serialPrint(const char* message) {
    printf("%s", message);
}

void serialPrintln(const char* message) {
    printf("%s\n", message);
}

// Non-blocking function to read a line from serial input.
// It accumulates characters in a static buffer until a newline (or carriage return) is received.
// When a complete line is available, it returns a pointer to the buffer; otherwise, it returns NULL.
char* serialReadLine() {
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            if (bufferIndex > 0) {
                commandBuffer[bufferIndex] = '\0'; // Terminate the string.
                bufferIndex = 0; // Reset for the next command.
                return commandBuffer;
            }
            // If no character has been collected yet, skip the newline.
        } else {
            if (bufferIndex < BUFFER_SIZE - 1) {
                commandBuffer[bufferIndex++] = c;
            }
            // Else: If the buffer is full, additional characters are ignored.
        }
    }
    return NULL;
}
