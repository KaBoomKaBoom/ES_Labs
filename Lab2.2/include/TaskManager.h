#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "Button.h"
#include "LED.h"
#include "SerialIO.h"

// Task handles
extern TaskHandle_t buttonLedTaskHandle;
extern TaskHandle_t syncTaskHandle;
extern TaskHandle_t asyncTaskHandle;

// Synchronization and communication
extern SemaphoreHandle_t buttonSemaphore;
extern QueueHandle_t dataBuffer;

// Task function prototypes
void buttonLedTask(void *pvParameters);
void syncTask(void *pvParameters);
void asyncTask(void *pvParameters);

// Task periods and delays
#define TASK1_PERIOD_MS         10      // Button LED task frequency
#define TASK2_INTERVAL_MS       50      // Sync Task interval for sending bytes
#define TASK3_PERIOD_MS         200     // Async Task read interval
#define LED_ON_DURATION_MS      300     // LED ON phase
#define LED_OFF_DURATION_MS     500     // LED OFF phase
#define BUTTON_LED_DURATION_MS  1000    // Duration to keep LED1 on after button press


// Pin definitions
#define BUTTON_PIN              3
#define LED1_PIN                2      // LED for Task 1 (Button LED)
#define LED2_PIN                12      // LED for Task 2 (Synchronized Task)

// Initialization function
void initTaskManager();

#endif // TASK_MANAGER_H