/**
 * temperature_sensor.cpp
 * Implementation of temperature sensor interface
 */

 #include "temperature_sensor.h"
 #include <DHT.h>
 
 // Create DHT sensor instance
 DHT dht(DHT_PIN, DHT_TYPE);
 
 TemperatureSensor::TemperatureSensor() {
     lastReadTime = 0;
     currentTemperature = 0.0;
     sensorInitialized = false;
 }
 
 bool TemperatureSensor::begin() {
     dht.begin();
     delay(2000);  // DHT sensors need 2 seconds to stabilize
     
     // Test if sensor is responding
     float testReading = dht.readTemperature();
     if (isnan(testReading)) {
         sensorInitialized = false;
         return false;
     }
     
     currentTemperature = testReading;
     sensorInitialized = true;
     return true;
 }
 
 bool TemperatureSensor::update() {
     unsigned long currentTime = millis();
     
     // Check if it's time to read the sensor
     if (currentTime - lastReadTime >= TEMPERATURE_READ_INTERVAL) {
         lastReadTime = currentTime;
         
         float reading = dht.readTemperature();
         if (!isnan(reading)) {
             currentTemperature = reading;
             return true;
         }
     }
     
     return false;
 }
 
 float TemperatureSensor::getTemperature() {
     return currentTemperature;
 }
 
 bool TemperatureSensor::isOperational() {
     return sensorInitialized && !isnan(dht.readTemperature());
 }