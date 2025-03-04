/**
 * Arduino FreeRTOS Project - Blinking LED Task
 * 
 * This file contains the declaration for the task that handles
 * blinking LED2 when LED1 is off.
 */

 #ifndef TASK_BLINK_LED_H
 #define TASK_BLINK_LED_H
 
 #include <Arduino_FreeRTOS.h>
 
 /* Task 2: Blinking LED Task - LED2 blinks when LED1 is off */
 void blink_led_task(void *pvParameters);
 
 #endif /* TASK_BLINK_LED_H */