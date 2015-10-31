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
unsigned int dummyVariable2 = 0;
volatile int uni = 0;
volatile int dec = 0;
volatile int cen = 0;
volatile int mil = 0;

volatile int v1 = 0;
volatile int v2 = 0;
volatile int v3 = 0;

int main(void){
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initTimer1();
    initTimer2();
    initPWM();
    initPWM2();
    initSW();  
    initLCD();
    clearLCD();
    initHBridgeInputs();
    initADC();
    
    while (1) {
              
         switch (state) {
            case Idle:
                ToggleMode(1);
                AD1CON1bits.ADON = 1;
                break;
                
            case Idle2:
                ToggleMode(1);
                AD1CON1bits.ADON = 1;
                break;

             case Forward:
                ToggleMode(2);
                AD1CON1bits.ADON = 1;
                break;

            case Backward:
                ToggleMode(3);
                AD1CON1bits.ADON = 1;
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

    //Assign the correct values for the motor to work to the OCxRS variables.
    OC2RS = ADC1BUF0+400;
    if(ADC1BUF0 < 512) {OC4RS = 1023;}
    else {OC4RS = ((-1023+ADC1BUF0)*(-1))+(400);}
   
    //Divides the value stored in the ADC1Buffer into thousands, hundreds, tens, units.
    mil = ADC1BUF0/1000;
    cen = ADC1BUF0%1000/100;
    dec = ADC1BUF0%1000%100/10;
    uni = ADC1BUF0%1000%100%10;
    
    //Print the value of the ADC Buffer into the LCD in the correct position.    
    moveCursorLCD(0, 0);
    printCharLCD('A');
    printCharLCD('D');
    printCharLCD('C');
    printCharLCD('=' );
    printCharLCD('0' + mil);
    printCharLCD('0' + cen);
    printCharLCD('0' + dec);
    printCharLCD('0' + uni);
    
    ///Calculate the value of the voltage read from the potentiometer.
    v1 = (int)(ADC1BUF0*5.00/1023.00);
    v2 = (int)((ADC1BUF0*5.00/1023.00)*10);
    v2=v2%10;
    v3 = (int)((ADC1BUF0*5.00/1023.00)*100);
    v3=v3%10;
    
    //Print the value of the voltage read from the potentiometer.
    moveCursorLCD(0, 2);
    printCharLCD('V');
    printCharLCD('t');
    printCharLCD('s');
    printCharLCD('=');
    
    printCharLCD('0'+v1);
    printCharLCD('.');
    printCharLCD('0'+v2);
    printCharLCD('0'+v3);
    
    AD1CON1bits.ADON = 0;   //Turns off the ADC.
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
      dummyVariable = PORTDbits.RD6;
    
      if (state == Idle) 
      {
          state = DebouncePress;
      }
      else
      if (state==WaitRelease) 
      {
      state=DebounceRelease;
      }
      else
      if (state == Forward) 
      {
          state = DebouncePress2;
      }
      else
      if (state == WaitRelease2) 
      {
          state = DebounceRelease2;
      }
      else
      if (state == Idle2)
      {
          state = DebouncePress3;
      } 
      else
      if (state==WaitRelease3)
      {
      state=DebounceRelease3;
      }
      else
      if (state == Backward) 
      {
          state = DebouncePress4;
      }
      else
      if (state == WaitRelease4) 
      {
          state = DebounceRelease4;
      }
     IFS1bits.CNDIF = 0;     
}
