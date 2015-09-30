/*
 * File:   switch.c
 * Author: TEAM 206
 *
 * Created on September 19, 2015, 10:46 AM
 */

//#include <proc/p32mx470f512l.h>
#include <xc.h>

#define INPUT 1
#define OUTPUT 0
#define S_ON 1
#define S_OFF 0

void initSwitch1() {
    TRISAbits.TRISA7= INPUT;   //Configure digital input
    CNPUAbits.CNPUA7 = S_ON;   //Pull up resistor
    CNCONAbits.ON = S_ON;       //Enable overall interrupt
    CNENAbits.CNIEA7 = S_ON;   //Enable pin CN
    IFS1bits.CNAIF = S_OFF;     //Put down flag
    IPC8bits.CNIP = 2;          //Configure interrupt priority
    IPC8bits.CNIS = 3;          //Configure the interrupt sub-priority
    IEC1bits.CNAIE = S_ON;      //Enable interrupt for G pins
}
