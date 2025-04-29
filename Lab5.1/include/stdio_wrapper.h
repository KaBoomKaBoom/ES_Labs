/**
 * stdio_wrapper.h
 * Standard I/O wrapper for Arduino
 */

 #ifndef STDIO_WRAPPER_H
 #define STDIO_WRAPPER_H
 
 #include <Arduino.h>
 #include <stdio.h>
 
 // Initialize stdio functionality
 void stdio_init(unsigned long baud);
 
 // Create custom putchar and getchar functions to work with Arduino's Serial
 int uart_putchar(char c, FILE *stream);
 int uart_getchar(FILE *stream);
 
 // Check if input is available
 bool stdio_available();
 
 // Read a string until newline
 bool stdio_readstring(char* buffer, size_t max_length);
 
 #endif // STDIO_WRAPPER_H