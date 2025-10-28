/*
 * A game of snake controlled by two buttons,
 * showing the game field on a led matrix and the score on a 7-segment display
 * 
 * Authors: Richard Leytes, Tom Weise
 * Devices: PIC18F47K42, 8x8 LED-Matrix, MIKROE-1201
 */
#include "Definitions.h"
#include "globals.h"
#include <builtins.h>
#include <pic18f47k42.h>

void configureRegisters() {
    // 0: output, 1:input 
    TRISE = 0; 
    TRISA = 0;
    TRISB = 0;
}

// executes on External Interrupt 0
void Int0Handler() {
    LATEbits.LATE0 = 1;
    __delay_ms(1000);
    LATEbits.LATE0 = 0;
}

// executes on External Interrupt 1
void Int1Handler() {
    
}

// executes on External Interrupt 2
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

int main(void) {
    configureRegisters();
    unsigned int oldScore = score;
    updateScoreDisplay(score);

    while(1) {
        if(oldScore != score) {
            // against flickering, only update when necessary
            updateScoreDisplay(score);
            oldScore = score;
        }
        applyGameLogic();
        __delay_ms(700);
    }
    return 0;
}