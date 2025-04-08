#include "command_processor.h"
#include "motor_control.h"
#include <string.h>

char inputBuffer[64];

void processCommand(const char* commandStr) {
  char command[32];
  char subCommand[32] = "";
  int value = 0;
  
  // Parse the command using sscanf
  if (sscanf(commandStr, "%s %s %d", command, subCommand, &value) >= 1) {
    printf("> %s", command);
    if (strlen(subCommand) > 0) printf(" %s", subCommand);
    if (value != 0 || strcmp(subCommand, "set") == 0) printf(" %d", value);
    printf("\n");
    
    if (strcmp(command, "motor") == 0) {
      if (strcmp(subCommand, "set") == 0) {
        setMotorPower(value);
      } 
      else if (strcmp(subCommand, "stop") == 0) {
        setMotorPower(0);
      } 
      else if (strcmp(subCommand, "max") == 0) {
        // Set to max power in current direction
        int currentPower = getCurrentPower();
        if (currentPower >= 0) {
          setMotorPower(100);
        } else {
          setMotorPower(-100);
        }
      } 
      else if (strcmp(subCommand, "inc") == 0) {
        int currentPower = getCurrentPower();
        setMotorPower(currentPower + 10);
      } 
      else if (strcmp(subCommand, "dec") == 0) {
        int currentPower = getCurrentPower();
        setMotorPower(currentPower - 10);
      }
      else {
        printf("Unknown sub-command\n");
      }
    }
    else {
      printf("Unknown command\n");
    }
  }
  else {
    printf("Invalid command format\n");
  }
}

// Read a line from Serial using stdio functions
void readLine() {
  int i = 0;
  char c;
  
  printf("Enter command: ");
  
  // Clear the buffer
  memset(inputBuffer, 0, sizeof(inputBuffer));
  
  // Read until newline or buffer is full
  while (i < sizeof(inputBuffer) - 1) {
    c = getchar();
    
    // Echo the character back
    putchar(c);
    
    if (c == '\n' || c == '\r') {
      break;
    }
    
    inputBuffer[i++] = c;
  }
  
  inputBuffer[i] = '\0';  // Null terminate the string
  
  if (strlen(inputBuffer) > 0) {
    processCommand(inputBuffer);
  }
}

void printCommandHelp() {
  printf("Motor Control Ready\n");
  printf("Available commands:\n");
  printf("  motor set [-100..100] - Set power and direction\n");
  printf("  motor stop - Stop the motor\n");
  printf("  motor max - Set to max power in current direction\n");
  printf("  motor inc - Increase power by 10%%\n");
  printf("  motor dec - Decrease power by 10%%\n");
} 