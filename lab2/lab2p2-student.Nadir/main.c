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
    Start, WaitPress, DebouncePress, WaitRelease, DebounceRelease, ROW1, ROW2, ROW3, ROW4, WriteLCD
} stateType;

volatile stateType state = Start;

unsigned int dummyVariable = 0;
unsigned int dummyVariable2 = 0;
unsigned int dummyVariable3 = 0;

int main(void) {

    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initTimer1();
    initTimer2();
    initLCD();
    clearLCD();

    while (1) {
        switch (state) {
            case Start:
                initLCD();
                clearLCD();
                state = ROW1;
                break;


            case ROW1:
                ODCGbits.ODCG13 = ENABLED;
                ODCDbits.ODCD12 = DISABLED;
                delayUs2(1000);
                state = ROW2;
                break;

            case ROW2:
                ODCGbits.ODCG0 = ENABLED;
                ODCGbits.ODCG13 = DISABLED;
                delayUs2(1000);
                state = ROW3;
                break;

            case ROW3:
                ODCFbits.ODCF1 = ENABLED;
                ODCGbits.ODCG0 = DISABLED;
                delayUs2(1000);
                state = ROW4;
                break;

            case ROW4:
                ODCDbits.ODCD12 = ENABLED;
                ODCFbits.ODCF1 = DISABLED;
                delayUs2(1000);
                state = ROW1;
                break;

            case DebouncePress:
                delayUs2(700);
                state = WaitRelease;
                break;

            case WaitRelease:
                delayUs2(700);
                state = WaitRelease;
                break;

            case DebounceRelease:
                delayUs2(700);
                state = WaitRelease;
                break;

            case WriteLCD:
                break;
        }
    }

    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    //TODO: Implement the interrupt to capture the press of the button
    char key;
    dummyVariable = PORTDbits.RD6 = 1;
    dummyVariable2 = PORTCbits.RC13 = 1;
    dummyVariable3 = PORTDbits.RD3 = 1;
    
   
 
        
    key=scanKeypad();
    printCharLCD(key);

   IFS1bits.CNDIF = 0;
   IFS1bits.CNCIF = 0;
}
