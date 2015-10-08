/*
* File:   leds.c
* Author: Team 206
*
*/

#include <xc.h>
#include "leds.h"

#define OUTPUT 0
#define INPUT 1


void initLEDs(){
    TRISGbits.TRISG12 = OUTPUT;
    TRISGbits.TRISG14 = OUTPUT;
    //ODCGbits.ODCG12 = 1;
    //ODCGbits.ODCG14 = 1;
}

void turnOnLED(int led){

    if (led==1){                //Turn on led 1 (run)
        //TRISGbits.TRISG12 = 1;
        //PORTGbits.RG14 = 0;
        LATGbits.LATG12 = 0;
        LATGbits.LATG14 = 1;
        //delayUs(20);
    }
    else if (led==2){           ///Turn on led 2 (stop)
        //TRISGbits.TRISG14 = 1;
        //PORTGbits.RG12 = 0;
        LATGbits.LATG12 = 1;
        LATGbits.LATG14 = 0;
       //delayUs(20);
    }
}