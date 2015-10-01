// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      Team 206
// Created on September 24th 2015
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt2.h"
#include "switch.h"
#include "timer.h"

typedef enum stateTypeEnum {
    Start, DebouncePress1, WaitRelease1, DebounceRelease1, DebouncePress2,
    WaitRelease2, DebounceRelease2, ChangeLed
} stateType;

volatile stateType state;
unsigned int dummyVariable = 0;

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void) {
    
    SYSTEMConfigPerformance(80000000);
    
    state = Start;
    enableInterrupts();
    initLEDs();
    initSW2();
    initTimer1();

    while (1) {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch

        switch (state) {
            case Start:
                //delayUs(20);
                turnOnLED(1);
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
                turnOnLED(2);
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

