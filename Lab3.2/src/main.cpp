/**
 * Ultrasonic Sensor Application with FreeRTOS for Arduino Uno
 * Main file: Contains setup, loop and main task
 */

 #include <Arduino.h>
 #include <Arduino_FreeRTOS.h>
 #include <semphr.h>
 #include <stdio.h>
 #include "ultrasonic.h"
 #include "filter.h"
 #include "printf_redirect.h"
 
 #define STACK_SIZE 256  // Increase stack size

 // Task parameters
 #define STACK_SIZE          128     // Reduced stack size for Arduino Uno
 #define ACQUISITION_PERIOD  100     // Acquisition period in milliseconds
 
 // Signal conditioning parameters
 #define SALT_PEPPER_WINDOW  5       // Window size for salt and pepper filter
 #define WEIGHTED_AVG_WINDOW 5       // Reduced window size for Arduino memory constraints
 
 // Filter buffers
 static float salt_pepper_buffer[SALT_PEPPER_WINDOW];
 static float weighted_avg_buffer[WEIGHTED_AVG_WINDOW];
 // Weights for weighted average (must sum to 1.0)
 static const float weights[WEIGHTED_AVG_WINDOW] = {0.1, 0.2, 0.4, 0.2, 0.1}; 
 
 // Function prototypes
 void ultrasonic_distance_task(void *pvParameters);
 
 // Mutex for data access protection
 SemaphoreHandle_t data_mutex;
 
 void printDistance(const char *label, float distance)
 {
   char buffer[10]; // Ensure enough space for the formatted string
   dtostrf(distance, 5, 2, buffer); // Convert float to string
   printf("%s: %s cm\n", label, buffer); // Use %s instead of %f
 }
 

 void setup() {
   // Initialize serial communication
   Serial.begin(9600);
   while (!Serial) {
     ; // Wait for serial port to connect
   }
   
   // Initialize printf redirection
   init_printf_redirect();
   
   printf("Ultrasonic Sensor Application Starting...\n");
   
   // Create mutex
   data_mutex = xSemaphoreCreateMutex();
   
   // Initialize hardware
   setup_ultrasonic_sensor();
   
   // Initialize filter buffers
   for (int i = 0; i < SALT_PEPPER_WINDOW; i++) {
     salt_pepper_buffer[i] = 0.0;
   }
   for (int i = 0; i < WEIGHTED_AVG_WINDOW; i++) {
     weighted_avg_buffer[i] = 0.0;
   }
   
   // Create task
   xTaskCreate(
     ultrasonic_distance_task,       // Task function
     "ultrasonic",                   // Task name
     STACK_SIZE,                     // Stack size
     NULL,                           // Parameters
     1,                              // Priority
     NULL                            // Task handle
   );
   
   printf("Application initialized successfully\n");
   
   // Start the scheduler
   vTaskStartScheduler();
 }
 
 void loop() {
   // Empty. Things are done in Tasks.
 }
 
 /**
  * Task for ultrasonic distance measurement and processing
  */
 void ultrasonic_distance_task(void *pvParameters) {
   (void) pvParameters;
   
   TickType_t last_wake_time;
   const TickType_t period = pdMS_TO_TICKS(ACQUISITION_PERIOD);
   
   // Initialize the last_wake_time variable with the current time
   last_wake_time = xTaskGetTickCount();
   
   float raw_distance, filtered_distance1, filtered_distance2, final_distance;
   
   while (1) {
     // Get raw distance measurement
     raw_distance = measure_distance();
     
     // Apply salt and pepper filter
     filtered_distance1 = apply_salt_pepper_filter(raw_distance, salt_pepper_buffer, SALT_PEPPER_WINDOW);
     
     // Apply weighted average filter
     filtered_distance2 = apply_weighted_average_filter(filtered_distance1, weighted_avg_buffer, weights, WEIGHTED_AVG_WINDOW);
     
     // Apply saturation to keep values in valid range
     final_distance = apply_saturation(filtered_distance2, MIN_DISTANCE_CM, MAX_DISTANCE_CM);
     
     // Acquire mutex to print data
     if (xSemaphoreTake(data_mutex, portMAX_DELAY) == pdTRUE) {
       // Print results using printf
       printf("Distance Measurements:\n");
       printDistance("Raw", raw_distance);
       printDistance("After Salt & Pepper", filtered_distance1);
       printDistance("After Weighted Avg", filtered_distance2);
       printDistance("Final (Saturated)", final_distance);
       
       
       // Release mutex
       xSemaphoreGive(data_mutex);
     }
     
     // Wait precisely for the next cycle using vTaskDelayUntil
     vTaskDelayUntil(&last_wake_time, period);
   }
 }