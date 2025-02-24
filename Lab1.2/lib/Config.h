#include <stdint.h>  // Include this to use uint8_t
#ifndef CONFIG_H
#define CONFIG_H

#define VALID_CODE "1234"    // Codul valid pentru deblocare

// Pini Keypad
#define ROWS 4
#define COLS 4
const uint8_t rowPins[ROWS] = {9, 8, 7, 6};    // Pini pentru rânduri
const uint8_t colPins[COLS] = {5, 4, 3, 2};    // Pini pentru coloane

// Pini LCD
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 10
#define LCD_D5 9
#define LCD_D6 8
#define LCD_D7 7

// Pini LED-uri
#define GREEN_LED A0
#define RED_LED A1

#endif
