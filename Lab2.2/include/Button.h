#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
    Button(uint8_t pin);
    bool isPressed();

private:
    uint8_t pin;
};

#endif
    