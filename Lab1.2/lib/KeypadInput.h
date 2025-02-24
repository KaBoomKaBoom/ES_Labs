#include <Arduino.h>
#ifndef KEYPAD_INPUT_H
#define KEYPAD_INPUT_H

class KeypadInput {
public:
    void init();
    String readCode();
};

#endif
