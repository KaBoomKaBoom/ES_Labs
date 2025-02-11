#include "buttonControl.h"
#include "ledControl.h"

void setup() {
  pinMode(LED_PIN, OUTPUT);    // Set the LED pin as output
  pinMode(BUTTON_PIN, INPUT);  // Set the button pin as input
}

void loop() {
  int buttonState = readButton();  // Read the button state

  if (buttonState == HIGH) {  // Button is pressed
    toggleLed();              // Toggle the LED
    delay(200);               // Debounce delay
  }
}
