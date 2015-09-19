/* 
 * File:   timer.c
 * Author: oscarmoralesvera
 *
 */

#include <xc.h>
#include <proc/p32mx470f512l.h>

#define S_ON 1
#define S_OFF 0
#define S_CLR 0

void initTimer1() {
    TMR1 = S_CLR;               //Clear TMR1
    PR1 = 2442;                 //Init PR1
    T1CONbits.TCKPS = 3;        //Init pre-scaler 256
    T1CONbits.TCS = 0;          //Setting the oscillator
    T1CONbits.ON = S_OFF;       //Turn timer of  
}

void toggleTimer1(int clk) {
    if (clk == 0) {
        IFS0bits.T1IF = S_OFF;  //Put the flag down
        T1CONbits.ON = S_OFF;   
        TMR1 = S_CLR;           //Clear TMR1    
    } else if (clk == 1) {
        T1CONbits.ON = S_ON;
    }
}

void initTimer2() {
    TMR2 = S_CLR;               //Clear TMR2
    T2CONbits.TCKPS = 0;        //Init pre-scaler 1
    T2CONbits.TCS = 0;          //Setting the oscillator
    IFS0bits.T2IF = S_OFF;      //Put the flag down    
}

void delayMs(unsigned int delay) {
    TMR2 = S_CLR;               //Clear TMR2
    PR2 = delay * 624;          //Period register, ms delay
    IFS0bits.T2IF = S_OFF;      //Put flag down
    T2CONbits.ON = S_ON;        //Turn timer on
    while (IFS0bits.T2IF == 0); //Wait for change
    T2CONbits.ON = S_OFF;       //Turn timer off
}