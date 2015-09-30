/*
 * File:   leds.c
 * Author: TEAM 206
 *
 * Created on December 27, 2014, 1:31 PM
 */

#include <xc.h>
//#include "leds.h"

#define OUTPUT 0
#define INPUT 1

void initLEDs() {
    TRISGbits.TRISG12 = OUTPUT; // TRD1
    TRISGbits.TRISG14 = OUTPUT; // TRD2
    ODCGbits.ODCG12 = 1;
    ODCGbits.ODCG14 = 1;
    LATGbits.LATG12 = 0;
    LATGbits.LATG14 = 1;
}

void runLED() {
    LATGbits.LATG12 = 1;
    LATGbits.LATG14 = 0;
}

void stopLED() {
    LATGbits.LATG12 = 0;
    LATGbits.LATG14 = 1;
}