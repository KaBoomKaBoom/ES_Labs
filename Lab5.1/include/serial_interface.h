/**
 * serial_interface.h
 * Module for serial communication interface using stdio
 */

 #ifndef SERIAL_INTERFACE_H
 #define SERIAL_INTERFACE_H
 
 #include <Arduino.h>
 #include <stdio.h>
 #include "config.h"
 #include "stdio_wrapper.h"
 
 class SerialInterface {
 private:
     unsigned long lastPrintTime;            // Time of last serial print
     unsigned long lastAlertTime;            // Time of last alert message
     bool alertActive;                       // Flag for active alert
     
 public:
     /**
      * Constructor
      */
     SerialInterface();
     
     /**
      * Initialize serial communication
      */
     void begin();
     
     /**
      * Print system status if print interval has passed
      * @param temperature Current temperature
      * @param setPoint Temperature setpoint
      * @param hysteresis Hysteresis value
      * @param relayState Current relay state
      */
     void printStatus(float temperature, float setPoint, float hysteresis, bool relayState);
     
     /**
      * Print help menu with available commands
      */
     void printHelpMenu();
     
     /**
      * Process incoming serial commands
      * @param currentSetPoint Current setpoint value
      * @param currentHysteresis Current hysteresis value
      * @return true if a command was processed, false otherwise
      */
     bool processCommands(float* currentSetPoint, float* currentHysteresis);
     
     /**
      * Check for temperature deviation alert condition
      * @param temperature Current temperature
      * @param setPoint Temperature setpoint
      * @return true if alert was triggered, false otherwise
      */
     bool checkAlert(float temperature, float setPoint);
 };
 
 #endif // SERIAL_INTERFACE_H