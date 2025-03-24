/**
 * Digital filters module implementation file
 */

 #include <Arduino.h>
 #include <string.h>
 #include "filter.h"
 
 /**
  * Salt and Pepper filter (median filter)
  * Removes impulsive noise by taking the median value from a window
  */
 float apply_salt_pepper_filter(float new_value, float *buffer, int window_size) {
   float sorted_values[window_size];
   
   // Shift values in buffer
   for (int i = 0; i < window_size - 1; i++) {
     buffer[i] = buffer[i + 1];
   }
   buffer[window_size - 1] = new_value;
   
   // Copy values to sorting array
   memcpy(sorted_values, buffer, sizeof(float) * window_size);
   
   // Perform simple bubble sort (sufficient for small arrays)
   for (int i = 0; i < window_size - 1; i++) {
     for (int j = 0; j < window_size - i - 1; j++) {
       if (sorted_values[j] > sorted_values[j + 1]) {
         float temp = sorted_values[j];
         sorted_values[j] = sorted_values[j + 1];
         sorted_values[j + 1] = temp;
       }
     }
   }
   
   // Return median value
   return sorted_values[window_size / 2];
 }
 
 /**
  * Weighted Average filter
  * Applies weighted average to smooth the signal
  */
 float apply_weighted_average_filter(float new_value, float *buffer, const float *weights, int window_size) {
   // Shift values in buffer
   for (int i = 0; i < window_size - 1; i++) {
     buffer[i] = buffer[i + 1];
   }
   buffer[window_size - 1] = new_value;
   
   // Apply weighted average
   float weighted_sum = 0.0;
   for (int i = 0; i < window_size; i++) {
     weighted_sum += buffer[i] * weights[i];
   }
   
   return weighted_sum;
 }
 
 /**
  * Apply saturation to ensure value is within valid range
  */
 float apply_saturation(float value, float min_val, float max_val) {
   if (value < min_val) {
     return min_val;
   } else if (value > max_val) {
     return max_val;
   } else {
     return value;
   }
 }