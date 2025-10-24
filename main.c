/*
 * File:   Main.c
 * Author: Richard Leytes
 *
 * Created on October 14, 2025, 4:27 PM
 */

#include "Definitions.h"

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

void InterruptInit() {
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

//END REGION INTERRUPTS

//REGION GAME
int body[64] = {0x01, 0x00};
int apple = 0x55;
int direction = 0x01; //0x01: left, 0x10: down, -0x01: right, -0x10: up

void DisplayFrame() {
    int frame[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
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
        LATC = (0x01 << i);
    }
}

//END REGION GAME

int main(void) {
    InterruptInit();
    
    TRISA = 0; //output x coordinate
    TRISC = 0; //output y coordinate
    TRISE = 0; //control register
    
    Nop();
    return 0;
}