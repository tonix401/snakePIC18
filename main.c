/*
 * File:   Main.c
 * Author: Richard Leytes, Tom Weise
 * Device: PIC18F47K42
 * Created on October 14, 2025, 4:27 PM
 */
#include "Definitions.h"
#include <builtins.h>
#include <pic18f47k42.h>

//REGION INTERRUPTS
//executes on External Interrupt 0
void Int0Handler() {
    LATEbits.LATE0 = 1;
    __delay_ms(1000);
    LATEbits.LATE0 = 0;
}

//executes on External Interrupt 1
void Int1Handler() {
    
}

//executes on External Interrupt 2
void Int2Handler() {
    
}

void interruptInit() {
    TRISB = 0xFF;
    ANSELB = 0x00;
    
    INTCON0bits.GIE = 1;
    INTCON0bits.GIEH = 1;
    INTCON0bits.GIEL = 1;
    
    PIE1bits.INT0IE = 1;
    PIE5bits.INT1IE = 1;
    PIE7bits.INT2IE = 1;
    
    INTCON0bits.INT0EDG = 1;
    INTCON0bits.INT1EDG = 1;
    INTCON0bits.INT2EDG = 1;
}

void __interrupt() isr(void) {
    if (PIR1bits.INT0IF) {
        PIR1bits.INT0IF = 0;
        Int0Handler();
        Nop();
    } else if (PIR5bits.INT1IF) {
        PIR5bits.INT1IF = 0;
        Int1Handler();
        Nop();
    } else if (PIR7bits.INT2IF) {
        PIR7bits.INT2IF = 0;
        Int2Handler();
        Nop();
    }
}
// END REGION INTERRUPTS

// REGION GAME
int body[64] = {0x01, 0x00};
int apple = 0x55;
int direction = 0x01; //0x01: left, 0x10: down, -0x01: right, -0x10: up
int score = 2;
int frame[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void updateBodyMovement() {
    int newHead = body[0] + direction;
    for(int i = score; i >= 0; i--) {
        body[i] = body[i - 1];
    }
    body[0] = newHead;
}

void imprintLossScreen() {
    int lossScreen[8] = {
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

void imprintWinScreen() {
    int winScreen[8] = {
        0b00000000,
        0b00100100,
        0b00100100,
        0b00000000,
        0b01000010,
        0b00111100,
        0b00000000,
        0b00000000
    };
    for (int i = 7; i >= 0; i--) {
        frame[i] = winScreen[i];
    }
}

void showFrame() {
    //display snake
    for (int i = 0; i < sizeof(body); i++) {
        int y = (body[i] & 0xF0) >> 4;
        int x = (body[i] & 0x0F);
        frame[y] += (0x01 << x);
    }
    
    //display apple
    int y = (apple & 0xF0) >> 4;
    int x = (apple & 0x0F);
    frame[y] += (0x01 << x);
    
    //cycle through pins
    for (int i = 0; i < sizeof(frame); i++) {
        LATA = frame[i];
        LATC = (0x01 << i) ^ 0xFF; // "^ 0xFF" = invert
    }
}

//END REGION GAME

int main(void) {
    TRISE = 0; // control register
    TRISA = 0; // define A as output register for x coordinate
    TRISC = 0; // define C as output register for y coordinate

    while(1) {
        LATEbits.LATE0 = 1;
        __delay_ms(200);
        LATEbits.LATE0 = 0;
        __delay_ms(200);
    }
    // InterruptInit();
    
    return 0;
}