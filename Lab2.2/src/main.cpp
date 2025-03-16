#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "TaskManager.h"
#include "SerialIO.h"

void setup() {
    serialInit();
    initTaskManager();
    vTaskStartScheduler();

}

void loop() {
}