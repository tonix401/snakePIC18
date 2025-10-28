#include "Definitions.h"
#include <builtins.h>
#include <pic18f47k42.h>

#define LATCH_7SEG LATAbits.LATA0
#define CLOCK_7SEG LATAbits.LATA1
#define INPUT_7SEG LATAbits.LATA2

// Pushes a byte to the 7-segment display
void pushByte(unsigned char byte) {
    for(int i = 0; i < 8; i++) {
        CLOCK_7SEG = 0;
        INPUT_7SEG = (byte >> i) & 0x1;
        CLOCK_7SEG = 1;
    }
}

// Converts integers into the segments of a 7-segment display and pushes them to the display
void pushDigit(unsigned char digit) {
    switch (digit % 10) {
        case 0: pushByte(0b1111110); break;
        case 1: pushByte(0b1010000); break;
        case 2: pushByte(0b1101101); break;
        case 3: pushByte(0b1111001); break;
        case 4: pushByte(0b1010011); break;
        case 5: pushByte(0b0111011); break;
        case 6: pushByte(0b0111111); break;
        case 7: pushByte(0b1110000); break;
        case 8: pushByte(0b1111111); break;
        case 9: pushByte(0b1111011); break;
    }
}

// Displays a 2-digit number on the 7-segment display
void updateScoreDisplay(unsigned int number) {
    LATCH_7SEG = 0;
    pushDigit(number % 10);
    pushDigit(number / 10 % 10);
    LATCH_7SEG = 1;
}