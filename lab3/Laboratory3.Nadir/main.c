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
    Forward, Backward, Left, Right, Idle
} stateType;

volatile stateType state = Idle;



int main(void){
    SYSTEMConfigPerformance(40000000);
    initTimer1();
    //initTimer2();
    initPWM();
    initPWM2();
    //initADC();
    enableInterrupts();
    initLCD();
    clearLCD();
    
    while (1) {
       //char string = 'Nadir';
       printCharLCD('c');
       //delayUs(500);
       //initLCD();
       //runLCD();
       //printStringLCD(string);
       //string = ADC1BUF0;
        
         /*switch (state) {
            case Idle:
                break;
                
            case Forward:
                break;

            case Backward:
                break;
                
            case Left:
                break;
                
            case Right:           
                break;
        }*/
    }

    return 0;
       
}


void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
    OC4RS = ADC1BUF0;   
}

