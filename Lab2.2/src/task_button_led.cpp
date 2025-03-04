/**
 * Arduino FreeRTOS Project - Button-LED Task Implementation
 */

 #include <Arduino.h>
 #include <Arduino_FreeRTOS.h>
 #include <semphr.h>
 #include "config.h"
 #include "button_utils.h"
 #include "task_button_led.h"
 
 /* Task 1: Button-LED Task - Changes LED1 state on button press */
 void button_led_task(void *pvParameters) {
   /* Task offset */
   vTaskDelay(pdMS_TO_TICKS(BUTTON_LED_TASK_OFFSET));
   
   TickType_t last_wake_time = xTaskGetTickCount();
   bool last_button_state = false;
   
   for (;;) {
     /* Read button state */
     bool current_button_state = read_button(BUTTON1_PIN);
     
     /* Detect button press (transition from not pressed to pressed) */
     if (current_button_state && !last_button_state) {
       /* Toggle LED1 state */
       led1_state = !led1_state;
       digitalWrite(LED1_PIN, led1_state ? HIGH : LOW);
       
       /* Signal button press for display task (provider) */
       button1_pressed = true;
       xSemaphoreGive(button1_semaphore);
       
       /* Signal LED state change for display task (provider) */
       xSemaphoreGive(led_state_semaphore);
     }
     
     /* Update last button state */
     last_button_state = current_button_state;
     
     /* Wait until next period */
     vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(BUTTON_LED_TASK_PERIOD));
   }
 }