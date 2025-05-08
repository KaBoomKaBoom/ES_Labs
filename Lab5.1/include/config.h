/**
 * config.h
 * Configuration parameters for ON-OFF temperature control system with hysteresis
 */

 #ifndef CONFIG_H
 #define CONFIG_H
 
 // DHT Sensor Configuration
 #define DHT_PIN 2           // Digital pin connected to DHT sensor
 #define DHT_TYPE DHT11      // DHT sensor type (DHT11, DHT22, etc.)
 #define TEMPERATURE_READ_INTERVAL 2000  // Read temperature every 2 seconds
 
 // Relay Configuration
 #define RELAY_PIN 4         // Digital pin connected to relay
 
 // Hysteresis Configuration
 #define DEFAULT_SETPOINT 25.0           // Default temperature setpoint (°C)
 #define DEFAULT_HYSTERESIS 2.0          // Default hysteresis value (±°C)
 #define MIN_TEMPERATURE 10.0            // Minimum allowed temperature setpoint
 #define MAX_TEMPERATURE 40.0            // Maximum allowed temperature setpoint
 
 // Serial Communication
 #define SERIAL_BAUD_RATE 9600           // Serial communication baud rate
 #define SERIAL_PRINT_INTERVAL 4000      // Update serial output every 1 second
 
 // Alert Configuration (Bonus Feature)
 #define ALERT_THRESHOLD 5.0             // Temperature deviation threshold for alert (°C)
 #define ALERT_INTERVAL 5000             // Minimum time between alerts (ms)
 
 #endif // CONFIG_H