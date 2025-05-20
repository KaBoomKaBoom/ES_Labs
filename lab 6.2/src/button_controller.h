/**
 * button_controller.h
 * Header file for button handling module
 */
#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Button pin definitions
#define EV_REQUEST_PIN 2
#define NS_REQUEST_PIN 3
#define NIGHT_MODE_BUTTON 4

// Button request identifiers
typedef enum {
    NO_REQUEST = 0,
    EV_REQUEST = 1,
    NS_REQUEST = 2,
    NIGHT_MODE_REQUEST = 3
} ButtonRequest;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize button input pins and attach interrupts
 * 
 * @param queue Queue handle for button press events
 * @return 0 on success, -1 on failure
 */
int buttonInit(QueueHandle_t queue);

/**
 * Check current button states
 * 
 * @param evState Pointer to store East-West button state (HIGH/LOW)
 * @param nsState Pointer to store North-South button state (HIGH/LOW)
 * @param nightModeState Pointer to store Night Mode button state (HIGH/LOW)
 */
void buttonGetStates(int* evState, int* nsState, int* nightModeState);

/**
 * Get the string representation of a button request
 * 
 * @param request The button request to describe
 * @return String describing the button request
 */
const char* buttonGetRequestName(ButtonRequest request);

/**
 * Get the string representation of a button state
 * 
 * @param state The button state (HIGH/LOW)
 * @return String describing the button state
 */
const char* buttonGetStateName(int state);

#ifdef __cplusplus
}
#endif

#endif // BUTTON_CONTROLLER_H