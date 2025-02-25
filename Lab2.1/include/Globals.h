#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "Config.h"

volatile bool led1State = false;
volatile int blinkCount = 5;
volatile unsigned long lastTaskTime[3];
volatile bool buttonPressed = false;
volatile bool incButtonPressed = false;
volatile bool decButtonPressed = false;

void setupPrintf();

#endif
