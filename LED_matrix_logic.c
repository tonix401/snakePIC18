#include "Definitions.h"
#include <builtins.h>
#include "globals.h"
#include <pic18f47k42.h>

#define DIN_MATRIX LATCbits.LATC0
#define CS_MATRIX LATCbits.LATC1
#define CLOCK_MATRIX LATCbits.LATC2
#define VCC_MATRIX LATCbits.LATC3

unsigned int frame[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void imprintLossScreen() {
    unsigned int lossScreen[8] = {
        0b10000001,
        0b01000010,
        0b00100100,
        0b00011000,
        0b00011000,
        0b00100100,
        0b01000010,
        0b10000001
    };
    for (int i = 7; i >= 0; i--) {
        frame[i] = lossScreen[i];
    }
}

// Displays the current frame on the LED matrix
void applyPositionsToFrame() {
    // add snake
    for (int i = 0; i < 64; i++) {
        int y = (snake_body[i] & 0xF0) >> 4;
        int x = (snake_body[i] & 0x0F);
        frame[y] += (0x01 << x);
    }
    
    // add apple
    int y = (apple_position & 0xF0) >> 4;
    int x = (apple_position & 0x0F);
    frame[y] += (0x01 << x);
}

void clearFrame() {
    for (unsigned int i = 0; i < sizeof(frame); i++) {
        frame[i] = 0;
    }
}

void pushFrame() {
    for (int i = 0; i < sizeof(frame); i++) {
        for (int j = 0; j < 8; j++) {
            if (i & (0x80 >> j)) {
                DIN_MATRIX = 1;
            } else {
                DIN_MATRIX = 0;
            }
            CLOCK_MATRIX = 1;
            CLOCK_MATRIX = 0;
        }
        
        for (int j = 0; j < 8; j++) {
            if (frame[i] & (0x80 >> j)) {
                DIN_MATRIX = 1;
            } else {
                DIN_MATRIX = 0;
            }
            CLOCK_MATRIX = 1;
            CLOCK_MATRIX = 0;
        }
    }
}