#include "SerialIO.h"
#include "Relay.h"

#define RELAY_PIN 8 

Relay relay(RELAY_PIN);

void setup() {
    serialInit();
    printf("Relay Control Initialized. Type 'relay on' or 'relay off'.\n");
}

void loop() {
    char command[20];
    if (Serial.available() > 0) {
        //Serial.readBytesUntil('\n', command, sizeof(command) -1);
        fgets(command, sizeof(command), stdin); 
        command[strcspn(command, "\r\n")] = 0;

        if (strcmp(command, "relay on") == 0) {
            relay.turnOn();
            printf("Relay is ON\n");
        } 
        else if (strcmp(command, "relay off") == 0) {
            relay.turnOff();
            printf("Relay is OFF\n");
        } 
        else {
            printf("Invalid command! Use 'relay on' or 'relay off'.\n");
        }
    }
}