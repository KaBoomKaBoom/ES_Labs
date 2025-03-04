/**
 * Arduino FreeRTOS Project - Button Utilities Implementation
 */

 #include "button_utils.h"

 /* Function to read button state with debouncing */
 bool read_button(uint8_t pin) {
   static uint32_t last_debounce_time[3] = {0, 0, 0};
   static bool last_button_state[3] = {false, false, false};
   const uint16_t debounce_delay = 50;
   
   int button_index;
   
   if (pin == BUTTON1_PIN) {
     button_index = 0;
   } else if (pin == BUTTON2_PIN) {
     button_index = 1;
   } else if (pin == BUTTON3_PIN) {
     button_index = 2;
   } else {
     return false;
   }
   
   bool current_reading = digitalRead(pin) == LOW;  // Assuming active LOW (pull-up)
   
   if (current_reading != last_button_state[button_index]) {
     last_debounce_time[button_index] = millis();
   }
   
   if ((millis() - last_debounce_time[button_index]) > debounce_delay) {
     last_button_state[button_index] = current_reading;
     return current_reading;
   }
   
   return false;
 }