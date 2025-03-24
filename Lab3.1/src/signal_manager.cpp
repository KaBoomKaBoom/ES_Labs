/*
 * signal_manager.cpp
 * 
 * Implementation file for signal and state management
 */

 #include "signal_manager.h"
 #include "sensor.h"
 #include <string.h>
 
 // Global system signals
 static SystemSignals signals = {0, SYSTEM_IDLE, 0, 0, 0};
 
 // Mutex for protecting access to shared signals
 static SemaphoreHandle_t signalsMutex;
 
 /**
  * Update system state based on sensor data
  */
 static void updateSystemState(SystemSignals *signals) {
   // Check for sensor errors
   if (signals->distance < 0) {
     signals->state = SYSTEM_ERROR;
     signals->errorCode = 1; // Error code 1: Invalid distance reading
   }
   // Check if object is too close (less than 10cm)
   else if (signals->distance < 10) {
     signals->state = SYSTEM_MEASURING;
     signals->errorCode = 0; // No error
   }
   // Normal operation
   else {
     signals->state = SYSTEM_MEASURING;
     signals->errorCode = 0; // No error
   }
 }
 
 void signal_manager_init() {
   // Create mutex for signals
   signalsMutex = xSemaphoreCreateMutex();
   
   // Initialize signals
   signals.distance = 0;
   signals.state = SYSTEM_IDLE;
   signals.errorCode = 0;
   signals.measurementCount = 0;
   signals.lastMeasurementTime = 0;
 }
 
 void signal_manager_update(float distance) {
   // Acquire mutex before updating shared signals
   if (xSemaphoreTake(signalsMutex, pdMS_TO_TICKS(10)) == pdTRUE) {
     signals.distance = distance;
     signals.measurementCount++;
     signals.lastMeasurementTime = xTaskGetTickCount();
     
     // Update system state based on sensor data
     updateSystemState(&signals);
     
     // Release mutex
     xSemaphoreGive(signalsMutex);
   }
 }
 
 bool signal_manager_get_signals(SystemSignals *dest) {
   bool success = false;
   
   // Acquire mutex before reading shared signals
   if (xSemaphoreTake(signalsMutex, pdMS_TO_TICKS(10)) == pdTRUE) {
     // Copy signals to destination
     memcpy(dest, &signals, sizeof(SystemSignals));
     
     // Release mutex
     xSemaphoreGive(signalsMutex);
     
     success = true;
   }
   
   return success;
 }
 
 void acquisitionTask(void *pvParameters) {
   TickType_t xLastWakeTime;
   const TickType_t xFrequency = pdMS_TO_TICKS(100); // 100ms sampling rate
   
   // Initialize the xLastWakeTime variable with the current time
   xLastWakeTime = xTaskGetTickCount();
   
   for (;;) {
     // Wait for the next cycle with precise timing
     vTaskDelayUntil(&xLastWakeTime, xFrequency);
     
     // Read distance from sensor
     float distance = sensor_read_distance();
     
     // Update signals with new reading
     signal_manager_update(distance);
   }
 }