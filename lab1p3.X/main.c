// ******************************************************************************************* //
//
// File:         lab1p3.c
// Authors:      TEAM 206
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt2.h"
#include "switchReset.h"
#include "switchSS.h"


typedef enum stateTypeEnum {
    Start, DebouncePress1, WaitRelease1, DebounceRelease1, DebouncePress2,
    WaitRelease2, DebounceRelease2, ChangeLed
} stateType;

volatile stateType state;
unsigned int dummyVariable = 0;

// ******************************************************************************************* //
int main(void)
{
    SYSTEMConfigPerformance(80000000);
    
    state = Start;
    enableInterrupts();
    initLEDs();
    initSWRESET();
    initSWSS();
    initTimer1(); 
    initLCD();

    while(1)
    {
        switch (state) {
            case Start:
                //delayUs(20);
                toggleLED();
                break;

            case DebouncePress1:
                delayUs(700);
                state = WaitRelease1;
                break;

            case WaitRelease1:
                //delayUs(20);
                break;

            case DebounceRelease1:
                delayUs(700);
                state = ChangeLed;
                break;

            case ChangeLed:
                //delayUs(20);
                toggleLED();
                break;

            case DebouncePress2:
                delayUs(700);
                state = WaitRelease2;
                break;

            case WaitRelease2:
                //delayUs(20);
                break;

            case DebounceRelease2:
                delayUs(700);
                state = Start;
                break;
        }
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _TInterrupt(){
    IFS0bits.T1IF = 0;
    //counter = counter +1;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    //TODO: Implement the interrupt to capture the press of the button
      dummyVariable = PORTAbits.RA7 = 1;
      IFS1bits.CNAIF = 0;
    if (state == Start) {
        state = DebouncePress1;
    } else 
    if (state == WaitRelease1) {
        state = DebounceRelease1;
    } else 
    if (state == ChangeLed) {
        state = DebouncePress2;
    } else
    if (state == WaitRelease2) {
        state = DebounceRelease2;
    }
}
