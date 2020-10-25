#include <KeyPadMatrix.h>

#define PIN_KEYBOARD_C0         2 // D4 on WEMOS D1 Mini
#define PIN_KEYBOARD_C1         0 // D3 on WEMOS D1 Mini
#define PIN_KEYBOARD_C2         4 // D2 on WEMOS D1 Mini
#define PIN_KEYBOARD_C3         5 // D1 WEMOS D1 Mini

// Setup for 4 x 4 Matrix (16 keys)
KeyPadMatrix keyPadMatrix = KeyPadMatrix(PIN_KEYBOARD_C0, PIN_KEYBOARD_C1, PIN_KEYBOARD_C2, PIN_KEYBOARD_C3);

// Setup for 3 x 3 Matrix (9 keys)
// KeyPadMatrix keyPadMatrix = KeyPadMatrix(PIN_KEYBOARD_C0, PIN_KEYBOARD_C1, PIN_KEYBOARD_C2);

void setup()
{
    Serial.begin(76800);

    // set long key press timeout (default 1000)
    keyPadMatrix.setLongKeyPressTimeout(3000);
}

void loop() {
    keyPadMatrix.scan();

    // Process keypad key press
    if (keyPadMatrix.hasEvent()) {

        String txtAction = "";
        switch (keyPadMatrix.getAction()) {
            case keyPadMatrix.keyAction::pressed:     txtAction = "press     "; break;
            case keyPadMatrix.keyAction::pressedLong: txtAction = "press long"; break;
            case keyPadMatrix.keyAction::released:    txtAction = "release   "; break;
        }

        switch (keyPadMatrix.getAction()) {
            case keyPadMatrix.keyAction::pressed:     txtAction = "press     "; break;
            case keyPadMatrix.keyAction::pressedLong: txtAction = "press long"; break;
            case keyPadMatrix.keyAction::released:    txtAction = "release   "; break;
        }

        Serial.print ("Action: ");
        Serial.print (txtAction);
        Serial.print ("   Key code: ");
        Serial.print (keyPadMatrix.getKeycode());
        Serial.println ();
    }
}
