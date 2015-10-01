/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

#define S_ON 1
#define S_OFF 0
#define S_CLR 0

void initTimer2() {
    TMR2 = S_CLR;               //Clear TMR2
    T2CONbits.TCKPS = 0;        //Init pre-scaler 1
    T2CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T2IF = S_OFF;      //Put the flag down    
}

void delayus(unsigned int delay) {
    TMR2 = S_CLR;               //Clear TMR2
    PR2 = delay * 624;          //Period register, ms delay
    IFS0bits.T2IF = S_OFF;      //Put flag down
    T2CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T2IF == 0); //Wait for change
    T2CONbits.ON = S_OFF;       //Turn timer off
}