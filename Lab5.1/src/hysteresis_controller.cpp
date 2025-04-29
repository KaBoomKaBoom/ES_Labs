/**
 * hysteresis_controller.cpp
 * Implementation of ON-OFF control with hysteresis
 */

 #include "hysteresis_controller.h"

 HysteresisController::HysteresisController() {
     setPoint = DEFAULT_SETPOINT;
     hysteresis = DEFAULT_HYSTERESIS;
     relayState = false;
 }
 
 void HysteresisController::begin() {
     pinMode(RELAY_PIN, OUTPUT);
     digitalWrite(RELAY_PIN, LOW);  // Initialize relay as OFF
 }
 
 bool HysteresisController::update(float currentTemperature) {
     bool previousState = relayState;
     
     // Hysteresis control logic
     // - Turn ON if temperature falls below (setPoint - hysteresis) 
     // - Turn OFF if temperature rises above (setPoint + hysteresis)
     
     if (currentTemperature < (setPoint - hysteresis)) {
         relayState = true;
     } else if (currentTemperature > (setPoint + hysteresis)) {
         relayState = false;
     }
     // If temperature is between thresholds, maintain previous state
     
     // Update relay output if state changed
     if (previousState != relayState) {
         digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
         return true;  // State changed
     }
     
     return false;  // No change
 }
 
 bool HysteresisController::setSetPoint(float newSetPoint) {
     // Validate setpoint within allowed range
     if (newSetPoint >= MIN_TEMPERATURE && newSetPoint <= MAX_TEMPERATURE) {
         setPoint = newSetPoint;
         return true;
     }
     return false;
 }
 
 void HysteresisController::setHysteresis(float newHysteresis) {
     // Ensure hysteresis is positive
     hysteresis = abs(newHysteresis);
 }
 
 float HysteresisController::getSetPoint() {
     return setPoint;
 }
 
 float HysteresisController::getHysteresis() {
     return hysteresis;
 }
 
 bool HysteresisController::getRelayState() {
     return relayState;
 }
 
 float HysteresisController::getLowerThreshold() {
     return setPoint - hysteresis;
 }
 
 float HysteresisController::getUpperThreshold() {
     return setPoint + hysteresis;
 }