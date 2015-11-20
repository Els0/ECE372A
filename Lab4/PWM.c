/* 
 * File:   pwm.c
 * Author: TEAM 206
 *
 * Created on October 22, 2015
 */

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

//OC2  Motor 1
#define In1  TRISDbits.TRISD1        
#define In2  TRISDbits.TRISD5       

//OC4  Motor 2
#define In3  TRISDbits.TRISD3        
#define In4  TRISDbits.TRISD11      

void initHBridgeInputs(){
    

    In1 = OUTPUT; //
    In2 = OUTPUT; //
    In3 = OUTPUT; //  
    In4 = OUTPUT; //

}        

void ToggleMode(int CurrentState){

    switch (CurrentState) {
        case 1: //Idle
            
            In1 = OUTPUT;
            In2 = OUTPUT;
            In3 = OUTPUT;
            In4 = OUTPUT;
            
            LATDbits.LATD1 = 0;
            LATDbits.LATD5 = 0;
            LATDbits.LATD3 = 0;
            LATDbits.LATD11 = 0;
            //Motor 1
            RPD5Rbits.RPD5R = 0b0000;
            RPD1Rbits.RPD1R = 0b0000;
            //Motor 2
            RPD11Rbits.RPD11R = 0b0000;
            RPD3Rbits.RPD3R = 0b0000;
            break;

        case 2: //Forward
            In1 = OUTPUT;
            In2 = OUTPUT;
            In3 = OUTPUT;
            In4 = OUTPUT;
            //Motor 1
            RPD5Rbits.RPD5R = 0b0000;
            RPD1Rbits.RPD1R = 0b1011;
            //Motor 2
            RPD11Rbits.RPD11R = 0b0000;
            RPD3Rbits.RPD3R = 0b1011;
            
            break;

        case 3: //Backward
            In1 = OUTPUT;
            In2 = OUTPUT;
            In3 = OUTPUT;
            In4 = OUTPUT;
            //Motor 1
            RPD1Rbits.RPD1R = 0b0000;
            RPD5Rbits.RPD5R = 0b1011;
            //Motor 2
            RPD3Rbits.RPD3R = 0b0000;
            RPD11Rbits.RPD11R = 0b1011;
            break;
            
            case 4: //Turn_Right
            In1 = OUTPUT;
            In2 = OUTPUT;
            In3 = OUTPUT;
            In4 = OUTPUT;
            //Motor 1
            RPD5Rbits.RPD5R = 0b0000;
            RPD1Rbits.RPD1R = 0b1011;
            //Motor 2
            RPD3Rbits.RPD3R = 0b0000;
            RPD11Rbits.RPD11R = 0b1011;
            break;
            
            case 5: //Turn_Left
            In1 = OUTPUT;
            In2 = OUTPUT;
            In3 = OUTPUT;
            In4 = OUTPUT;
            //Motor 1
            RPD1Rbits.RPD1R = 0b0000;
            RPD5Rbits.RPD5R = 0b1011;
            //Motor 2
            RPD11Rbits.RPD11R = 0b0000;
            RPD3Rbits.RPD3R = 0b1011;
            break;
    }
    
}

void initPWM(){
    OC2CON = 0x0000; // Turn off OC2 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONSET = 0x8000; // Enable OC2
}

void initPWM2(){
    OC4CON = 0x0000; // Turn off OC4 while doing setup.
    OC4R = 0x0000; // Initialize primary Compare Register
    OC4RS = 0x0000; // Initialize secondary Compare Register
    OC4CON = 0x0006; // Configure for PWM mode
    OC4CONSET = 0x8000; // Enable OC4
}