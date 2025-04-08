#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <Arduino.h>
#include <stdio.h>

// Process received command
void processCommand(const char* command);

// Handle reading a line from Serial
void readLine();

// Print available commands help
void printCommandHelp();

#endif // COMMAND_PROCESSOR_H 