/*
 * File:   timer.c
 * Authors: Team 206
 *
 */

#include <xc.h>
#include "timer.h"

#define CLEAR 0
#define SET_OFF 0
#define SET_ON 1


void initTimer1(){
    //Initialize Timer 1.
    TMR1 = CLEAR;                   //Clear TMR1
    T1CONbits.TCKPS = 0;            //Init pre-scaler 1
    T1CONbits.TCS = 0;              //Setting the oscillator
    IFS0bits.T1IF = SET_OFF;        //Put the flag down
    //IEC0bits.T2IE = SET_ON;       //Enable the interrupt
    //IPC2bits.T2IP = 6;            //Configure interrupt priority//
    T1CONbits.ON = SET_OFF;         //Turn timer on  
}
//Uses timer 1
void delayUs(unsigned int delay){
    TMR1 = CLEAR;                    //Clear TMR1
    PR1 = delay*80;                 //Period register, ms delay
    IFS0bits.T1IF = SET_OFF;         //Put flag down
    T1CONbits.ON = SET_ON;           //Turn timer on
    while(IFS0bits.T1IF == 0);       //Wait for change
    T1CONbits.ON = SET_OFF;          //Turn timer off
    
}