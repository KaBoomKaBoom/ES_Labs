#ifndef SERIAL_STDIO_H
#define SERIAL_STDIO_H

void initializeStdio(unsigned long baudRate);
int serialScanf(const char* format, ...);
void processSerialInput(void (*commandCallback)(const char* command));
void serialPrint(const char* message);
void serialPrintln(const char* message);
char* serialReadLine();

#endif