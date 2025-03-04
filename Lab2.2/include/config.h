 #ifndef CONFIG_H
 #define CONFIG_H

 #include "Arduino_FreeRTOS.h"
 #include "semphr.h"
 
 /* Pin Definitions */
 #define LED1_PIN        2   // LED1 connected to digital pin 2
 #define LED2_PIN        3   // LED2 connected to digital pin 3
 #define BUTTON1_PIN     4   // Button1 connected to digital pin 4
 #define BUTTON2_PIN     5   // Button2 connected to digital pin 5 (Increment)
 #define BUTTON3_PIN     6   // Button3 connected to digital pin 6 (Decrement)
 
 /* Task Periods (ms) */
 #define BUTTON_LED_TASK_PERIOD      50
 #define BLINK_LED_TASK_PERIOD       100
 #define COUNTER_TASK_PERIOD         50 
 #define DISPLAY_TASK_PERIOD         200
 
 /* Task Offsets (ms) */
 #define BUTTON_LED_TASK_OFFSET      0
 #define BLINK_LED_TASK_OFFSET       10
 #define COUNTER_TASK_OFFSET         20
 #define DISPLAY_TASK_OFFSET         30
 
 /* External declarations for global variables */
 extern bool led1_state;
 extern bool led2_state;
 extern int blink_counter;
 extern bool button1_pressed;
 extern bool button2_pressed;
 extern bool button3_pressed;
 
 /* External declarations for semaphores */
 extern SemaphoreHandle_t button1_semaphore;
 extern SemaphoreHandle_t button2_semaphore;
 extern SemaphoreHandle_t button3_semaphore;
 extern SemaphoreHandle_t led_state_semaphore;
 
 #endif /* CONFIG_H */