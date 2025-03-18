#include "TaskManager.h"

// Task handles
TaskHandle_t buttonLedTaskHandle = NULL;
TaskHandle_t syncTaskHandle = NULL;
TaskHandle_t asyncTaskHandle = NULL;

// Synchronization and communication
SemaphoreHandle_t buttonSemaphore = NULL;
QueueHandle_t dataBuffer = NULL;

// Objects
Button button(BUTTON_PIN);
Led led1(LED1_PIN);
Led led2(LED2_PIN);

void initTaskManager() {
    // Create semaphore for button press synchronization
    buttonSemaphore = xSemaphoreCreateBinary();
    // Create queue for data communication between tasks
    dataBuffer = xQueueCreate(10, sizeof(uint8_t[10]));
    
    xTaskCreate(buttonLedTask,"ButtonLedTask",128,NULL, 1, NULL);
    xTaskCreate(syncTask,"SyncTask",128,NULL,2,NULL);
    xTaskCreate(asyncTask,"AsyncTask",128,NULL,3,NULL);
}

// Task 1: Button LED - Checks button state and signals with semaphore
void buttonLedTask(void *pvParameters) {
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    
    while (1) {
        if (button.isPressed()) {
            printf("Button pressed\n");
            led1.turnOn();
            xSemaphoreGive(buttonSemaphore);
            vTaskDelay(pdMS_TO_TICKS(BUTTON_LED_DURATION_MS));
            led1.turnOff();
        }
        
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(TASK1_PERIOD_MS));
    }
}

// Task 2: Synchronized Task - Waits for semaphore, increments N, sends N bytes
void syncTask(void *pvParameters) {
    static uint8_t N = 0;
    while (1) {
        // Wait for semaphore from Task 1
        if (xSemaphoreTake(buttonSemaphore, portMAX_DELAY) == pdTRUE) {
            N++;
            uint8_t data[N];
            for (uint8_t i = 0; i < N; i++) {
                data[i] = i + 1;
            }
            xQueueSendToFront(dataBuffer, &data, portMAX_DELAY);
            for (uint8_t i = 0; i < N; i++) {
                led2.turnOn();
                vTaskDelay(pdMS_TO_TICKS(LED_ON_DURATION_MS));
                led2.turnOff();
                vTaskDelay(pdMS_TO_TICKS(LED_OFF_DURATION_MS));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(TASK2_INTERVAL_MS));
    }
}

// Task 3: Asynchronous Task - Reads buffer every 200ms and displays data
void asyncTask(void *pvParameters) {
    uint8_t receivedData[10];
    while (1)
    {
        if (xQueueReceive(dataBuffer, &receivedData, portMAX_DELAY) == pdTRUE) {
            printf("Data: ");
            for (uint8_t i = 0; i < sizeof(receivedData); i++)
            {
                if (receivedData[i] == 0) {
                    printf("\n");
                    break;
                }
                printf("%d", receivedData[i]);
                printf(" ");
            }  
        }
        vTaskDelay(pdMS_TO_TICKS(TASK3_PERIOD_MS));
    }
}