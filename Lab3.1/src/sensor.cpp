/*
 * sensor.cpp
 * 
 * Implementation file for ultrasonic sensor functionality
 */

 #include "sensor.h"
 #include <NewPing.h>
 
 // Global objects
 static NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
 void sensor_init() {
   // HC-SR04 requires no special initialization
   // Pins are configured by the NewPing library
 }
 
 float sensor_read_distance() {
   // Measure distance
   float distance = sonar.ping_cm();
   
   // If distance is 0, sensor might be out of range or there's an error
   if (distance == 0) {
     distance = MAX_DISTANCE; // Set to max distance if no echo received
   }
   
   return distance;
 }