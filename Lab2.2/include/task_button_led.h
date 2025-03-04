/**
 * Arduino FreeRTOS Project - Button-LED Task
 * 
 * This file contains the declaration for the task that handles
 * toggling LED1 based on Button1 press.
 */

 #ifndef TASK_BUTTON_LED_H
 #define TASK_BUTTON_LED_H
 
 #include <Arduino_FreeRTOS.h>
 
 /* Task 1: Button-LED Task - Changes LED1 state on button press */
 void button_led_task(void *pvParameters);
 
 #endif /* TASK_BUTTON_LED_H */