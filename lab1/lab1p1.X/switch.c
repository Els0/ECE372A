/*
 * File:   switch.c
 * Author: Team 206
 *
 */

#include <xc.h>
#include "switch.h"

#define S_ON 1
#define S_OFF 0
#define INPUT 1
#define OUTPUT 0

void initSW2() {
    TRISAbits.TRISA7 = INPUT; //Configure Digital Input for the switch. 
    CNCONAbits.ON = S_ON; 
    CNENAbits.CNIEA7 = S_ON;         // Enable pin CN
    CNPUAbits.CNPUA7 = S_ON;      //Pull Up resistor
    //Enable Interrupt        
    IFS1bits.CNAIF = S_OFF;
    IPC8bits.CNIP = 7;            // Configure interrupt priority
    IEC1bits.CNAIE = S_ON;   
    
   

}

