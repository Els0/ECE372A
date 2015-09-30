// ******************************************************************************************* //
//
// File:        lab1p1.c
// Date:        09/24/2015 
// Authors:     TEAM 206
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define S_ON 1
#define S_OFF 0
#define PRESSED 0
#define RELEASED 1

typedef enum stateTypeEnum {
    waitPress1, debouncePress1, waitRelease1, debounceRelease1, ledStop, debouncePress2, waitRelease2, debounceRelease2
} stateType;

volatile stateType state = waitPress1;
unsigned int dummyVariable = 0;

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void) {
    //Enables interrupts
    enableInterrupts();
    //Initialization of devices
    initSwitch1();
    initLEDs();
    initTimer1();

    while (1) {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        switch (state) {

                //Turns led1 ON, and 2-3 OFF
            case waitPress1:
                turnOnLED(1);
                break;
                
            case debouncePress1:
                delayMs(20);
                state = waitRelease1;
                break;
                
            case waitRelease1:
                break;
                
            case debounceRelease1:
                delayMs(20);
                state = ledStop;
                break;
                
            case ledStop:
                turnOnLED(2);
                break;
                
            case debouncePress2:
                delayMs(20);
                state = waitRelease2;
                break;
                
            case waitRelease2:
                break;
                
            case debounceRelease2:
                delayMs(20);
                state = waitPress1;
                break;
        }

        return 0;
    }
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SRS) _CNInterrupt(void) {
    //TODO: Implement the interrupt to capture the press of the button
    dummyVariable = PORTAbits.RA7 = 1;
    IFS1bits.CNAIF = 0;
    if (state == waitPress1) {
        state = debouncePress1;
    } else if (state == waitRelease1) {
        state = debounceRelease1;
    } else if (state == ledStop) {
        state = debouncePress2;
    } else if (state == waitRelease2) {
        state = debounceRelease2;
    }
}