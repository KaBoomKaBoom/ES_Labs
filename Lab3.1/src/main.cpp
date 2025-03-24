/*
 * Ultrasonic Sensor Data Acquisition and Display using FreeRTOS
 * 
 * Main file - Program initialization and entry point
 */

 #include <Arduino_FreeRTOS.h>
 #include <stdio.h>
 #include "sensor.h"
 #include "signal_manager.h"
 #include "display.h"
 
 // Task handles
 TaskHandle_t acquisitionTaskHandle;
 TaskHandle_t displayTaskHandle;
 
 // Required for printf redirection to Serial
 int serialPutchar(char c, FILE *) {
   Serial.write(c);
   return c;
 }
 
 // Setup printf
 FILE serial_stdout;
 
 void setup() {
   // Initialize serial communication
   Serial.begin(115200);
   
   // Set up printf to output to Serial
   fdev_setup_stream(&serial_stdout, serialPutchar, NULL, _FDEV_SETUP_WRITE);
   stdout = &serial_stdout;
   
   // Print startup message
   printf("\nUltrasonic Sensor System Starting...\n");
   
   // Initialize sensor
   sensor_init();
   
   // Initialize signal manager
   signal_manager_init();
   
   // Create FreeRTOS tasks
   xTaskCreate(
     acquisitionTask,          // Task function
     "AcquisitionTask",        // Task name
     128,                      // Stack size
     NULL,                     // Parameters
     2,                        // Priority (higher number = higher priority)
     &acquisitionTaskHandle    // Task handle
   );
   
   xTaskCreate(
     displayTask,              // Task function
     "DisplayTask",            // Task name
     256,                      // Stack size (larger for display task due to printf)
     NULL,                     // Parameters
     1,                        // Priority (lower than acquisition task)
     &displayTaskHandle        // Task handle
   );
   
   // Start the scheduler
   vTaskStartScheduler();
 }
 
 void loop() {
   // Empty, as FreeRTOS takes control
 }