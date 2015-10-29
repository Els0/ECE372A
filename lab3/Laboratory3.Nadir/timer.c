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

void initTimer1() {
    TMR2 = S_CLR;               //Clear TMR1
    T2CONbits.TCKPS = 3;        //Init pre-scaler 8
    T2CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T2IF = S_OFF;      //Put the flag down
    T2CONbits.ON = S_OFF;       //Turn timer off
}



void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    if (delay == 0) return;
    TMR2 = S_CLR;               //Clear TMR1
    PR2 = delay * 10;          //Period register, us delay ** NOTE change prescaler to 8
    IFS0bits.T2IF = S_OFF;      //Put flag down
    T2CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T2IF == 0); //Wait for change
    T2CONbits.ON = S_OFF;       //Turn timer off
}
///////////////////////////////////
//////////////////////////////////
///////TESTS////////////////////////
///////ABOVE//////////////////////
//////////////////////////////////

//README
//Puede que se haga un desmadre mezclando estos timers c: asi que quizas se tenga que cambiar para utilizar el timer 1 y 2 para el control, y el timer 3 para todo el resto del desmadre de delays y la madre alv.
//Timer1 used for all the other delays.

/*void initTimer1() {
    TMR1 = S_CLR;               //Clear TMR1
    T1CONbits.TCKPS = 1;        //Init pre-scaler 8
    T1CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T1IF = S_OFF;      //Put the flag down
    T1CONbits.ON = S_OFF;       //Turn timer off
}



void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
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
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    T2CONbits.ON = 1;
}

//Uses timer 2
void delayUs2(unsigned int delay){
    TMR1 = 0;
    PR1 = 5*delay;
    IFS0bits.T2IF = 0;
    T1CONbits.TCKPS = 1;
    disableInterrupts();
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0);
    T1CONbits.TON = 0;
    enableInterrupts();
}*/