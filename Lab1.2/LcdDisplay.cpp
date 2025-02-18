#include <LiquidCrystal.h>
#include "Config.h"
#include "LcdDisplay.h"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void LcdDisplay::init() {
    lcd.begin(16, 2);
    lcd.clear();
}

void LcdDisplay::displayMessage(String message) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
}
