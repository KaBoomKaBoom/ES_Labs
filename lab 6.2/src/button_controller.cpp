/**
 * button_controller.cpp
 * Implementation of button handling module
 */
#include "button_controller.h"
#include <stdio.h>

// Static queue handle for ISRs
static QueueHandle_t buttonQueue = NULL;

// Static state descriptions
static const char* REQUEST_NAMES[] = {
    "NONE",
    "EAST-WEST REQUEST",
    "NORTH-SOUTH REQUEST",
    "NIGHT MODE REQUEST"
};

static const char* STATE_NAMES[] = {
    "ACTIVE",
    "INACTIVE"
};

/**
 * East-West button interrupt service routine
 */
static void buttonISR_EV() {
    ButtonRequest req = EV_REQUEST;
    xQueueSendFromISR(buttonQueue, &req, NULL);
}

/**
 * North-South button interrupt service routine
 */
static void buttonISR_NS() {
    ButtonRequest req = NS_REQUEST;
    xQueueSendFromISR(buttonQueue, &req, NULL);
}

/**
 * Night mode button interrupt service routine
 */
static void buttonISR_Night() {
    ButtonRequest req = NIGHT_MODE_REQUEST;
    xQueueSendFromISR(buttonQueue, &req, NULL);
}

/**
 * Initialize button input pins and attach interrupts
 * 
 * @param queue Queue handle for button press events
 * @return 0 on success, -1 on failure
 */
int buttonInit(QueueHandle_t queue) {
    if (queue == NULL) {
        return -1;
    }
    
    // Store queue handle for ISRs
    buttonQueue = queue;
    
    // Configure button pins as inputs with pull-up resistors
    pinMode(EV_REQUEST_PIN, INPUT_PULLUP);
    pinMode(NS_REQUEST_PIN, INPUT_PULLUP);
    pinMode(NIGHT_MODE_BUTTON, INPUT_PULLUP);

    // Attach interrupts for button presses
    attachInterrupt(digitalPinToInterrupt(EV_REQUEST_PIN), buttonISR_EV, FALLING);
    attachInterrupt(digitalPinToInterrupt(NS_REQUEST_PIN), buttonISR_NS, FALLING);
    attachInterrupt(digitalPinToInterrupt(NIGHT_MODE_BUTTON), buttonISR_Night, FALLING);
    
    printf("Button controller initialized\n");
    return 0;
}

/**
 * Check current button states
 * 
 * @param evState Pointer to store East-West button state (HIGH/LOW)
 * @param nsState Pointer to store North-South button state (HIGH/LOW)
 * @param nightModeState Pointer to store Night Mode button state (HIGH/LOW)
 */
void buttonGetStates(int* evState, int* nsState, int* nightModeState) {
    if (evState != NULL) {
        *evState = digitalRead(EV_REQUEST_PIN);
    }
    
    if (nsState != NULL) {
        *nsState = digitalRead(NS_REQUEST_PIN);
    }
    
    if (nightModeState != NULL) {
        *nightModeState = digitalRead(NIGHT_MODE_BUTTON);
    }
}

/**
 * Get the string representation of a button request
 * 
 * @param request The button request to describe
 * @return String describing the button request
 */
const char* buttonGetRequestName(ButtonRequest request) {
    if (request >= NO_REQUEST && request <= NIGHT_MODE_REQUEST) {
        return REQUEST_NAMES[request];
    } else {
        return "UNKNOWN REQUEST";
    }
}

/**
 * Get the string representation of a button state
 * 
 * @param state The button state (HIGH/LOW)
 * @return String describing the button state
 */
const char* buttonGetStateName(int state) {
    return (state == LOW) ? STATE_NAMES[0] : STATE_NAMES[1];
}