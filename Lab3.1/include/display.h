/*
 * display.h
 * 
 * Header file for display functionality
 */

 #ifndef DISPLAY_H
 #define DISPLAY_H
 
 #include "signal_manager.h"
 
 /**
  * Print formatted report using printf
  * 
  * @param signals pointer to the system signals to be displayed
  */
 void printReport(const SystemSignals *signals);
 
 /**
  * Task for displaying data on Serial
  * Uses vTaskDelay for timing
  */
 void displayTask(void *pvParameters);
 
 #endif // DISPLAY_H