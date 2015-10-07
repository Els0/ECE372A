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
    //Initialization of devices
    SYSTEMConfigPerformance(80000000);
    
    initSW1();
    initLEDs();
    initTimer1();
    
    //Enables interrupts
    enableInterrupts();

    while (1) {
        //Debounce the switch
        /*switch (state) {
            case waitPress1:
                break;
            case debouncePress1:
                state = waitRelease1;
                delayMs(700);
                break;
            case waitRelease1:
                toggleLED();
                break;
            case debounceRelease1:
                state = ledStop;
                delayMs(700);
                break;
            case ledStop:
                break;
            case debouncePress2:
                state = waitRelease2;
                delayMs(700);
                break;
            case waitRelease2:
                toggleLED();
                break;
            case debounceRelease2:
                state = waitPress1;
                delayMs(700);
                break;
        }*/
        switch (state) {
            case waitPress1:
                break;
            case waitRelease1:
                break;
            case ledStop:
                break;
            case waitRelease2:
                break;
        }
        return 0;
    }
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    dummyVariable = PORTAbits.RA7 = 1;
    IFS1bits.CNAIF = 0;
    /*if (state == waitPress1) {
        toggleLED();
        state = debouncePress1;
    } 
    else if (state == waitRelease1) {
        state = debounceRelease1;
    } 
    else if (state == ledStop) {
        toggleLED();
        state = debouncePress2;
    } 
    else if (state == waitRelease2) {
        state = debounceRelease2;
    }*/
    if (state == waitPress1) {
        state = waitRelease1;
        delayUs(700);
    } 
    else if (state == waitRelease1) {
        state = ledStop;
        toggleLED();
        delayUs(700);
    } 
    else if (state == ledStop) {
        state = waitRelease2;
        delayUs(700);
    } 
    else if (state == waitRelease2) {
        state = waitPress1;
        toggleLED();
        delayUs(700);
    }
}