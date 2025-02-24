#include <Arduino.h>
#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

class LcdDisplay {
public:
    void init();
    void displayMessage(String message);
};

#endif
