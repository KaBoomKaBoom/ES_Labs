/**
 * serial_interface.cpp
 * Implementation of serial communication interface using stdio
 */

 #include <stdlib.h> // For atof
 #include <ctype.h>  // For isspace
 #include "serial_interface.h"
 
 SerialInterface::SerialInterface() {
     lastPrintTime = 0;
     lastAlertTime = 0;
     alertActive = false;
 }
 
 void SerialInterface::begin() {
     // Initialize stdio wrapper
     stdio_init(SERIAL_BAUD_RATE);
     
     // Print welcome message and help menu
     printf("\n=== Temperature Control System with Hysteresis ===\n");
     printHelpMenu();
 }
 
 void SerialInterface::printStatus(float temperature, float setPoint, float hysteresis, bool relayState) {
     unsigned long currentTime = millis();
     
     // Check if it's time to update the serial output
     if (currentTime - lastPrintTime >= SERIAL_PRINT_INTERVAL) {
         lastPrintTime = currentTime;
         
         // Print status information using printf formatting
         printf("\n--- System Status ---\n");
 
         char tempStr[32];
         char setPointStr[32];
         char hysteresisStr[32];
 
         dtostrf(temperature, 5, 2, tempStr);
         dtostrf(setPoint, 5, 2, setPointStr);
         dtostrf(hysteresis, 5, 2, hysteresisStr);
         
         printf("Temperature: %s °C\n", tempStr);
         printf("Set Point: %s °C\n", setPointStr);
         printf("Hysteresis: ±%s °C\n", hysteresisStr);
         printf("Relay: %s\n", relayState ? "ON" : "OFF");
         printf("-------------------\n");
     }
 }
 
 void SerialInterface::printHelpMenu() {
     printf("\n--- Available Commands ---\n");
     printf("set:XX.X    - Set temperature setpoint (e.g., 'set:25.5')\n");
     printf("hyst:X.X    - Set hysteresis value (e.g., 'hyst:2.0')\n");
     printf("help        - Display this help menu\n");
     printf("------------------------\n");
 }
 
 bool SerialInterface::processCommands(float* currentSetPoint, float* currentHysteresis) {
     // Maximum command length
     const size_t MAX_CMD_LENGTH = 32;
     char command[MAX_CMD_LENGTH];
     
     // Check if there's input available and read it
     if (stdio_available()) {
         if (stdio_readstring(command, MAX_CMD_LENGTH)) {
             // Debug: Print the raw command
             printf("DEBUG: Received command: '");
             for (size_t i = 0; command[i] != '\0'; i++) {
                 if (isprint(command[i])) {
                     printf("%c", command[i]);
                 } else {
                     printf("[0x%02X]", (unsigned char)command[i]);
                 }
             }
             printf("'\n");
             
             // Process setpoint command
             if (strncmp(command, "set:", 4) == 0) {
                 // Trim whitespace from the substring
                 char* valueStr = command + 4;
                 size_t len = strlen(valueStr);
                 while (len > 0 && isspace(valueStr[len - 1])) {
                     valueStr[len - 1] = '\0';
                     len--;
                 }
                 
                 // Debug: Print the substring to be parsed
                 printf("DEBUG: Parsing setpoint: '");
                 for (size_t i = 0; valueStr[i] != '\0'; i++) {
                     if (isprint(valueStr[i])) {
                         printf("%c", valueStr[i]);
                     } else {
                         printf("[0x%02X]", (unsigned char)valueStr[i]);
                     }
                 }
                 printf("'\n");
                 
                 float newSetPoint;
                 if (sscanf(valueStr, "%f", &newSetPoint) == 1) {
                     if (newSetPoint >= MIN_TEMPERATURE && newSetPoint <= MAX_TEMPERATURE) {
                         *currentSetPoint = newSetPoint;
                            // Print the new setpoint using printf formatting
                            char setPointStr[32];
                            dtostrf(newSetPoint, 5, 2, setPointStr);
                            printf("New setpoint: %s °C\n", setPointStr);
                         
                         return true;
                     } else {
                         printf("Error: Setpoint must be between %.1f and %.1f °C\n", 
                                MIN_TEMPERATURE, MAX_TEMPERATURE);
                     }
                 } else {
                     // Fallback to atof
                     newSetPoint = atof(valueStr);
                     if (newSetPoint != 0.0 || strcmp(valueStr, "0") == 0 || strcmp(valueStr, "0.0") == 0) {
                         if (newSetPoint >= MIN_TEMPERATURE && newSetPoint <= MAX_TEMPERATURE) {
                             *currentSetPoint = newSetPoint;
                             char setPointStr[32];
                             dtostrf(newSetPoint, 5, 2, setPointStr);
                             printf("New setpoint: %s °C\n", setPointStr);
                             return true;
                         } else {
                             printf("Error: Setpoint must be between %.1f and %.1f °C\n", 
                                    MIN_TEMPERATURE, MAX_TEMPERATURE);
                         }
                     } else {
                         printf("Error: Invalid setpoint format\n");
                     }
                 }
             }
             // Process hysteresis command
             else if (strncmp(command, "hyst:", 5) == 0) {
                 // Trim whitespace from the substring
                 char* valueStr = command + 5;
                 size_t len = strlen(valueStr);
                 while (len > 0 && isspace(valueStr[len - 1])) {
                     valueStr[len - 1] = '\0';
                     len--;
                 }
                 
                 // Debug: Print the substring to be parsed
                 printf("DEBUG: Parsing hysteresis: '");
                 for (size_t i = 0; valueStr[i] != '\0'; i++) {
                     if (isprint(valueStr[i])) {
                         printf("%c", valueStr[i]);
                     } else {
                         printf("[0x%02X]", (unsigned char)valueStr[i]);
                     }
                 }
                 printf("'\n");
                 
                 float newHysteresis;
                 if (sscanf(valueStr, "%f", &newHysteresis) == 1) {
                     if (newHysteresis > 0) {
                         *currentHysteresis = newHysteresis;
                            // Print the new hysteresis using printf formatting
                            char hysteresisStr[32];
                            dtostrf(newHysteresis, 5, 2, hysteresisStr);
                            printf("New hysteresis: ±%s °C\n", hysteresisStr);
                         
                         return true;
                     } else {
                         printf("Error: Hysteresis must be positive\n");
                     }
                 } else {
                     // Fallback to atof
                     newHysteresis = atof(valueStr);
                     if (newHysteresis != 0.0 || strcmp(valueStr, "0") == 0 || strcmp(valueStr, "0.0") == 0) {
                         if (newHysteresis > 0) {
                             *currentHysteresis = newHysteresis;
                             char hysteresisStr[32];
                             dtostrf(newHysteresis, 5, 2, hysteresisStr);
                             printf("New hysteresis: ±%s °C\n", hysteresisStr);
                             return true;
                         } else {
                             printf("Error: Hysteresis must be positive\n");
                         }
                     } else {
                         printf("Error: Invalid hysteresis format\n");
                     }
                 }
             }
             // Help command
             else if (strcmp(command, "help") == 0) {
                 printHelpMenu();
             }
             // Unknown command
             else {
                 printf("Unknown command: '%s'\n", command);
                 printf("Type 'help' for available commands\n");
             }
         }
     }
     
     return false;
 }
 
 bool SerialInterface::checkAlert(float temperature, float setPoint) {
     unsigned long currentTime = millis();
     
     // Calculate absolute deviation from setpoint
     float deviation = fabs(temperature - setPoint);
     
     // Check if deviation exceeds threshold and alert interval has passed
     if (deviation > ALERT_THRESHOLD) {
         if (!alertActive || (currentTime - lastAlertTime >= ALERT_INTERVAL)) {
             alertActive = true;
             lastAlertTime = currentTime;
             
             char deviationStr[32];
                dtostrf(deviation, 5, 2, deviationStr);
                // Print alert message using printf formatting
                printf("\n!!! ALERT !!!\n");
                printf("Temperature deviation exceeds threshold: %s °C\n", deviationStr);
                printf("!!!!!!!!!!!!!!!\n");

             
             return true;
         }
     } else {
         // Reset alert state when temperature returns to normal range
         if (alertActive) {
             alertActive = false;
             printf("\n--- Alert cleared: Temperature stabilized ---\n");
         }
     }
     
     return false;
 }