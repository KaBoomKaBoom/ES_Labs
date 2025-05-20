/**
 * traffic_light_controller.h
 * Header file for traffic light controller system
 */
#ifndef TRAFFIC_LIGHT_CONTROLLER_H
#define TRAFFIC_LIGHT_CONTROLLER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include <stdio.h>
#include "led_controller.h"
#include "button_controller.h"
#include "srv_serial_stdio.h"

// Timing constants
#define YELLOW_TIME    3000

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize traffic light controller
 * 
 * @return 0 on success, -1 on failure
 */
int trafficLightInit(void);

/**
 * Update traffic light state (can be called from external modules)
 * 
 * @param newState New traffic light state to set
 * @return 0 on success, -1 on failure
 */
int trafficLightUpdateState(TrafficLightState newState);

/**
 * Get current traffic light state
 * 
 * @return Current traffic light state
 */
TrafficLightState trafficLightGetState(void);
}
#ifdef __Cpp

#endif
#endif // TRAFFIC_LIGHT_CONTROLLER_H

