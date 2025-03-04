/**
 * Arduino FreeRTOS Project - Main File
 * 
 * This is the main file of the project that includes all necessary headers
 * and implements the setup() and loop() functions.
 */

 #include <Arduino.h>
 #include <Arduino_FreeRTOS.h>
 #include <semphr.h>
 #include "config.h"
 #include "task_button_led.h"
 #include "task_blink_led.h"
 #include "task_counter.h"
 #include "task_display.h"
 #include "button_utils.h"
 #include "globals.h"
 
 // Global semaphores
 SemaphoreHandle_t button1_semaphore;
 SemaphoreHandle_t button2_semaphore;
 SemaphoreHandle_t button3_semaphore;
 SemaphoreHandle_t led_state_semaphore;
 
 // Global variables
 bool led1_state = false;
 bool led2_state = false;
 int blink_counter = 5;  // Default number of blinks/time
 bool button1_pressed = false;
 bool button2_pressed = false;
 bool button3_pressed = false;
 
 void setup() {
   /* Initialize Serial communication */
   setupPrintf();
   Serial.begin(9600);
   while (!Serial) {
     ; // Wait for serial port to connect
   }
   
   /* Initialize pins */
   pinMode(LED1_PIN, OUTPUT);
   pinMode(LED2_PIN, OUTPUT);
   pinMode(BUTTON1_PIN, INPUT_PULLUP);  // Using internal pull-up resistors
   pinMode(BUTTON2_PIN, INPUT_PULLUP);
   pinMode(BUTTON3_PIN, INPUT_PULLUP);
   
   /* Initialize LEDs to OFF */
   digitalWrite(LED1_PIN, LOW);
   digitalWrite(LED2_PIN, LOW);
   
   printf("FreeRTOS Multiple Tasks Application");
   printf("-------------------------------------");
   
   /* Create semaphores */
   button1_semaphore = xSemaphoreCreateBinary();
   button2_semaphore = xSemaphoreCreateBinary();
   button3_semaphore = xSemaphoreCreateBinary();
   led_state_semaphore = xSemaphoreCreateBinary();
   
   /* Create tasks */
   xTaskCreate(
     button_led_task,        // Task function
     "ButtonLED",            // Task name
     128,                    // Stack size
     NULL,                   // Parameters
     3,                      // Priority (higher number = higher priority)
     NULL                    // Task handle
   );
   
   xTaskCreate(
     blink_led_task,
     "BlinkLED",
     128,
     NULL,
     2,
     NULL
   );
   
   xTaskCreate(
     counter_task,
     "Counter",
     128,
     NULL,
     1,
     NULL
   );
   
   xTaskCreate(
     display_task,
     "Display",
     256,                    // Larger stack for Serial
     NULL,
     4,                      // Highest priority
     NULL
   );
   
   // The scheduler is started automatically by Arduino_FreeRTOS
 }
 
 void loop() {
   // Empty as tasks are managed by FreeRTOS
 }