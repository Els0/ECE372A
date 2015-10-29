/* 
 * File:   PWM.c
 * Author: TEAM 206
 *
 * Created on October 8, 2015, 9:14 AM
 */

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define In1  TRISGbits.TRISG13       // 
#define In2  TRISGbits.TRISG0        //
#define In3  TRISFbits.TRISF1        // 
#define In4  TRISDbits.TRISD12       //

void initHBridgeInputs(){
    

    In1 = OUTPUT; //
    In2 = OUTPUT; //
    In3 = OUTPUT; //  
    In4 = OUTPUT; //

}        

void ToggleMode(int CurrentState){

    switch (CurrentState) {
        case 1: //Idle
            //Motor 1
            LATGbits.LATG13 = 0;
            LATGbits.LATG0 = 0;
            //Motor 2
            LATFbits.LATF1 = 0;
            LATDbits.LATD12 = 0;
            break;

        case 2: //Forward
            //Motor 1
            LATGbits.LATG13 = 1;
            LATGbits.LATG0 = 0;
            //Motor 2
            LATFbits.LATF1 = 1;
            LATDbits.LATD12 = 0;
            break;

        case 3: //Backward
            //Motor 1
            LATGbits.LATG13 = 0;
            LATGbits.LATG0 = 1;
            //Motor 2
            LATFbits.LATF1 = 0;
            LATDbits.LATD12 = 1;
            break;
    }
    
}

void initPWM(){
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
    OC2CON = 0x0000; // Turn off OC2 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONSET = 0x8000; // Enable OC2
}

void initPWM2(){
    RPD3Rbits.RPD3R = 0b1011; // map OC2 to RD1
    OC4CON = 0x0000; // Turn off OC4 while doing setup.
    OC4R = 0x0000; // Initialize primary Compare Register
    OC4RS = 0x0000; // Initialize secondary Compare Register
    OC4CON = 0x0006; // Configure for PWM mode
    OC4CONSET = 0x8000; // Enable OC4
}