/**
 * Arduino FreeRTOS Project - Counter Task
 * 
 * This file contains the declaration for the task that handles
 * incrementing/decrementing the blink counter based on button presses.
 */

 #ifndef TASK_COUNTER_H
 #define TASK_COUNTER_H
 
 #include <Arduino_FreeRTOS.h>
 
 /* Task 3: Counter Task - Increments/decrements a variable using two buttons */
 void counter_task(void *pvParameters);
 
 #endif /* TASK_COUNTER_H */