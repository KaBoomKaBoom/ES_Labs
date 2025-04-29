/**
 * main.cpp
 * Temperature control system with ON-OFF hysteresis using stdio
 */

 #include <Arduino.h>
 #include <stdio.h>
 #include "config.h"
 #include "stdio_wrapper.h"
 #include "temperature_sensor.h"
 #include "hysteresis_controller.h"
 #include "serial_interface.h"
 
 // Create instances of modules
 TemperatureSensor tempSensor;
 HysteresisController controller;
 SerialInterface serialUI;
 
 void setup() {
     // Initialize serial interface
     serialUI.begin();
     
     // Initialize temperature sensor
     printf("Initializing temperature sensor... ");
     if (tempSensor.begin()) {
         printf("OK\n");
     } else {
         printf("FAILED\n");
         printf("Check sensor connection and restart\n");
     }
     
     // Initialize controller
     controller.begin();
     printf("Initializing controller... ");
     printf("OK\n");
     
     // Print initial configuration
     printf("\nInitial setpoint: %.2f °C\n", controller.getSetPoint());
     printf("Initial hysteresis: ±%.2f °C\n", controller.getHysteresis());
     printf("\nSystem running. Type 'help' for commands.\n");
 }
 
 void loop() {
     // Update temperature reading
     tempSensor.update();
     
     // Get current temperature
     float currentTemperature = tempSensor.getTemperature();
     
     // Update controller state
     bool stateChanged = controller.update(currentTemperature);
     
     // Process serial commands
     float currentSetPoint = controller.getSetPoint();
     float currentHysteresis = controller.getHysteresis();
     
     bool commandProcessed = serialUI.processCommands(&currentSetPoint, &currentHysteresis);
     
     // Update controller parameters if changed via serial
     if (commandProcessed) {
         controller.setSetPoint(currentSetPoint);
         controller.setHysteresis(currentHysteresis);
     }
     
     // Print status information
     serialUI.printStatus(
         currentTemperature,
         controller.getSetPoint(),
         controller.getHysteresis(),
         controller.getRelayState()
     );
     
     // Check for temperature deviation alert (bonus feature)
     serialUI.checkAlert(currentTemperature, controller.getSetPoint());
     
     // Small delay to reduce CPU usage
     delay(100);
 }