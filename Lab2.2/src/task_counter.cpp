/**
 * Arduino FreeRTOS Project - Counter Task Implementation
 */

 #include <Arduino.h>
 #include <Arduino_FreeRTOS.h>
 #include <semphr.h>
 #include "config.h"
 #include "button_utils.h"
 #include "task_counter.h"
 
 /* Task 3: Counter Task - Increments/decrements a variable using two buttons */
 void counter_task(void *pvParameters) {
   /* Task offset */
   vTaskDelay(pdMS_TO_TICKS(COUNTER_TASK_OFFSET));
   
   TickType_t last_wake_time = xTaskGetTickCount();
   bool last_button2_state = false;
   bool last_button3_state = false;
   
   for (;;) {
     /* Read button states */
     bool current_button2_state = read_button(BUTTON2_PIN);
     bool current_button3_state = read_button(BUTTON3_PIN);
     
     /* Detect button 2 press (increment) */
     if (current_button2_state && !last_button2_state) {
       blink_counter++;
       if (blink_counter > 20) blink_counter = 20;  // Limit maximum value
       
       /* Signal button press for display task (provider) */
       button2_pressed = true;
       xSemaphoreGive(button2_semaphore);
     }
     
     /* Detect button 3 press (decrement) */
     if (current_button3_state && !last_button3_state) {
       blink_counter--;
       if (blink_counter < 1) blink_counter = 1;  // Limit minimum value
       
       /* Signal button press for display task (provider) */
       button3_pressed = true;
       xSemaphoreGive(button3_semaphore);
     }
     
     /* Update last button states */
     last_button2_state = current_button2_state;
     last_button3_state = current_button3_state;
     
     /* Wait until next period */
     vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(COUNTER_TASK_PERIOD));
   }
 }