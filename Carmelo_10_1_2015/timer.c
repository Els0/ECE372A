/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"
#include <proc/p32mx470f512l.h>

#define S_ON 1
#define S_OFF 0
#define S_CLR 0

void delayMs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR1 = S_CLR;               //Clear TMR1
    PR1 = delay * 80;          //Period register, ms delay
    IFS0bits.T1IF = S_OFF;      //Put flag down
    T1CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T1IF == 0); //Wait for change
    T1CONbits.ON = S_OFF;       //Turn timer off
}