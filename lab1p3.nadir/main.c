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
    WaitRelease2, DebounceRelease2, ChangeLed, Running, Clear, Stopped, WaitPress1
} stateType;

volatile stateType state;
volatile int milis;
volatile int seconds;
volatile int minutes;
unsigned int dummyVariable = 0;

// ******************************************************************************************* //
int main(void)
{
    SYSTEMConfigPerformance(40000000);
    
    state = Start;
    enableInterrupts();
    initLEDs();
    initSWRESET();
    initSWSS();
    initTimer2(); 
    //initLCD();
    testLCD();

    while(1)
    {
        switch (state) {
            case Start:
                turnOnLED(1);
                 stopLCD();
                break;

            case Clear:
                clearLCD();
                state = Stopped;
                break;
                
            case Stopped:
                stopLCD();
                state = WaitPress1;
                break;    
                
            case WaitPress1:
                break;    
                
            case DebouncePress1:
                delayUs(700);
                state = WaitRelease1;
                break;

            case WaitRelease1:
                break;

            case DebounceRelease1:
                delayUs(700);
                state = ChangeLed;
                break;

            case ChangeLed:
                turnOnLED(2);
                runLCD();
                break;

            case DebouncePress2:
                delayUs(700);
                state = WaitRelease2;
                break;

            case WaitRelease2:
                break;

            case DebounceRelease2:
                delayUs(700);
                state = Start;
                break;
        }
    }
    
    return 0;
}

void __ISR(_TIMER_2_VECTOR, IPL3SRS) _TInterrupt(){
    IFS0bits.T2IF = 0;
    milis+=milis;
    if(milis==99){
        seconds+=seconds;
        milis=0;
        if(seconds==60){
            minutes=minutes;
            seconds=0;
        }
    }
    //Here the function to write minutes:seconds:milis
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    //TODO: Implement the interrupt to capture the press of the button
      dummyVariable = PORTAbits.RA7 = 1;
      IFS1bits.CNAIF = 0;
    if (state == Start) {
        state = DebouncePress1;
    } else 
    if (state == WaitRelease1) {
        //T2CONbits.ON = 1;
        state = DebounceRelease1;
    } else 
    if (state == ChangeLed) {
        state = DebouncePress2;
    } else
    if (state == WaitRelease2) {
        //T2CONbits.ON = 0;
        state = DebounceRelease2;
    }
}
