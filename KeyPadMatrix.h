/**
 **********************************************************************************************************************
 * @file  KeyPadMatrix.h
 * @brief ...
 ***********************************************************************************************************************
 */

#ifndef KEY_PAD_MATRIX_H
#define KEY_PAD_MATRIX_H

#include <Arduino.h>

class KeyPadMatrix {
    public:
        /* Constructor */
        KeyPadMatrix(uint8 row0, uint8 row1, uint8 row2, uint8 row3);
        KeyPadMatrix(uint8 row0, uint8 row1, uint8 row2);

        void scan();
        void setKeypressLongTimeout(uint16_t ms);

        uint8 hasEvent(void);
        uint8 getKeycode(void);
        uint8 getMode(void);

        enum keyMode {
            keyModeNone = 0,
            keyModePressed,
            keyModePressedLong,
            keyModeReleased
        };

    private:
        uint8_t rowCountMax = 4;
        uint8_t pinMap[4];
        uint8_t scanRow = 0;		// counter for current scan row
        uint8_t setupDone = 0;

        uint8_t keyCode = 0;
        uint8_t keyCodeReleased = 0;
        uint8_t keyCodeOld = 0;
        uint8_t keyCodeSaved = 0;

        uint32_t keyCodeLastMillis = 0;
        uint8_t keyHasEvent = 0;
        keyMode mode = keyModeNone;
        uint8_t keyCode2 = 0;
        uint16_t keyPressLongTimeout = 1000;
    };

#endif
