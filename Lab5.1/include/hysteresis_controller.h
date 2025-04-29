/**
 * hysteresis_controller.h
 * Module for ON-OFF control with hysteresis
 */

 #ifndef HYSTERESIS_CONTROLLER_H
 #define HYSTERESIS_CONTROLLER_H
 
 #include <Arduino.h>
 #include "config.h"
 
 class HysteresisController {
 private:
     float setPoint;         // Temperature setpoint
     float hysteresis;       // Hysteresis value
     bool relayState;        // Current relay state
     
 public:
     /**
      * Constructor with default values
      */
     HysteresisController();
     
     /**
      * Initialize the controller and relay pin
      */
     void begin();
     
     /**
      * Update the control logic based on current temperature
      * @param currentTemperature The current temperature reading
      * @return true if relay state changed, false otherwise
      */
     bool update(float currentTemperature);
     
     /**
      * Set a new temperature setpoint
      * @param newSetPoint New setpoint value
      * @return true if setpoint was changed, false if out of range
      */
     bool setSetPoint(float newSetPoint);
     
     /**
      * Set a new hysteresis value
      * @param newHysteresis New hysteresis value
      */
     void setHysteresis(float newHysteresis);
     
     /**
      * Get the current setpoint
      * @return setpoint value
      */
     float getSetPoint();
     
     /**
      * Get the current hysteresis value
      * @return hysteresis value
      */
     float getHysteresis();
     
     /**
      * Get the current relay state
      * @return true if relay is ON, false if OFF
      */
     bool getRelayState();
     
     /**
      * Get the lower threshold (setpoint - hysteresis)
      * @return lower threshold value
      */
     float getLowerThreshold();
     
     /**
      * Get the upper threshold (setpoint + hysteresis)
      * @return upper threshold value
      */
     float getUpperThreshold();
 };
 
 #endif // HYSTERESIS_CONTROLLER_H