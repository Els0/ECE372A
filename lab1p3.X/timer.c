/*
 * File:   timer.c
 * Authors: TEAM 206
 *
 */

#include <xc.h>
#include "timer.h"
#include <proc/p32mx470f512l.h>

#define S_ON 1
#define S_OFF 0
#define S_CLR 0

void delayUs(unsigned int delay){
    TMR1 = S_CLR;               //Clear TMR1
    PR1 = delay * 10;           //Period register, us delay ** NOTE change prescaler to 8
    IFS0bits.T1IF = S_OFF;      //Put flag down
    T1CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T1IF == 0); //Wait for change
    T1CONbits.ON = S_OFF;       //Turn timer off
}

void initTimer2(){
    //Initialize Timer 2.
    TMR2 = S_CLR;                   //Clear TMR1
    T2CONbits.TCKPS = 0;            //Init pre-scaler 1
    T2CONbits.TCS = 0;              //Setting the oscillator
    IFS0bits.T2IF = S_OFF;        //Put the flag down
    IEC0bits.T2IE = S_ON;       //Enable the interrupt
    IPC2bits.T2IP = 7;            //Configure interrupt priority//
    T2CONbits.ON = S_OFF;         //Turn timer on  
}
//Uses timer 2
void delayUs2(unsigned int delay){
    // Using timer 2, create a delay
    // that is delay amount of us.
    TMR2 = S_CLR;                  //Clear TMR2
    PR2 = delay*80;                //Period register, us delay
    IFS0bits.T2IF = S_OFF;         //Put flag down
    T2CONbits.ON = S_ON;           //Turn timer on
    while(IFS0bits.T2IF == 0);     //Wait for change
    T2CONbits.ON = S_OFF;          //Turn timer off
}