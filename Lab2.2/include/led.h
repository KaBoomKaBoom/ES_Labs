// led.h (unchanged)
#ifndef LED_H
#define LED_H

void initializeLed(int pin);
void turnOnLed(int pin);
void turnOffLed(int pin);
bool getLedState();

#endif