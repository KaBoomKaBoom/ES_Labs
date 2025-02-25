#include <Arduino.h>
#include "ButtonLED.h"
#include "BlinkingLED.h"
#include "StateVariable.h"
#include "IdleTask.h"
#include "Globals.h"

void setup() {
    Serial.begin(9600);
    setupPrintf();
  
    printf("Sequential Task System Initialized\n");

    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(LED_1_PIN, OUTPUT);
    pinMode(LED_2_PIN, OUTPUT);
    pinMode(INC_BUTTON_PIN, INPUT_PULLUP);
    pinMode(DEC_BUTTON_PIN, INPUT_PULLUP);

    unsigned long currentTime = millis();
    lastTaskTime[0] = currentTime + TASK1_OFFSET;
    lastTaskTime[1] = currentTime + TASK2_OFFSET;
    lastTaskTime[2] = currentTime + TASK3_OFFSET;

    digitalWrite(LED_1_PIN, led1State);
    digitalWrite(LED_2_PIN, LOW);
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastTaskTime[0] >= TASK1_RECURRENCE) {
        task1_ButtonLED();
        lastTaskTime[0] = currentTime;
    }
  
    if (currentTime - lastTaskTime[1] >= TASK2_RECURRENCE) {
        task2_BlinkingLED();
        lastTaskTime[1] = currentTime;
    }

    if (currentTime - lastTaskTime[2] >= TASK3_RECURRENCE) {
        task3_StateVariable();
        lastTaskTime[2] = currentTime;
    }

    idleTask_Report();
}
