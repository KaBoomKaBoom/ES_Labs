#include "IdleTask.h"
#include "Globals.h"

void idleTask_Report() {
    static unsigned long lastReportTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastReportTime >= IDLE_REPORT_INTERVAL) {
        printf("--- System Status Report ---\n");
        printf("Task 1 LED State: %s\n", led1State ? "ON" : "OFF");
        printf("Task 2 Blink Status: %s\n", led1State ? "INACTIVE" : "ACTIVE");
        printf("Task 3 Blink Count: %d\n", blinkCount);
        printf("---------------------------\n");

        lastReportTime = currentTime;
    }
}
