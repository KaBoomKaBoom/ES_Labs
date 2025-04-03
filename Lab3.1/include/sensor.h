/*
 * sensor.h
 * 
 * Header file for ultrasonic sensor functionality
 */

 #ifndef SENSOR_H
 #define SENSOR_H
 
 #include <Arduino.h>
 
 // Pin definitions for HC-SR04 ultrasonic sensor
 #define TRIGGER_PIN 9
 #define ECHO_PIN 8
 #define MAX_DISTANCE 400 // Maximum distance to measure (in cm)
 
 /**
  * Initialize the ultrasonic sensor
  */
 void sensor_init();
 
 /**
  * Read distance from ultrasonic sensor
  * 
  * @return measured distance in cm, or MAX_DISTANCE if no echo received
  */
 float sensor_read_distance();
 
 #endif // SENSOR_H