// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt2.h"


// ******************************************************************************************* //

int main(void)
{
    SYSTEMConfigPerformance(40000000);
    
    initTimer2();
    initLCD();

    while(1)
    {
        testLCD();
        //        writeFourBits(0b10100000, 0, 4100, 0);
//      for(i = 0; i < 1000; i++) delayUs(1000);
//      LATDbits.LATD0 ^= 1;
    }
    
    return 0;
}
