#include <Keypad.h>
#include "Config.h"
#include "KeypadInput.h"

char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte rowPinsArray[ROWS] = {9, 8, 7, 6};
byte colPinsArray[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPinsArray, colPinsArray, ROWS, COLS);

void KeypadInput::init() {
    // Inițializare Keypad (nu necesită configurații suplimentare)
}


String KeypadInput::readCode() {
    String code = "";
    char key;
    while (code.length() < 4) {
        key = keypad.getKey();
        if (key) {
            code += key;
        }
    }
    return code;
}
