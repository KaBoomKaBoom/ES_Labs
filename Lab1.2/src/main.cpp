#include <Arduino.h>
#include "Config.h"
#include "LedControl.h"
#include "LcdDisplay.h"
#include "KeypadInput.h"

LedControl led;
LcdDisplay lcd;
KeypadInput keypad;

void setup() {
    Serial.begin(9600);  // Initialize serial communication
    led.init();
    lcd.init();
    keypad.init();

    printf("System initialized.\n");  // Using printf() to display an initial message
}

void loop() {
    String code = keypad.readCode();  // Get code from the keypad

    // Using printf() to print the code received from the keypad
    printf("Received code: %s\n", code.c_str());  

    lcd.displayMessage("Cod: " + code);
    delay(500);

    if (code == VALID_CODE) {
        lcd.displayMessage("Cod corect!");
        led.greenOn();
        led.redOff();
        printf("Code correct. LED green turned on.\n");  // Inform about the correct code
    } else {
        lcd.displayMessage("Cod gresit!");
        led.redOn();
        led.greenOff();
        printf("Code incorrect. LED red turned on.\n");  // Inform about the incorrect code
    }
    delay(1000);
}

void getInputFromSerial() {
    char inputBuffer[10];  // Define a buffer to store input
    printf("Enter a code: ");
    
    // Wait until data is available
    while (!Serial.available()) {
        delay(100);
    }

    // Use scanf() to read a string from serial input
    scanf("%s", inputBuffer);  // Read input into the buffer
    
    printf("You entered: %s\n", inputBuffer);  // Output the received code
}
