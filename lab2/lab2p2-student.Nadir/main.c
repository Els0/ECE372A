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
char key='N';


unsigned int dummyVariable = 0;
unsigned int dummyVariable2 = 0;
unsigned int dummyVariable3 = 0;

int main(void) {

    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
   // initTimer1();
    initTimer2();
    initLCD();
    clearLCD();
    initKeypad();

    while (1) {
        switch (state) {
            case Start:
                initLCD();
                //testLCD();
                clearLCD();
                //printCharLCD("N");
                state = ROW1;
                break;


            case ROW1:
                Row=1;
                //printCharLCD('1');
                LATDbits.LATD12 = DISABLED;
                LATGbits.LATG13 = ENABLED;                
                delayUs2(1000);
                state = ROW2;
                break;

            case ROW2:
                Row=2;
                //printCharLCD('2');
                LATGbits.LATG13 = DISABLED;
                LATGbits.LATG0 = ENABLED;
                delayUs2(1000);
                state = ROW3;
                break;

            case ROW3:
                Row=3;
                //printCharLCD('3');
                LATGbits.LATG0 = DISABLED;
                LATFbits.LATF1 = ENABLED;
                delayUs2(1000);
                state = ROW4;
                break;

            case ROW4:
                Row=4;
                //printCharLCD('4');
                LATFbits.LATF1 = DISABLED;
                LATDbits.LATD12 = ENABLED;
                delayUs2(1000);
                state = ROW1;
                break;

            case DebouncePress:
                delayUs2(700);
                 printCharLCD('D');
                  printCharLCD('P');
                state = WaitRelease;
                break;

            case WaitRelease:
                 printCharLCD('W');
                  printCharLCD('R');
                state = WaitRelease;
                break;

            case DebounceRelease:
                delayUs2(700);
                 printCharLCD('D');
                  printCharLCD('R');
                state = WriteLCD;
                break;

                
            case WriteLCD:
                 printCharLCD('P');
                  printCharLCD('R');
                   printCharLCD('I');
                    printCharLCD('N');
                     printCharLCD('T');
                    
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
    
    state = DebouncePress;
    
    dummyVariable = PORTDbits.RD6 = 1; // change the value
    dummyVariable2 = PORTCbits.RC13 = 1;
    dummyVariable3 = PORTDbits.RD3 = 1;
    printCharLCD('I');
    //printCharLCD('S');
    //printCharLCD('R');
    IFS1bits.CNDIF = 0;
    IFS1bits.CNCIF = 0;
    
    if (PORTDbits.RD6 == ENABLED) {
        Col=1;}
    else 
    if (PORTCbits.RC13 == ENABLED) {
        Col=2;}
    else
        if (PORTDbits.RD3 == ENABLED) {
        Col = 3;
    }

    if ((state == ROW1) || (state == ROW2) || (state == ROW3) || (state == ROW4)) {
        state = DebouncePress;
    } else
        if (state == WaitRelease)
        {
        state = DebounceRelease;
    }
    
   
   
    //key=scanKeypad();
    //printCharLCD(key);

 
}
