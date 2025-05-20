/**
 * led_controller.h
 * Header file for LED control module
 */
#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

// Traffic light pin definitions
// East-West traffic light pins
#define EV_RED_PIN     25
#define EV_YELLOW_PIN  26
#define EV_GREEN_PIN   27

// North-South traffic light pins
#define NS_RED_PIN     28
#define NS_YELLOW_PIN  29
#define NS_GREEN_PIN   30

// Traffic light states for LED control
typedef enum {
  EV_GREEN_NS_RED,
  EV_YELLOW_NS_YELLOW,
  EV_RED_NS_GREEN,
  NIGHT_MODE 
} TrafficLightState;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize all LED pins
 */
void ledInit(void);

/**
 * Update LED states based on the current traffic light state
 * 
 * @param state Current traffic light state
 * @return 0 on success, -1 on failure
 */
int ledUpdate(TrafficLightState state);

/**
 * Turn off all LEDs
 */
void ledAllOff(void);

/**
 * Get human-readable description of the current state
 * 
 * @param state Current traffic light state
 * @return String description of the state
 */
const char* ledGetStateDescription(TrafficLightState state);

#ifdef __cplusplus
}
#endif

#endif // LED_CONTROLLER_H