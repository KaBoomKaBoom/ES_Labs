/**
 * traffic_light_controller.cpp
 * Implementation of traffic light controller system
 */
#include "traffic_light_controller.h"

// Global variables
static TrafficLightState currentState = EV_GREEN_NS_RED;
static QueueHandle_t stateChangeQueue = NULL;
static SemaphoreHandle_t stateChangeMutex = NULL;
static bool isNightMode = false;

// Task handles
static TaskHandle_t trafficLightTaskHandle = NULL;
static TaskHandle_t monitorTaskHandle = NULL;

/**
 * Traffic light control task
 * Handles state transitions based on button presses
 */
// Helper function to blink both yellow LEDs
static void blinkYellowLEDs(int times, int delayMs) {
    for (int i = 0; i < times; i++) {
        digitalWrite(EV_YELLOW_PIN, HIGH);
        digitalWrite(NS_YELLOW_PIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(delayMs));

        digitalWrite(EV_YELLOW_PIN, LOW);
        digitalWrite(NS_YELLOW_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(delayMs));
    }
}

static void trafficLightTask(void *pvParameters) {
    ButtonRequest requestType;

    while (1) {
        if (xQueueReceive(stateChangeQueue, &requestType, portMAX_DELAY)) {
            if (requestType == NIGHT_MODE_REQUEST) {
                xSemaphoreTake(stateChangeMutex, portMAX_DELAY);
                isNightMode = !isNightMode;
                if (isNightMode) {
                    currentState = NIGHT_MODE;
                    ledUpdate(currentState);
                    // Start blinking yellow LEDs continuously
                    while (isNightMode) {
                        digitalWrite(EV_YELLOW_PIN, HIGH);
                        digitalWrite(NS_YELLOW_PIN, HIGH);
                        vTaskDelay(pdMS_TO_TICKS(500));
                        digitalWrite(EV_YELLOW_PIN, LOW);
                        digitalWrite(NS_YELLOW_PIN, LOW);
                        vTaskDelay(pdMS_TO_TICKS(500));
                        // Check if a new request (night mode toggle) has arrived
                        if (xQueueReceive(stateChangeQueue, &requestType, 0)) {
                            if (requestType == NIGHT_MODE_REQUEST) {
                                isNightMode = false;
                                currentState = EV_GREEN_NS_RED;
                                ledUpdate(currentState);
                                break;
                            }
                        }
                    }
                } else {
                    currentState = EV_GREEN_NS_RED;
                    ledUpdate(currentState);
                }
                xSemaphoreGive(stateChangeMutex);
            }
            else if (!isNightMode) {
                if (requestType == EV_REQUEST && currentState == EV_RED_NS_GREEN) {
                    xSemaphoreTake(stateChangeMutex, portMAX_DELAY);
                    currentState = EV_YELLOW_NS_YELLOW;
                    ledUpdate(currentState);
                    xSemaphoreGive(stateChangeMutex);

                    vTaskDelay(pdMS_TO_TICKS(YELLOW_TIME));

                    blinkYellowLEDs(3, 500);

                    xSemaphoreTake(stateChangeMutex, portMAX_DELAY);
                    currentState = EV_GREEN_NS_RED;
                    ledUpdate(currentState);
                    xSemaphoreGive(stateChangeMutex);
                }
                else if (requestType == NS_REQUEST && currentState == EV_GREEN_NS_RED) {
                    xSemaphoreTake(stateChangeMutex, portMAX_DELAY);
                    currentState = EV_YELLOW_NS_YELLOW;
                    ledUpdate(currentState);
                    xSemaphoreGive(stateChangeMutex);

                    vTaskDelay(pdMS_TO_TICKS(YELLOW_TIME));

                    blinkYellowLEDs(3, 500);

                    xSemaphoreTake(stateChangeMutex, portMAX_DELAY);
                    currentState = EV_RED_NS_GREEN;
                    ledUpdate(currentState);
                    xSemaphoreGive(stateChangeMutex);
                }
            }
        }
    }
}

/**
 * Monitor task
 * Periodically reports system status
 */
static void monitorTask(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    int evState, nsState, nightModeState;

    while (1) {
        printf("Traffic light state: %s\n", ledGetStateDescription(currentState));
        
        buttonGetStates(&evState, &nsState, &nightModeState);
        printf("EV Request: %s, NS Request: %s, Night Mode Button: %s\n", 
               buttonGetStateName(evState),
               buttonGetStateName(nsState),
               buttonGetStateName(nightModeState));

        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(1000));
    }
}

/**
 * Initialize traffic light controller
 * 
 * @return 0 on success, -1 on failure
 */
int trafficLightInit(void) {
    // Initialize communication
    srvSerialSetup();
    printf("Initializing traffic light controller...\n");
    
    // Create communication primitives
    stateChangeQueue = xQueueCreate(5, sizeof(ButtonRequest));
    stateChangeMutex = xSemaphoreCreateMutex();

    if (stateChangeQueue == NULL || stateChangeMutex == NULL) {
        printf("Failed to create queue or mutex\n");
        return -1;
    }

    // Initialize LED module
    ledInit();
    
    // Initialize button module
    if (buttonInit(stateChangeQueue) != 0) {
        printf("Failed to initialize button controller\n");
        return -1;
    }

    // Set initial state
    currentState = EV_GREEN_NS_RED;
    ledUpdate(currentState);

    // Create tasks
    if (xTaskCreate(trafficLightTask, "TrafficLightTask", 256, NULL, 2, &trafficLightTaskHandle) != pdPASS) {
        printf("Failed to create traffic light task\n");
        return -1;
    }
    
    if (xTaskCreate(monitorTask, "MonitorTask", 256, NULL, 1, &monitorTaskHandle) != pdPASS) {
        printf("Failed to create monitor task\n");
        return -1;
    }

    printf("Arduino Mega traffic light system initialized\n");
    return 0;
}

/**
 * Update traffic light state (can be called from external modules)
 * 
 * @param newState New traffic light state to set
 * @return 0 on success, -1 on failure
 */
int trafficLightUpdateState(TrafficLightState newState) {
    if (xSemaphoreTake(stateChangeMutex, portMAX_DELAY) == pdTRUE) {
        currentState = newState;
        int result = ledUpdate(currentState);
        xSemaphoreGive(stateChangeMutex);
        return result;
    }
    return -1;
}

/**
 * Get current traffic light state
 * 
 * @return Current traffic light state
 */
TrafficLightState trafficLightGetState(void) {
    TrafficLightState state;
    if (xSemaphoreTake(stateChangeMutex, portMAX_DELAY) == pdTRUE) {
        state = currentState;
        xSemaphoreGive(stateChangeMutex);
    }
    return state;
}