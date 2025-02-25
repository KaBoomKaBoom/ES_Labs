#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions
const int BUTTON_1_PIN = 2;
const int LED_1_PIN = 11;
const int LED_2_PIN = 12;
const int INC_BUTTON_PIN = 3;
const int DEC_BUTTON_PIN = 4;

// Task recurrence times
const unsigned long TASK1_RECURRENCE = 50;
const unsigned long TASK2_RECURRENCE = 100;
const unsigned long TASK3_RECURRENCE = 100;
const unsigned long IDLE_REPORT_INTERVAL = 1000;

// Task offsets
const unsigned long TASK1_OFFSET = 0;
const unsigned long TASK2_OFFSET = 20;
const unsigned long TASK3_OFFSET = 40;

#endif
