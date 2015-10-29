/* 
* Author: TEAM 206
*
* Created on 10/22/2015
*
*/


#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "lcd.h"

#define ENABLED  1
#define DISABLED  0

typedef enum stateTypeEnum {
    Forward, Backward, Idle, Idle2, DebouncePress, DebounceRelease, WaitRelease, DebouncePress2, DebounceRelease2, WaitRelease2, DebouncePress3, DebounceRelease3, WaitRelease3, DebouncePress4, DebounceRelease4, WaitRelease4
} stateType;

volatile stateType state = Idle;
unsigned int dummyVariable = 0;

int main(void){
    SYSTEMConfigPerformance(40000000);
    initTimer1();
    initTimer2();
    initPWM();
    initPWM2();
    initSW();
    initADC();
    enableInterrupts();
    initLCD();
    clearLCD();
    initHBridgeInputs();
    
    while (1) {
              
         switch (state) {
            case Idle:
                printCharLCD('I');
                ToggleMode(1);
                break;
                
            case Idle2:
                printCharLCD('D');
                ToggleMode(1);
                break;

             case Forward:
                 printCharLCD('F');
                 ToggleMode(2);
                break;

            case Backward:
                printCharLCD('B');
                ToggleMode(3);
                break;

            case DebouncePress:
                delayUs(700);
                state = WaitRelease;
                break;

            case DebounceRelease:
                delayUs(700);
                state = Forward;
                break;

            case WaitRelease:
                break;

            case DebouncePress2:
                delayUs(700);
                state = WaitRelease2;
                break;

            case DebounceRelease2:
                delayUs(700);
                state = Idle2;
                break;

            case WaitRelease2:
                break;

            case DebouncePress3:
                delayUs(700);
                state = WaitRelease3;
                break;

            case DebounceRelease3:
                delayUs(700);
                state = Backward;
                break;

            case WaitRelease3:
                break;

            case DebouncePress4:
                delayUs(700);
                state = WaitRelease4;
                break;

            case DebounceRelease4:
                delayUs(700);
                state = Idle;
                break;

            case WaitRelease4:
                break;
          }
    }

    return 0;
       
}


void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
    OC4RS = ADC1BUF0;   
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
      dummyVariable = PORTDbits.RD6;
    
      if ((state == Idle) &&  (IFS1bits.CNDIF == 1)) 
      {state = DebouncePress;}
      else
      if ((state==WaitRelease) && (IFS1bits.CNDIF == 1)) {
      state=DebounceRelease;}
      else
      if ((state == Forward) &&  (IFS1bits.CNDIF == 1)) 
      {state = DebouncePress2;}
      else
      if ((state == WaitRelease2) &&  (IFS1bits.CNDIF == 1)) 
      {state = DebounceRelease2;}
      else
      if ((state == Idle2) &&  (IFS1bits.CNDIF == 1)) 
      {state = DebouncePress3;} 
      else
      if ((state==WaitRelease3) && (IFS1bits.CNDIF == 1)) {
      state=DebounceRelease3;}
      else
      if ((state == Backward) &&  (IFS1bits.CNDIF == 1)) 
      {state = DebouncePress4;}
      else
      if ((state == WaitRelease4) &&  (IFS1bits.CNDIF == 1)) 
      {state = DebounceRelease4;}
     IFS1bits.CNDIF = 0;
         
}
