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



//Timer used to show the clock on the LCD
void initTimer1() {
    TMR1 = S_CLR;               //Clear TMR1
    T1CONbits.TCKPS = 1;        //Init pre-scaler 8
    T1CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T1IF = S_OFF;      //Put the flag down
    IEC0bits.T1IE = S_ON;       //Enables the interrupt
    IPC1bits.T1IP = 7;          //Configure interrupt priority
    T1CONbits.ON = S_OFF;       //Turn timer off
}



void delayUs1(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    if (delay == 0) return;
    TMR1 = S_CLR;               //Clear TMR1
    PR1 = delay * 10;          //Period register, us delay ** NOTE change prescaler to 8
    IFS0bits.T1IF = S_OFF;      //Put flag down
    T1CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T1IF == 0); //Wait for change
    T1CONbits.ON = S_OFF;       //Turn timer off
}


//Timed used for every delay in the program
void initTimer2() {
    TMR2 = S_CLR;               //Clear TMR1
    T2CONbits.TCKPS = 3;        //Init pre-scaler 8
    T2CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T2IF = S_OFF;      //Put the flag down
    T2CONbits.ON = S_OFF;       //Turn timer off
}



void delayUs2(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    if (delay == 0) return;
    TMR2 = S_CLR;               //Clear TMR1
    PR2 = delay * 10;          //Period register, us delay ** NOTE change prescaler to 8
    IFS0bits.T2IF = S_OFF;      //Put flag down
    T2CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T2IF == 0); //Wait for change
    T2CONbits.ON = S_OFF;       //Turn timer off
}