/**
 * stdio_wrapper.cpp
 * Standard I/O wrapper implementation for Arduino
 */

 #include "stdio_wrapper.h"

 // Create a FILE stream structure for stdin and stdout
 static FILE uartout = {0};
 static FILE uartin = {0};
 
 // Buffer for reading serial input
 #define BUFFER_SIZE 32
 static char commandBuffer[BUFFER_SIZE];
 static int bufferIndex = 0;
 
 void stdio_init(unsigned long baud) {
     // Initialize serial
     Serial.begin(baud);
     
     // Wait for serial port to connect (needed for native USB port only)
     while (!Serial && millis() < 5000);
     
     // Setup stdout stream
     fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
     stdout = &uartout;
     
     // Setup stdin stream
     fdev_setup_stream(&uartin, NULL, uart_getchar, _FDEV_SETUP_READ);
     stdin = &uartin;
 }
 
 int uart_putchar(char c, FILE *stream) {
     // Optionally convert newline to carriage return + newline
     if (c == '\n') {
         Serial.write('\r');
     }
     Serial.write(c);
     return 0;
 }
 
 int uart_getchar(FILE *stream) {
     // Wait until character is available
     while (!Serial.available());
     return Serial.read();
 }
 
 bool stdio_available() {
     return Serial.available() > 0;
 }
 
 bool stdio_readstring(char* buffer, size_t max_length) {
     while (Serial.available()) {
         char c = Serial.read();
         if (c == '\n' || c == '\r') {
             if (bufferIndex > 0) {
                 commandBuffer[bufferIndex] = '\0'; // Terminate the string
                 bufferIndex = 0; // Reset for next command
                 // Copy to output buffer, respecting max_length
                 strncpy(buffer, commandBuffer, max_length - 1);
                 buffer[max_length - 1] = '\0'; // Ensure null-termination
                 // Debug: Print the buffer
                 printf("DEBUG: stdio_readstring buffer: '%s'\n", buffer);
                 return true;
             }
             // Skip empty lines
         } else {
             if (bufferIndex < BUFFER_SIZE - 1) {
                 commandBuffer[bufferIndex++] = c;
             }
             // Ignore characters if buffer is full
         }
     }
     return false;
 }