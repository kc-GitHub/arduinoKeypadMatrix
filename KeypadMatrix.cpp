/**
 * Description ...
 */

// include this library's description file
#include "KeypadMatrix.h"

/***********************************************************************************************************************
 */
KeypadMatrix::KeypadMatrix(uint8 row0, uint8 row1, uint8 row2, uint8 row3) {
    pinMap[0] = row0;
    pinMap[1] = row1;
    pinMap[2] = row2;
    pinMap[3] = row3;
}

KeypadMatrix::KeypadMatrix(uint8 row0, uint8 row1, uint8 row2) {
    pinMap[0] = row0;
    pinMap[1] = row1;
    pinMap[2] = row2;
    rowCountMax = 3;
}

/***********************************************************************************************************************
 */

void KeypadMatrix::scan(void) {
    uint8_t keyCodeLast = 0;

    // Configure scan row pins
    for (uint8_t i = 0; i < rowCountMax; i++) {
        if (i != scanRow || scanRow == rowCountMax) {
            // Set row as input
            pinMode(pinMap[i], INPUT_PULLUP);
        } else {
            // Set row as output an low
            pinMode(pinMap[i], OUTPUT);
            digitalWrite(pinMap[i], LOW);
        }
    }

	// Read all row pins
	uint8_t keyByte = !digitalRead(pinMap[0]) << 0 | !digitalRead(pinMap[1]) << 1 | !digitalRead(pinMap[2]) << 2 | !digitalRead(pinMap[3]) << 3;

	// Mask out read row
	keyByte &= ~(1 << scanRow);

	// Calculate the key code
	uint8_t keycode = (keyByte * (1 << (scanRow))) + scanRow;

    if (keyByte > 0 && scanRow == rowCountMax) {
        keyCodeLast = keycode;
    } else if (keyByte > 0 && keyCodeSaved == 0) {
        keyCodeSaved = keycode;
    }

    scanRow ++;

    if (scanRow > rowCountMax) {
        scanRow = 0;

        if (keyCodeSaved || keyCodeLast) {
            keyCode = keyCodeLast ? keyCodeLast : keyCodeSaved;
            keyCodeSaved = 0;
            keyCodeLast = 0;
        } else {
            keyCode = 0;
        }

        if (keyCodeOld != keyCode && keyHasEvent == 0) {
            if (keyCodeOld == 0 && keyCode > 0) {
                action = keyAction::pressed;
            } else if (keyCode == 0 && keyCodeOld > 0) {
                action = keyAction::released;
            } else {
                action = keyAction::none;
            }

            if (action > 0) {
                keyCodeReleased = (action == keyAction::released) ? keyCodeOld : 0;
                keyHasEvent = 1;
                keyCodeOld = keyCode;
                keyCodeMillis = millis();
            }
        } else if (keyCode != 0 && keyCodeOld == keyCode && keyHasEvent == 0 && action != keyAction::pressedLong && (millis() - keyCodeMillis) > longTimeout) {
            action = keyAction::pressedLong;
            keyHasEvent = 1;
        }
    }
}

void KeypadMatrix::setLongKeyPressTimeout(uint16_t timeoutMs) {
    longTimeout = timeoutMs;
}

uint8 KeypadMatrix::hasEvent (void) {
    return keyHasEvent;
}

uint8 KeypadMatrix::getAction (void) {
    return action;
}

uint8 KeypadMatrix::getKeycode() {
    uint8 keycode = (action == keyAction::released) ? keyCodeReleased : keyCode;
    keyHasEvent = 0;
    return keycode;
}
