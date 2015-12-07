 /* 
 * File:   UltrasonicSensor.c
 * Author: TEAM 206
 *
 * Created on October 22, 2015
 */

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

//Signal Pin - J11-30 (RB4)
#define Signal TRISBbits.TRISB4             
     

void InitSensor(){
    Signal = OUTPUT;
    LATBbits.LATB4 = 0;
    TRISDbits.TRISD2 = OUTPUT;  // Sets the pin as an output
    
}

void ReadSensor(){
    int duration=0;
    int cm=0;
    Signal = OUTPUT; //Set Pin as an output
    LATBbits.LATB4 = 0; //Write a digital 0 to the pin to initialize the sensor
    delayUs(2);
    LATBbits.LATB4 = 1; //Write a digital 1 to the pin to initialize the sensor
    delayUs(3); //Wait for (aprox) 5 microseconds before turning the pin low
    LATBbits.LATB4 = 0; //Turns the pin low to a digital 0
    Signal = INPUT; // Sets the pin as an input to read the pulse from the Sensor
    //while (Signal == 0) {}
    T4CONbits.ON = 1; //Initiates the timer4
    delayUs(2);
    //while (Signal == 1) {}
    duration = TMR4;
    IFS0bits.AD1IF = 0;  //Turns the flag off
    T4CONbits.ON = 0;    //Turns the timer off
    
    TMR4 = 0;               //Clear TMR4
    duration = duration / 1000;
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    // cm = duration / 29 / 2, equals cm = duration / 58;
    cm = duration / 58;
    if (cm <= 30) {LATDbits.LATD2 = 1;}         // Turns the led ON
    else { LATDbits.LATD2 = 0;         // Turns the led OFF}
    }}