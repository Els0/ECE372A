/*
 * File:   switch.c
 * Author: TEAM 206
 *
 */

//#include <proc/p32mx470f512l.h>
#include <xc.h>

#define INPUT 1
#define OUTPUT 0
#define ENABLED 1
#define DISABLED 0

void initSWSS(){
    TRISAbits.TRISA7 = INPUT;           // Configure switch as input
    CNCONAbits.ON = 1;                  // Enable overall interrupt
    CNENAbits.CNIEA7 = ENABLED;         // Enable pin CN
    CNPUAbits.CNPUA7 = ENABLED;         // Enable pull-up resistor
    IFS1bits.CNAIF = 0;                 // Put down the flag
    IPC8bits.CNIP = 7;                  // Configure interrupt priority
    IEC1bits.CNAIE = ENABLED;           // Enable interrupt for D pins
}