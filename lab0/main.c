/* 
 * File:   main.c
 * Author: oscarmoralesvera
 * Description: lab 0.
 * Team: 206
 * Date: 09/18/2015
 * 
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define S_ON 1
#define S_OFF 0
#define PRESSED 0
#define RELEASED 1

typedef enum stateTypeEnum {
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

volatile stateType state = led1;

int main() {

    enableInterrupts();

    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();

    while (1) {

        switch (state) {
            case led1:
                turnOnLED(1);
                if (SW1 == PRESSED) {
                    state = debouncePress;
                }
                break;

            case led2:
                turnOnLED(2);
                if (SW1 == PRESSED) {
                    state = debouncePress;
                }
                break;

            case led3:
                turnOnLED(3);
                if (SW1 == PRESSED) {
                    state = debouncePress;
                }
                break;

            case debouncePress:
                delayMs(30);
                state = wait;
                toggleTimer1(1);
                break;

            case wait:
                if (IFS0bits.T1IF == S_OFF && SW1 == RELEASED) {
                    state = debounceRelease;
                }
                if (IFS0bits.T1IF == S_ON && SW1 == PRESSED) {
                    state = wait2;
                }
                break;

            case wait2:
                if (SW1 == RELEASED) {
                    state = debounceRelease2;
                }
                break;

            case debounceRelease:
                delayMs(30);
                toggleTimer1(0);
                if (LATDbits.LATD0 == S_ON) {
                    state = led2;
                } else if (LATDbits.LATD1 == S_ON) {
                    state = led3;
                } else if (LATDbits.LATD2 == S_ON) {
                    state = led1;
                }
                break;

            case debounceRelease2:
                delayMs(30);
                toggleTimer1(0);
                if (LATDbits.LATD0 == S_ON) {
                    state = led3;
                } else if (LATDbits.LATD1 == S_ON) {
                    state = led1;
                } else if (LATDbits.LATD2 == S_ON) {
                    state = led2;
                }
                break;
        }
    }

    return 0;
}