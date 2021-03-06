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
    Forward, Idle, Sensor, Turn_Left, Turn_Right, Turn_Left2, Turn_Right2, Ramp_Down, Ramp_Up,  Finish, WaitPress, DebouncePress, DebounceRelease, WaitRelease
} stateType;

volatile stateType state = Sensor;
unsigned int dummyVariable = 0;
unsigned int dummyVariable2 = 0;
int S0=0;
int S1=0;
int S2=0;
int S3=0;
int i=0;
int x=0;
int y=0;


int main(void){
    SYSTEMConfigPerformance(40000000);
    initTimer1();
    initTimer2();
    initTimer4(); 
    //initPWM();
    //initPWM2();
    initSW();
    enableInterrupts();
    initHBridgeInputs();
    //initADC1();   
    //initADC2();   
    //initADC3();   
    //initADC4();   
    InitSensor();
    
    while (1) {
              
         switch (state) {
            case Idle:
                ToggleMode(1);
                AD1CON1bits.ADON = 1;
                break;
                
            case Forward:
                 ToggleMode(2);
                 AD1CON1bits.ADON = 1;
                break;

            case Turn_Right:
                ToggleMode(5);
                AD1CON1bits.ADON = 1;
                break;

            case Turn_Left:
                ToggleMode(4);
                AD1CON1bits.ADON = 1;
                break;
                
            case Turn_Right2:        
                i=0;
                ToggleMode(5);
                for (i = 0; i < 1000; i++) delayUs(1000);
                AD1CON1bits.ADON = 1;
                break;

                
            case Sensor:
                ReadSensor();
                //AD1CON1bits.ADON = 1;
                break;
                
            case Turn_Left2:
                i=0;
                ToggleMode(4);
                for (i = 0; i < 1000; i++) delayUs(1000);                
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

            case Ramp_Down:
                break;

            case Ramp_Up:
                break;

             case Finish:
                break;
          
          }
    }

    return 0;
       
}


/*void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    //Turns the flag down
    IFS0bits.AD1IF = 0;   
    
    //Buffer from Sensor 0 mayor de .600v 126-220, dentro fuera
    if (ADC1BUF0<=170) {S0=1;} 
    else {S0=0;}
     
    //Buffer from Sensor 1 mayor de .300 180-220, dentro fuera
    if (ADC1BUF1<=200) {S1=1;} 
    else {S1=0;}
    
    //Buffer from Sensor 2 mayor de .800, 150-270 dentro fuera
    if (ADC1BUF2<=210) {S2=1;} 
    else {S2=0;}
    
    //Buffer from Sensor 3 mayor de .600, 60-220 dentro fuera
    if (ADC1BUF3<=140) {S3=1;} 
    else {S3=0;}
    
    
    
    
    
     //State Selector
    if ((S1==1)&&(S2==1)){
        state=Forward;
        OC4RS = 800;
        OC2RS = 800;}
    else
    if (S3==1){
       state=Turn_Right;
       OC4RS = 800;
       OC2RS = 800;} 
    else
    if (S0==1){
        state=Turn_Left;
        OC4RS = 800;
        OC2RS = 800;}
   
        
    
    
    //Erase this 
    //OC4RS = 800;
    //OC2RS = 800;
    //End Erase this
    
    //Assign the correct values for the motor to work to the OCxRS variables.
    //OC2RS = ADC1BUF0+400;
    //if(ADC1BUF0 < 512) {OC4RS = 1023;}
    //else {OC4RS = ((-1023+ADC1BUF0)*(-1))+(400);}

    AD1CON1bits.ADON = 0;               //Turns off the ADC.
    //for (i = 0; i < 1000; i++) delayUs(1000);
}*/

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
      dummyVariable = PORTDbits.RD6;
    
      if (state == Idle) 
      {state = DebouncePress;}
      else
      if (state==WaitRelease) {
      state=DebounceRelease;}
    
     IFS1bits.CNDIF = 0;
         
}

