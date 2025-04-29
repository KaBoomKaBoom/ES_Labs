#include <Arduino.h>
#include <stdio.h>
#include "relay.h"

FILE relay_scan;
FILE relay_print;

char command[32];

int stdio_getinput(FILE *stream) {
    while (!Serial.available());
    return Serial.read();
  }

int stdio_print(char c, FILE *stream) {
    Serial.write(c);
    return 0;
}

void lab_4_1_setup() {
    Serial.begin(115200);
    relay_init();
    toggle_relay(false);
    FILE *fpSerial = fdevopen(stdio_print, stdio_getinput);
  
    stdin = fpSerial;
    stdout = fpSerial;
    printf("Available commands: relay on | relay off\n");
}

void lab_4_1_loop() {
    if (Serial.available()) {
        if (scanf("%31s", command) > 0) {
            // Procesarea comenzii
            if (strcmp(command, "relay") == 0) {
              char action[5];
              if (scanf("%4s", action) > 0) {
                if (strcmp(action, "on") == 0) {
                  toggle_relay(true);
                  printf("Relay on\n");
                } else if (strcmp(action, "off") == 0) {
                  toggle_relay(false);
                  printf("Relay off\n");
                } 
                else {
                    printf("Invalid command. Use 'relay on' or ' relay off'\n");
                }
              }
              else {
                printf("Invalid command. Use 'relay on' or ' relay off'\n");
              }
            }
        }
    }
}
