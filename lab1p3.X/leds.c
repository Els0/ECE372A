/*
 * File:   leds.c
 * Author: TEAM 206
 *
 */

#include <xc.h>
#include "leds.h"

#define OUTPUT 0
#define INPUT 1

void initLEDs() {
    TRISGbits.TRISG12 = OUTPUT; // TRD1
    TRISGbits.TRISG14 = OUTPUT; // TRD2
    ODCGbits.ODCG12 = 1;
    ODCGbits.ODCG14 = 1;
    LATGbits.LATG12 = 1;
    LATGbits.LATG14 = 0;
}

void turnOnLED(int led){
    if (led==1){                //Turn on led 1 (run)
        LATGbits.LATG12 = 0;
        LATGbits.LATG14 = 1;
    }
    else if (led==2){           ///Turn on led 2 (stop)
        LATGbits.LATG12 = 1;
        LATGbits.LATG14 = 0;
    }
}