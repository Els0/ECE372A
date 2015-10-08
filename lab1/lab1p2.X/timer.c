/*
 * File:   timer.c
 * Authors: TEAM 206
 *
 */

#include <xc.h>
#include "timer.h"

#define S_ON 1
#define S_OFF 0
#define S_CLR 0

void initTimer2() {
    TMR2 = S_CLR;               //Clear TMR1
    T2CONbits.TCKPS = 3;        //Init pre-scaler 8
    T2CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T2IF = S_OFF;      //Put the flag down
    T2CONbits.ON = S_OFF;       //Turn timer off
}



void delayUs(unsigned int delay){
    
    if (delay == 0) return;
    TMR2 = S_CLR;               //Clear TMR1
    PR2 = delay * 10;          //Period register, us delay ** NOTE change prescaler to 8
    IFS0bits.T2IF = S_OFF;      //Put flag down
    T2CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T2IF == 0); //Wait for change
    T2CONbits.ON = S_OFF;       //Turn timer off
}