#include "BlinkingLED.h"
#include "Globals.h"

void task2_BlinkingLED() {
    static bool led2State = false;
    static int currentBlink = 0;

    if (!led1State) {
        led2State = !led2State;
        digitalWrite(LED_2_PIN, led2State ? HIGH : LOW);

        if (led2State) {
            currentBlink++;
            if (currentBlink >= blinkCount) {
                currentBlink = 0;
            }
        }
    } else {
        digitalWrite(LED_2_PIN, LOW);
        currentBlink = 0;
    }
}
