/*
 * File:   timer.c
 * Author: TEAM 206
 *
 * Created on 10/22/2015
 */


#include <xc.h>
#include "timer.h"
#include "interrupt.h"

#define S_ON 1
#define S_OFF 0
#define S_CLR 0

//Timer1 used for all the other delays.

void initTimer1() {
    TMR1 = S_CLR;               //Clear TMR1
    T1CONbits.TCKPS = 1;        //Init pre-scaler 8
    T1CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T1IF = S_OFF;      //Put the flag down
    T1CONbits.ON = S_OFF;       //Turn timer off
}



void delayUs(unsigned int delay){
    if (delay == 0) return;
    TMR1 = S_CLR;               //Clear TMR1
    PR1 = delay * 10;          //Period register, us delay ** NOTE change prescaler to 8
    IFS0bits.T1IF = S_OFF;      //Put flag down
    T1CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T1IF == 0); //Wait for change
    T1CONbits.ON = S_OFF;       //Turn timer off
}



// TEAM 206 FTW


//Timer2 is used for the PWM
void initTimer2(){
    TMR2 = 0;
    PR2 = 1023;
    T2CONbits.TCKPS = 0;        //Init pre-scaler 
    T2CONbits.TCS = S_OFF;      //Setting the oscillator
    T2CONbits.ON = S_ON;       //Turn timer on
}

//Timer used by the ultrasonic sensor
void initTimer4() {
    TMR4 = S_CLR;               //Clear TMR1
    PR4 =  65000; 
    T4CONbits.TCKPS = 7;        //Init pre-scaler 1
    T4CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T4IF = S_OFF;      //Put the flag down
    //IEC0bits.T4IE = S_ON;       //Enables the interrupt
    //IPC4bits.T4IP = 7;          //Configure interrupt priority
    T4CONbits.ON = S_OFF;       //Turn timer off
}