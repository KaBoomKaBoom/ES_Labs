/*
 * display.cpp
 * 
 * Implementation file for display functionality
 */

 #include "display.h"
 #include <stdio.h>
 
 void printReport(const SystemSignals *signals) {
   // Print header
   printf("\n========== SYSTEM REPORT ==========\n");
   
   // Print current time
   printf("Time: %lu ms\n", (unsigned long)xTaskGetTickCount());
   
   // Print system state
   printf("State: ");
   switch (signals->state) {
     case SYSTEM_IDLE:
       printf("IDLE\n");
       break;
     case SYSTEM_MEASURING:
       printf("MEASURING\n");
       break;
     case SYSTEM_ERROR:
       printf("ERROR\n");
       break;
     default:
       printf("UNKNOWN\n");
   }
   
   // Print distance
   printf("Distance: %.2f cm\n", signals->distance);
   
   // Print measurement count
   printf("Measurements: %lu\n", (unsigned long)signals->measurementCount);
   
   // Print error code if any
   if (signals->errorCode > 0) {
     printf("Error Code: %d\n", signals->errorCode);
   }
   
   printf("====================================\n");
 }
 
 void displayTask(void *pvParameters) {
   // Add a small delay to offset from acquisition task
   vTaskDelay(pdMS_TO_TICKS(50));
   
   const TickType_t xFrequency = pdMS_TO_TICKS(500); // 500ms update rate
   SystemSignals localSignals;
   
   for (;;) {
     // Get a copy of the current signals
     if (signal_manager_get_signals(&localSignals)) {
       // Print report using printf
       printReport(&localSignals);
     }
     
     // Wait for the next cycle
     vTaskDelay(xFrequency);
   }
 }