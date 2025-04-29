/**
 * serial_interface.cpp
 * Implementation of serial communication interface using stdio
 */

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
         printf("Temperature: %.2f °C\n", temperature);
         printf("Set Point: %.2f °C\n", setPoint);
         printf("Hysteresis: ±%.2f °C\n", hysteresis);
         printf("Thresholds: %.2f to %.2f °C\n", setPoint - hysteresis, setPoint + hysteresis);
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
             // Process setpoint command
             if (strncmp(command, "set:", 4) == 0) {
                 float newSetPoint;
                 if (sscanf(command + 4, "%f", &newSetPoint) == 1) {
                     if (newSetPoint >= MIN_TEMPERATURE && newSetPoint <= MAX_TEMPERATURE) {
                         *currentSetPoint = newSetPoint;
                         printf("New setpoint: %.2f °C\n", newSetPoint);
                         return true;
                     } else {
                         printf("Error: Setpoint must be between %.1f and %.1f °C\n", 
                                MIN_TEMPERATURE, MAX_TEMPERATURE);
                     }
                 } else {
                     printf("Error: Invalid setpoint format\n");
                 }
             }
             // Process hysteresis command
             else if (strncmp(command, "hyst:", 5) == 0) {
                 float newHysteresis;
                 if (sscanf(command + 5, "%f", &newHysteresis) == 1) {
                     if (newHysteresis > 0) {
                         *currentHysteresis = newHysteresis;
                         printf("New hysteresis: ±%.2f °C\n", newHysteresis);
                         return true;
                     } else {
                         printf("Error: Hysteresis must be positive\n");
                     }
                 } else {
                     printf("Error: Invalid hysteresis format\n");
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
             
             // Print alert message
             printf("\n!!! ALERT !!!\n");
             printf("Temperature deviation exceeds threshold: %.2f °C\n", deviation);
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