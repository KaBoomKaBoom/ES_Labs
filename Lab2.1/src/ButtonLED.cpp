#include "ButtonLED.h"
#include "Globals.h"

void task1_ButtonLED() {
    int buttonReading = digitalRead(BUTTON_1_PIN);

    if (buttonReading == LOW) {
        if (!buttonPressed) {
            led1State = !led1State;
            digitalWrite(LED_1_PIN, led1State ? HIGH : LOW);
            printf("Button pressed! LED1 is now: %s\n", led1State ? "ON" : "OFF");
            buttonPressed = true;
        }
    } else {
        buttonPressed = false;
    }
}
