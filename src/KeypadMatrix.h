#ifndef KEYPAD_MATRIX_H
#define KEYPAD_MATRIX_H

#include <Arduino.h>

class KeypadMatrix {
    public:
        enum keyAction {
            none = 0,
            pressed,
            pressedLong,
            released
        };

        /* Constructor */
        KeypadMatrix(uint8 row0, uint8 row1, uint8 row2, uint8 row3);
        KeypadMatrix(uint8 row0, uint8 row1, uint8 row2);

        void scan();
        void setLongKeyPressTimeout(uint16_t timeoutMs);

        uint8_t hasEvent(void);
        uint8_t getKeycode(void);
        KeypadMatrix::keyAction getAction(void);

    private:
        uint8_t rowCountMax = 4;
        uint8_t pinMap[4];
        uint8_t scanRow = 0;		// counter for current scan row
        uint8_t setupDone = 0;

        uint8_t keyCode = 0;
        uint8_t keyCodeReleased = 0;
        uint8_t keyCodeOld = 0;
        uint8_t keyCodeSaved = 0;

        uint32_t keyCodeMillis = 0;
        uint8_t keyHasEvent = 0;
        keyAction action = keyAction::none;
        uint8_t keyCode2 = 0;
        uint16_t longTimeout = 1000;
    };

#endif
