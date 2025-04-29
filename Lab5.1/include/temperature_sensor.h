/**
 * temperature_sensor.h
 * Module for temperature sensor interface
 */

 #ifndef TEMPERATURE_SENSOR_H
 #define TEMPERATURE_SENSOR_H
 
 #include <Arduino.h>
 #include "config.h"
 
 class TemperatureSensor {
 private:
     unsigned long lastReadTime;     // Time of last sensor reading
     float currentTemperature;       // Current temperature reading
     bool sensorInitialized;         // Flag to check if sensor is initialized
 
 public:
     /**
      * Constructor
      */
     TemperatureSensor();
     
     /**
      * Initialize the temperature sensor
      * @return true if initialization successful, false otherwise
      */
     bool begin();
     
     /**
      * Update temperature reading if read interval has passed
      * @return true if reading updated, false otherwise
      */
     bool update();
     
     /**
      * Get the current temperature
      * @return current temperature in Celsius
      */
     float getTemperature();
     
     /**
      * Check if sensor is working properly
      * @return true if sensor is working, false otherwise
      */
     bool isOperational();
 };
 
 #endif // TEMPERATURE_SENSOR_H