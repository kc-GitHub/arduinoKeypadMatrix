/**
 **********************************************************************************************************************
 * @file  KeyPadMatrix.h
 * @brief ...
 ***********************************************************************************************************************
 */

#ifndef KEY_PAD_MATRIX_K
#define KEY_PAD_MATRIX_K

#include <Arduino.h>

#define KEYPADMATRIX_MODE_NONE        0
#define KEYPADMATRIX_MODE_PRESSED     1
#define KEYPADMATRIX_MODE_RELEASED    2

class KeyPadMatrix {
    public:
        /* Constructor */
        KeyPadMatrix(uint8 row0, uint8 row1, uint8 row2, uint8 row3);
        KeyPadMatrix(uint8 row0, uint8 row1, uint8 row2);

        void scan();
        uint8 keyCodeHasChanged(void);
        uint8 getKeycode(void);
        uint8 getMode(void);

    private:
        uint8_t rowCountMax = 4;
        uint8_t pinMap[4];
        uint8_t scanRow = 0;		// counter for current scan row
        uint8_t setupDone = 0;

        uint8_t keyCode = 0;
        uint8_t keyCodeOld = 255;
        uint8_t keyCodeSaved = 0;

        uint8_t keyCodeChanged = 0;
        uint8_t mode = 0;
        uint8_t keyCode2 = 0;
    };

#endif
