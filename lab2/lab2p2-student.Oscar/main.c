// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "config.h"
#include "interrupt.h"


#define ENABLED  1
#define DISABLED  0

typedef enum stateTypeEnum {
    Start, WaitPress, DebouncePress, WaitRelease, DebounceRelease, ROW1, ROW2, ROW3, ROW4, WriteLCD, COL1, COL2, COL3
} stateType;

volatile stateType state = Start;
volatile int Col, Row;
volatile int i=0;
char key='N';


unsigned int dummyVariable = 0;
unsigned int dummyVariable2 = 0;
unsigned int dummyVariable3 = 0;

int main(void) {

    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initTimer2();
    initLCD();
    clearLCD();
    initKeypad();
    
    while (1) {
        switch (state) {
            case Start:
                initLCD();
                clearLCD();
                state = ROW1;
                break;


            case ROW1:
                Row=1;
                //printCharLCD('1');
                LATGbits.LATG0 = DISABLED;
                LATFbits.LATF1 = DISABLED;
                LATDbits.LATD12 = DISABLED;
                LATGbits.LATG13 = ENABLED;                
                //delayUs2(70);
                state = ROW2;
                break;

            case ROW2:
                Row=2;
                //printCharLCD('2');
                LATDbits.LATD12 = DISABLED;
                LATFbits.LATF1 = DISABLED;
                LATGbits.LATG13 = DISABLED;
                LATGbits.LATG0 = ENABLED;
                //delayUs2(70);
                state = ROW3;
                break;

            case ROW3:
                Row=3;
                //printCharLCD('3');
                LATDbits.LATD12 = DISABLED;
                LATGbits.LATG13 = DISABLED;
                LATGbits.LATG0 = DISABLED;
                LATFbits.LATF1 = ENABLED;
                //delayUs2(70);
                state = ROW4;
                break;

            case ROW4:
                Row=4;
                LATGbits.LATG13 = DISABLED;
                LATGbits.LATG0 = DISABLED;
                LATFbits.LATF1 = DISABLED;
                LATDbits.LATD12 = ENABLED;
                //delayUs2(70);
                state = ROW1;
                break;

            case DebouncePress:
                delayUs2(700);
                state = WaitRelease;
                break;

            case WaitRelease:
                state = WaitRelease;
                break;

            case DebounceRelease:
                delayUs2(700);
                state = WriteLCD;
                break;

                
            case WriteLCD:       
                key=scanKeypad(Col, Row);
                printCharLCD(key);
                state = ROW1;
                break;
        }
    }

    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    //TODO: Implement the interrupt to capture the press of the button
    //char key;
      
      
    dummyVariable = PORTDbits.RD6; // change the value
    dummyVariable2 = PORTGbits.RG12;
    //dummyVariable2 = PORTDbits.RD5;
    dummyVariable3 = PORTDbits.RD9;
    
  
    IFS1bits.CNDIF = 0;
//    IFS1bits.CNBIF = 0;
    IFS1bits.CNGIF = 0;
 
    if (PORTDbits.RD6 == DISABLED) {
        Col = 1;} 
   
    if (PORTGbits.RG12 == DISABLED) {
        Col = 3;} 
    
    if (PORTDbits.RD9 == DISABLED) {
        Col = 2;}

    if ((state == ROW1) || (state == ROW2) || (state == ROW3) || (state == ROW4)) {
        state = DebouncePress;
    } 
    if (state == WaitRelease) {
        state = DebounceRelease;
    }

    if (i == 16) {
        moveCursorLCD(0, 2);
        
    }
    if (i >= 32) {
        moveCursorLCD(0, 0);
        i = 0;
    }
    i++;
}
