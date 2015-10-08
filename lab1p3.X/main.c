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

//FSM states
typedef enum stateTypeEnum {
    Start, DebouncePress1, WaitRelease1, DebounceRelease1, DebouncePress2,
    WaitRelease2, DebounceRelease2, ChangeLed, Running, Clear, Stopped, WaitPress1, WaitPress2, Clear2
} stateType;

volatile stateType state;
//time variables
volatile int millis = 0;
volatile int seconds = 0;
volatile int minutes = 0;
//interrupt variables
unsigned int dummyVariable = 0;
unsigned int dummyVariable2 = 0;

// ******************************************************************************************* //
    
int main(void)
{
    //Initialization
    SYSTEMConfigPerformance(40000000);
    initLEDs();
    enableInterrupts();
    initSWRESET();
    initSWSS();
    initTimer1();
    initTimer2();
    initLCD();
    clearLCD();

    while(1)
    {
        switch (state) {
            case Start:
                turnOnLED(1);
                state = Clear;
                break;

            case Clear:
                clearLCD();
                state = Stopped;
                break;
                
            case Stopped:
                stopLCD();
                state = WaitPress1;
                T1CONbits.ON = 0;
                break;    
                
            case WaitPress1:
                getTimeString(millis, seconds, minutes);
                break;    
                
            case DebouncePress1:
                delayUs2(700);
                state = WaitRelease1;
                break;

            case WaitRelease1:
                break;

            case DebounceRelease1:
                delayUs2(700);
                state = ChangeLed;
                break;

            case ChangeLed:
                turnOnLED(2);
                state = Clear2;
                break;
                
             case Clear2:
                clearLCD();
                state = Running;
                break;
                      
            case Running:
                runLCD();
                state = WaitPress2;
                T1CONbits.ON = 1;
                break;    
                
             case WaitPress2:
                break;  

            case DebouncePress2:
                delayUs2(700);
                state = WaitRelease2;
                break;

            case WaitRelease2:
                break;

            case DebounceRelease2:
                delayUs2(700);
                state = Start;
                break;
        }
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _TInterrupt(){
    IFS0bits.T1IF = 0;
    millis+=1;
    if(millis==100){
        seconds+=1;
        millis=0;
        if(seconds==60){
            minutes+=1;
            seconds=0;
        }
    }
    
    getTimeString(millis, seconds, minutes);
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
      dummyVariable = PORTAbits.RA7 = 1;
      dummyVariable2 = PORTDbits.RD6 = 1;
      
    if ( IFS0bits.T1IF == 1) {T1CONbits.ON = 0;}
    if (state == WaitPress1 && IFS1bits.CNDIF==1 ) {
        millis = 0;
        seconds = 0;
        minutes = 0;}
      
    if (state == WaitPress1 && IFS1bits.CNAIF == 1) {
        state = DebouncePress1;
    } else 
    if (state == WaitRelease1 && IFS1bits.CNAIF == 1) {
        state = DebounceRelease1;
    } else 
    if (state == WaitPress2 && IFS1bits.CNAIF == 1) {
        state = DebouncePress2;
    } else
    if (state == WaitRelease2 && IFS1bits.CNAIF == 1) {
        state = DebounceRelease2;
    }
      IFS1bits.CNAIF = 0;
      IFS1bits.CNDIF = 0;
}
