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
    initLCD();

    while(1)
    {
        testLCD();
    }
    
    return 0;
}
