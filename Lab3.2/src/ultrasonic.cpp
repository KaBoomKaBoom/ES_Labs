/**
 * Ultrasonic sensor module implementation file
 */

 #include <Arduino.h>
 #include "ultrasonic.h"
 
 /**
  * Setup function for ultrasonic sensor pins
  */
 void setup_ultrasonic_sensor(void) {
   // Configure trigger pin as output
   pinMode(TRIGGER_PIN, OUTPUT);
   digitalWrite(TRIGGER_PIN, LOW);
   
   // Configure echo pin as input
   pinMode(ECHO_PIN, INPUT);
 }
 
 /**
  * Measure distance using ultrasonic sensor
  * @return Distance in centimeters
  */
 float measure_distance(void) {
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
     return MAX_DISTANCE_CM;
   }
   
   // Calculate distance: pulse duration * speed of sound / 2
   // (divided by 2 because sound travels to object and back)
   distance = (pulse_duration * SOUND_SPEED) / 2.0;
   
   return distance;
 }