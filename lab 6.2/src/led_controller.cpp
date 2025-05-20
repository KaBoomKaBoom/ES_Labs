/**
 * led_controller.cpp
 * Implementation of the LED control module
 */
#include "led_controller.h"
#include <stdio.h>

// Static state descriptions
static const char* STATE_DESCRIPTIONS[] = {
    "East-West: GREEN, North-South: RED",
    "East-West: YELLOW, North-South: YELLOW",
    "East-West: RED, North-South: GREEN",
    "Night Mode: YELLOW BLINKING"
};

/**
 * Initialize all LED pins as outputs
 */
void ledInit(void) {
    pinMode(EV_RED_PIN, OUTPUT);
    pinMode(EV_YELLOW_PIN, OUTPUT);
    pinMode(EV_GREEN_PIN, OUTPUT);
    pinMode(NS_RED_PIN, OUTPUT);
    pinMode(NS_YELLOW_PIN, OUTPUT);
    pinMode(NS_GREEN_PIN, OUTPUT);
    
    // Set all LEDs to off initially
    ledAllOff();
}

/**
 * Update LED states based on the current traffic light state
 * 
 * @param state Current traffic light state
 * @return 0 on success, -1 on failure
 */
int ledUpdate(TrafficLightState state) {
    // Validate state
    if (state != EV_GREEN_NS_RED && 
        state != EV_YELLOW_NS_YELLOW && 
        state != EV_RED_NS_GREEN &&
        state != NIGHT_MODE) {
        return -1;
    }
    
    // Turn off all LEDs first to avoid any overlapping states
    ledAllOff();
    
    // Set LEDs based on state
    switch (state) {
        case EV_GREEN_NS_RED:
            digitalWrite(EV_GREEN_PIN, HIGH);
            digitalWrite(NS_RED_PIN, HIGH);
            break;
            
        case EV_YELLOW_NS_YELLOW:
            digitalWrite(EV_YELLOW_PIN, HIGH);
            digitalWrite(NS_YELLOW_PIN, HIGH);
            break;
            
        case EV_RED_NS_GREEN:
            digitalWrite(EV_RED_PIN, HIGH);
            digitalWrite(NS_GREEN_PIN, HIGH);
            break;
            
        case NIGHT_MODE:
            digitalWrite(EV_YELLOW_PIN, HIGH);
            digitalWrite(NS_YELLOW_PIN, HIGH);
            break;
    }
    
    printf("LED State: %s\n", ledGetStateDescription(state));
    return 0;
}

/**
 * Turn off all LEDs
 */
void ledAllOff(void) {
    digitalWrite(EV_RED_PIN, LOW);
    digitalWrite(EV_YELLOW_PIN, LOW);
    digitalWrite(EV_GREEN_PIN, LOW);
    digitalWrite(NS_RED_PIN, LOW);
    digitalWrite(NS_YELLOW_PIN, LOW);
    digitalWrite(NS_GREEN_PIN, LOW);
}

/**
 * Get human-readable description of the current state
 * 
 * @param state Current traffic light state
 * @return String description of the state
 */
const char* ledGetStateDescription(TrafficLightState state) {
    if (state >= 0 && state <= NIGHT_MODE) {
        return STATE_DESCRIPTIONS[state];
    } else {
        return "Unknown state";
    }
}