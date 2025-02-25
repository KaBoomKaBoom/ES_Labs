#include "Globals.h"
#include <stdio.h>

int serialPutchar(char c, FILE* stream) {
    Serial.write(c);
    return 0;
}

void setupPrintf() {
    static FILE serial_stdout;
    fdev_setup_stream(&serial_stdout, serialPutchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_stdout;
}
