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
    Start, WaitPress, DebouncePress, Increment, WaitRelease, DebounceRelease, ROW1, ROW2, ROW3, ROW4, WriteLCD, COL1, COL2, COL3
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
                initLCD();                  //Initialize the LCD
                clearLCD();                 //Clears the LCD
                state = ROW1;               //Goes to state ROW1
                break;

 //ROW1-ROW4 will be rotating until a key is pressed.
                
            case ROW1:
                Row=1;                      //Disable rows 2,3, and 4, but enables row 1.
                LATGbits.LATG0 = DISABLED;
                LATFbits.LATF1 = DISABLED;
                LATDbits.LATD12 = DISABLED;
                LATGbits.LATG13 = ENABLED;  
                state = ROW2;
                break;

            case ROW2:
                Row=2;                      //Disable rows 3,4, and 1, but enables row 2.
                LATDbits.LATD12 = DISABLED;
                LATFbits.LATF1 = DISABLED;
                LATGbits.LATG13 = DISABLED;
                LATGbits.LATG0 = ENABLED;
                state = ROW3;
                break;

            case ROW3:
                Row=3;                      //Disable rows 4,1, and 2, but enables row 3.
                LATDbits.LATD12 = DISABLED;
                LATGbits.LATG13 = DISABLED;
                LATGbits.LATG0 = DISABLED;
                LATFbits.LATF1 = ENABLED;
                state = ROW4;
                break;

            case ROW4:
                Row=4;                      //Disable rows 1,2, and 3, but enables row 4.
                LATGbits.LATG13 = DISABLED;
                LATGbits.LATG0 = DISABLED;
                LATFbits.LATF1 = DISABLED;
                LATDbits.LATD12 = ENABLED;
                state = ROW1;
                break;

            case DebouncePress:                     //A small delay is applied to prevent a debounce.
                delayUs2(1000);
                state = WaitRelease;               
                break;

            case WaitRelease:                       //Waits for a key to be pressed.
                state = WaitRelease;
                break;

            case DebounceRelease:                   //A small delay is applied to prevent a debounce.
                delayUs2(1000);
                state = Increment;
                break;

            case Increment:                         //Increments the i variable, this variable is used to
                i++;                                //keep track of the cursor position, so it can be moved
                state = WriteLCD;                   //to row two when needed
                break;
                
            case WriteLCD:                          //Calls the function scanKeypad(); which returns a value 
                key=scanKeypad(Col, Row);           //to be printed by the function printCharaLCD();
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
      
      
    dummyVariable = PORTDbits.RD6;      // change the value
    dummyVariable2 = PORTCbits.RC13;
    dummyVariable3 = PORTDbits.RD3;
    
  
    IFS1bits.CNDIF = 0;               //Turns OFF the flags
    IFS1bits.CNCIF = 0;
    
 //Depending on the key that was pressed, these if statements will
 //give a value to the Col variable, this is then used by the function scanKeypad();
    if (PORTDbits.RD6 == DISABLED) {        
        Col=1;}                             
    
    if (PORTCbits.RC13 == DISABLED) {
        Col=2;}
    
    if (PORTDbits.RD3 == DISABLED) {
        Col = 3;}

    
    //If the state was in ROW1, ROW2, ROW3, or ROW4, the next state will be DebouncePress.
    if ((state == ROW1) || (state == ROW2) || (state == ROW3) || (state == ROW4)) {
        state = DebouncePress;
    } 
    //If the state was in WaitRelease, the next state will be DebounceRelease.
    if (state == WaitRelease) {
        state = DebounceRelease;
    }

    //When 8 characters are printed on the LCD, the cursor will be moved to position 0 of row 2, 
    //when 16 are printed, the cursor will move to position 0 of row 1, and the variable will be assigned the value 0.
    if (i == 8) {
        moveCursorLCD(0, 2);
        
    }
    if (i >= 16) {
        moveCursorLCD(0, 0);
        i = 0;
    }
}
