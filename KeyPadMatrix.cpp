/**
 * Description ...
 */

// include this library's description file
#include "KeyPadMatrix.h"

/***********************************************************************************************************************
 */
KeyPadMatrix::KeyPadMatrix(uint8 row0, uint8 row1, uint8 row2, uint8 row3) {
	this->pinMap[0] = row0;
	this->pinMap[1] = row1;
	this->pinMap[2] = row2;
	this->pinMap[3] = row3;
}

/***********************************************************************************************************************
 */

void KeyPadMatrix::scanKeyPad(void) {
	uint8_t keyCodeLast = 0;

	// Configure scan row pins
	for (uint8_t i = 0; i < 4; i++) {
		if (i != scanCount || scanCount == 4) {
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
	keyByte &= ~(1 << scanCount);
	// Calculate the key code

	uint8_t keycode = (keyByte * (1 << (scanCount))) + scanCount;

	if (keyByte > 0 && scanCount == 4) {
		keyCodeLast = keycode;
	} else if (keyByte > 0 && keyCodeTmp == 0) {
		keyCodeTmp = keycode;
	}

	scanCount ++;

	if (scanCount > 4) {
		scanCount = 0;

		if (keyCodeTmp || keyCodeLast) {
			this->keyCode = keyCodeLast ? keyCodeLast : keyCodeTmp;
			keyCodeTmp = 0;
			keyCodeLast = 0;
		} else {
			this->keyCode = 0;
		}

		if (keyCodeOld != this->keyCode && keyCodeChanged == 0) {
			if (keyCodeOld == 0 && this->keyCode > 0) {
				mode = KEYPADMATRIX_MODE_PRESSED;
			} else if (this->keyCode == 0 && keyCodeOld > 0) {
				mode = KEYPADMATRIX_MODE_RELEASED;
			} else {
				mode = KEYPADMATRIX_MODE_NONE;
			}

			if (mode) {
				keyCodeChanged = 1;
				keyCodeOld = this->keyCode;
			}
		}
	}
}

uint8 KeyPadMatrix::keyCodeHasChanged (void) {
	return keyCodeChanged;
}

uint8 KeyPadMatrix::getMode (void) {
	return mode;
}

uint8 KeyPadMatrix::getKeycode() {
	uint8 keycode = this->keyCode;
	keyCodeChanged = 0;
	return keycode;
}
