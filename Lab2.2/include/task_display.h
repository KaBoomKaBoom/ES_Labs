/**
 * Arduino FreeRTOS Project - Display Task
 * 
 * This file contains the declaration for the task that handles
 * displaying system states via Serial.
 */

 #ifndef TASK_DISPLAY_H
 #define TASK_DISPLAY_H
 
 #include <Arduino_FreeRTOS.h>
 
 /* Task 4: Display Task - Displays program states using provider/consumer mechanism */
 void display_task(void *pvParameters);
 
 #endif /* TASK_DISPLAY_H */