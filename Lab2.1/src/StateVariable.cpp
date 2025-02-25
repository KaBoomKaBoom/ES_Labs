#include "StateVariable.h"
#include "Globals.h"

void task3_StateVariable() {
    bool incButtonState = digitalRead(INC_BUTTON_PIN) == LOW;
    bool decButtonState = digitalRead(DEC_BUTTON_PIN) == LOW;

    if (incButtonState && !incButtonPressed) {
        if (blinkCount < 20) {
            blinkCount++;
            printf("Blink count increased to: %d\n", blinkCount);
        }
        incButtonPressed = true;
    } else if (!incButtonState && incButtonPressed) {
        incButtonPressed = false;
    }

    if (decButtonState && !decButtonPressed) {
        if (blinkCount > 1) {
            blinkCount--;
            printf("Blink count decreased to: %d\n", blinkCount);
        }
        decButtonPressed = true;
    } else if (!decButtonState && decButtonPressed) {
        decButtonPressed = false;
    }
}
