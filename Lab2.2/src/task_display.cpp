/**
 * Arduino FreeRTOS Project - Display Task Implementation
 */

 #include <Arduino.h>
 #include <Arduino_FreeRTOS.h>
 #include <semphr.h>
 #include "config.h"
 #include "task_display.h"
 
 
 /* Task 4: Display Task - Displays program states using provider/consumer mechanism */
 void display_task(void *pvParameters) {
   /* Task offset */
   vTaskDelay(pdMS_TO_TICKS(DISPLAY_TASK_OFFSET));
   
   TickType_t last_wake_time = xTaskGetTickCount();
   
   for (;;) {
     /* Check for LED state change (consumer) */
     if (xSemaphoreTake(led_state_semaphore, 0) == pdTRUE) {
       printf("LED1 State: ");
       printf(led1_state ? "ON" : "OFF");
       printf("LED2 State: ");
       printf(led2_state ? "ON" : "OFF");
     }
     
     /* Check for button 1 press (consumer) */
     if (xSemaphoreTake(button1_semaphore, 0) == pdTRUE) {
       printf("Button 1 Pressed! LED1 toggled.");
       button1_pressed = false;  // Reset the flag
     }
     
     /* Check for button 2 press (consumer) */
     if (xSemaphoreTake(button2_semaphore, 0) == pdTRUE) {
       printf("Button 2 Pressed! Blink counter incremented to: ");
       Serial.println(blink_counter);
       button2_pressed = false;  // Reset the flag
     }
     
     /* Check for button 3 press (consumer) */
     if (xSemaphoreTake(button3_semaphore, 0) == pdTRUE) {
       printf("Button 3 Pressed! Blink counter decremented to: ");
       Serial.println(blink_counter);
       button3_pressed = false;  // Reset the flag
     }
     
     /* Wait until next period */
     vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(DISPLAY_TASK_PERIOD));
   }
 }