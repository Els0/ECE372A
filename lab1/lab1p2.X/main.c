// ******************************************************************************************* //
//
// File:         lab1p2.c
// Authors:      TEAM 206
//
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
    }
    
    return 0;
}
