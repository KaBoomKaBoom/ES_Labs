/*
 * signal_manager.h
 * 
 * Header file for signal and state management
 */

 #ifndef SIGNAL_MANAGER_H
 #define SIGNAL_MANAGER_H
 
 #include <Arduino.h>
 #include <Arduino_FreeRTOS.h>
 #include <semphr.h>
 
 // System state definitions
 typedef enum {
   SYSTEM_IDLE,
   SYSTEM_MEASURING,
   SYSTEM_ERROR
 } SystemState;
 
 // Signal structure to hold sensor data and system state
 typedef struct {
   float distance;         // Distance measured by ultrasonic sensor in cm
   SystemState state;      // Current system state
   uint8_t errorCode;      // Error code (0 = no error)
   uint32_t measurementCount; // Count of measurements taken
   TickType_t lastMeasurementTime; // Time of last measurement
 } SystemSignals;
 
 /**
  * Initialize the signal manager
  */
 void signal_manager_init();
 
 /**
  * Update system signals with new sensor data
  * 
  * @param distance the newly measured distance
  */
 void signal_manager_update(float distance);
 
 /**
  * Get a copy of the current system signals
  * 
  * @param dest pointer to a SystemSignals struct to be filled with current values
  * @return true if successful, false if mutex could not be acquired
  */
 bool signal_manager_get_signals(SystemSignals *dest);
 
 /**
  * Task for acquiring data from the ultrasonic sensor
  * Uses vTaskDelayUntil for precise timing
  */
 void acquisitionTask(void *pvParameters);
 
 #endif // SIGNAL_MANAGER_H