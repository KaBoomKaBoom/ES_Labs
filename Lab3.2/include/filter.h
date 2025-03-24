/**
 * Digital filters module header file
 */

 #ifndef FILTER_H
 #define FILTER_H
 
 // Function prototypes
 float apply_salt_pepper_filter(float new_value, float *buffer, int window_size);
 float apply_weighted_average_filter(float new_value, float *buffer, const float *weights, int window_size);
 float apply_saturation(float value, float min_val, float max_val);
 
 #endif /* FILTER_H */