/*
 * File:   leds.c
 * Author: TEAM 206
 *
 * Created on December 27, 2014, 1:31 PM
 */

#include <xc.h>
#include "leds.h"

#define OUTPUT 0
#define INPUT 0

void initLEDs() {
    TRISGbits.TRISG12 = INPUT;
    TRISGbits.TRISG14 = INPUT;
}

void turnOnLED(int led) {
    if (led == 1) {
        //PORTGbits.RG12 = 0;
        //TRISGbits.TRISG14 = OUTPUT;
        LATGbits.LATG12 = 1;
        LATGbits.LATG14 = 0;
    } 
    else if(led == 2) {
        LATGbits.LATG12 = 0;
        LATGbits.LATG14 = 1;
    }
}