/**
 * Ultrasonic sensor module header file
 */

 #ifndef ULTRASONIC_H
 #define ULTRASONIC_H
 
 // Pin definitions
 #define TRIGGER_PIN         12
 #define ECHO_PIN            13
 
 // Ultrasonic sensor parameters
 #define MAX_DISTANCE_CM     400     // Maximum valid distance in cm
 #define MIN_DISTANCE_CM     2       // Minimum valid distance in cm
 #define SOUND_SPEED         0.034   // Sound speed in cm/microsecond
 
 // Function prototypes
 void setup_ultrasonic_sensor(void);
 float measure_distance(void);
 
 #endif /* ULTRASONIC_H */