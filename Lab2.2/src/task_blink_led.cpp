/**
 * Arduino FreeRTOS Project - Blinking LED Task Implementation
 */

 #include <Arduino.h>
 #include <Arduino_FreeRTOS.h>
 #include <semphr.h>
 #include "config.h"
 #include "task_blink_led.h"
 #include "led.h"
 
 /* Task 2: Blinking LED Task - LED2 blinks when LED1 is off */
 void blink_led_task(void *pvParameters) {
    
   /* Task offset */
   vTaskDelay(pdMS_TO_TICKS(BLINK_LED_TASK_OFFSET));
   
   TickType_t last_wake_time = xTaskGetTickCount();
   int blink_count = 0;
   
   for (;;) {
     /* Check if LED1 is off */
     if (!led1_state) {
       /* Toggle LED2 state based on blink counter */
       if (blink_count < blink_counter) {
         led2_state = !led2_state;
         turnOnLed(LED2_PIN);
         
         /* Increment blink count only when turning on */
         if (led2_state) {
           blink_count++;
         }
         
         /* Signal LED state change for display task (provider) */
         xSemaphoreGive(led_state_semaphore);
       } else {
         if (led2_state) {
           led2_state = false;
           turnOffLed(LED2_PIN);
           xSemaphoreGive(led_state_semaphore);
         }
         blink_count = 0;  // Reset for next cycle
       }
     } else {
       /* If LED1 is on, make sure LED2 is off */
       if (led2_state) {
         led2_state = false;
         turnOffLed(LED2_PIN);
         xSemaphoreGive(led_state_semaphore);
       }
       blink_count = 0;  // Reset counter
     }
     
     /* Wait until next period */
     vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(BLINK_LED_TASK_PERIOD));
   }
 }