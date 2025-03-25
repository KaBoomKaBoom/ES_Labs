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
   // Variables to store pulse timing
   unsigned long pulse_start, pulse_end;
   float pulse_duration, distance;
   
   // Clear trigger pin
   digitalWrite(TRIGGER_PIN, LOW);
   delayMicroseconds(2);
   
   // Send a 10µs pulse to trigger
   digitalWrite(TRIGGER_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIGGER_PIN, LOW);
   
   // Measure the length of echo pulse
   pulse_duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout after 30ms
   
   // If timeout occurred, return max distance
   if (pulse_duration == 0) {
     return MAX_DISTANCE;
   }
   
   // Calculate distance: pulse duration * speed of sound / 2
   // (divided by 2 because sound travels to object and back)
   distance = (pulse_duration * 0.034) / 2.0;
   
   return distance;
 }