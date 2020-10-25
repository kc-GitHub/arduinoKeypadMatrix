/**
 * Description ...
 */

// include this library's description file
#include "KeyPadMatrix.h"

/***********************************************************************************************************************
 */
KeyPadMatrix::KeyPadMatrix(uint8 row0, uint8 row1, uint8 row2, uint8 row3) {
    pinMap[0] = row0;
    pinMap[1] = row1;
    pinMap[2] = row2;
    pinMap[3] = row3;
}

KeyPadMatrix::KeyPadMatrix(uint8 row0, uint8 row1, uint8 row2) {
    pinMap[0] = row0;
    pinMap[1] = row1;
    pinMap[2] = row2;
    rowCountMax = 3;
}

/***********************************************************************************************************************
 */

void KeyPadMatrix::scan(void) {
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
                mode = keyModePressed;
            } else if (keyCode == 0 && keyCodeOld > 0) {
                mode = keyModeReleased;
            } else {
                mode = keyModeNone;
            }

            if (mode > 0) {
                keyCodeReleased = (mode == keyModeReleased) ? keyCodeOld : 0;
                keyHasEvent = 1;
                keyCodeOld = keyCode;
                keyCodeLastMillis = millis();
            }
        } else if (keyCode != 0 && keyCodeOld == keyCode && keyHasEvent == 0 && mode != keyModePressedLong && (millis() - keyCodeLastMillis) > keyPressLongTimeout) {
            mode = keyModePressedLong;
            keyHasEvent = 1;
        }
    }
}

void KeyPadMatrix::setKeypressLongTimeout(uint16_t ms) {
    keyPressLongTimeout = ms;
}

uint8 KeyPadMatrix::hasEvent (void) {
    return keyHasEvent;
}

uint8 KeyPadMatrix::getMode (void) {
    return mode;
}

uint8 KeyPadMatrix::getKeycode() {
    uint8 keycode = (mode == keyModeReleased) ? keyCodeReleased : keyCode;
    keyHasEvent = 0;
    return keycode;
}
