#include <KeypadMatrix.h>

#define PIN_KEYBOARD_C0         2 // D4 on WEMOS D1 Mini
#define PIN_KEYBOARD_C1         0 // D3 on WEMOS D1 Mini
#define PIN_KEYBOARD_C2         4 // D2 on WEMOS D1 Mini
#define PIN_KEYBOARD_C3         5 // D1 WEMOS D1 Mini

// Setup for 4 x 4 Matrix (16 keys)
KeypadMatrix KeypadMatrix = KeypadMatrix(PIN_KEYBOARD_C0, PIN_KEYBOARD_C1, PIN_KEYBOARD_C2, PIN_KEYBOARD_C3);

// Setup for 3 x 3 Matrix (9 keys)
// KeypadMatrix KeypadMatrix = KeypadMatrix(PIN_KEYBOARD_C0, PIN_KEYBOARD_C1, PIN_KEYBOARD_C2);

void setup()
{
    Serial.begin(76800);

    // set long key press timeout (default 1000)
    KeypadMatrix.setLongKeyPressTimeout(3000);
}

void loop() {
    KeypadMatrix.scan();

    // Process keypad key press
    if (KeypadMatrix.hasEvent()) {

        String txtAction = "";
        switch (KeypadMatrix.getAction()) {
            case KeypadMatrix.keyAction::pressed:     txtAction = "press     "; break;
            case KeypadMatrix.keyAction::pressedLong: txtAction = "press long"; break;
            case KeypadMatrix.keyAction::released:    txtAction = "release   "; break;
        }

        Serial.print ("Action: ");
        Serial.print (txtAction);
        Serial.print ("   Key code: ");
        Serial.print (KeypadMatrix.getKeycode());
        Serial.println ();
    }
}
