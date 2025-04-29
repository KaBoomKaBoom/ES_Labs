/**
 * stdio_wrapper.cpp
 * Standard I/O wrapper implementation for Arduino
 */

 #include "stdio_wrapper.h"

 // Create a FILE stream structure for stdin and stdout
 static FILE uartout = {0};
 static FILE uartin = {0};
 
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
     if (!stdio_available()) {
         return false;
     }
     
     size_t index = 0;
     buffer[0] = '\0';
     
     // Wait for first character with timeout
     unsigned long start_time = millis();
     while (!stdio_available() && (millis() - start_time < 500));
     
     if (!stdio_available()) {
         return false;
     }
     
     // Read characters until newline or max length
     while (stdio_available() && index < max_length - 1) {
         char c = Serial.read();
         
         // Break on newline
         if (c == '\n' || c == '\r') {
             break;
         }
         
         // Add character to buffer
         buffer[index++] = c;
         buffer[index] = '\0';
         
         // Small delay to ensure all data is read
         delay(2);
     }
     
     // Flush any remaining characters in the buffer (up to newline)
     while (stdio_available()) {
         char c = Serial.read();
         if (c == '\n' || c == '\r') {
             break;
         }
         delay(1);
     }
     
     return index > 0;
 }