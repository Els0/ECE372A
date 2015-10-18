#include <xc.h>
#include "keypad.h"
#include "timer.h"

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */

/*
#define LCD_D4  LATEbits.LATE7  // LCD_ D4 = LATEbits and are use for the pins
#define LCD_D5  LATEbits.LATE5  //
#define LCD_D6  LATEbits.LATE3  //
#define LCD_D7  LATEbits.LATE1  //
#define LCD_RS  LATCbits.LATC4 //
#define LCD_E   LATCbits.LATC2  //**************************
*/

#define ROW1  TRISGbits.TRISG13       // Set them as an output
#define ROW2  TRISGbits.TRISG0        //
#define ROW3  TRISFbits.TRISF1        // ODC
#define ROW4  TRISDbits.TRISD12       //

#define COL1  TRISDbits.TRISD6        //Set them as inputs
#define COL2  TRISGbits.TRISG12       //
#define COL3  TRISDbits.TRISD9        // PULL UP RESISTORS

#define ODC1 ODCGbits.ODCG13   //Disable the ODC at the outputs.
#define ODC2 ODCGbits.ODCG0 
#define ODC3 ODCFbits.ODCF1 
#define ODC4 ODCDbits.ODCD12 

#define INPUT   1
#define OUTPUT  0

#define ENABLED  1
#define DISABLED  0

void initKeypad(void) {

    ROW1 = OUTPUT; //Setting the ports to OUTPUTs.
    ROW2 = OUTPUT; //
    ROW3 = OUTPUT; //  ODC
    ROW4 = OUTPUT; //

    COL1 = INPUT; // Setting the ports to INPUTs.
    COL2 = INPUT; //  PULL UP RESISTORS
    COL3 = INPUT; //

    //ANSELBbits.ANSB12=0;// to change to digital
     
    CNCONDbits.ON = 1;                  // Enable overall interrupt
//    CNCONBbits.ON = 1;                  // Enable overall interrupt
    CNCONGbits.ON = 1;                  // Enable overall interrupt

    CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
    CNENDbits.CNIED9 = ENABLED;
    CNENGbits.CNIEG12 = ENABLED;
   
    IFS1bits.CNDIF = 0;                 // Put down the flag
//    IFS1bits.CNBIF = 0;                 // Put down the flag
    IFS1bits.CNGIF = 0;                 // Put down the flag

    IPC8bits.CNIP = 7;                  // Configure interrupt priority
    IEC1bits.CNDIE = ENABLED;
    IEC1bits.CNGIE = ENABLED;
//    IEC1bits.CNBIE = ENABLED;           //CN enable all above
   
    ODCGbits.ODCG13 = ENABLED;   //Enable the ODC at the outputs.
    ODCGbits.ODCG0 =  ENABLED;
    ODCFbits.ODCF1 =  ENABLED;
    ODCDbits.ODCD12 = ENABLED;
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(int Colk, int Rowk){
    char key = -1;
    int Col = Colk;
    int Row = Rowk;
    
    if (Row == 2) {
        if (Col==1){
            key='1'; 
            return key;}
        if (Col==2){
            key='2'; 
            return key;}
        if (Col==3){
            key='3'; 
            return key;}
    }
  
    if (Row == 3) {
        if (Col==1){
            key='4'; 
            return key;}
        if (Col==2){
            key='5'; 
            return key;}
        if (Col==3){
            key='6'; 
            return key;}
    }
   
    if (Row == 4) {
        if (Col==1){
            key='7'; 
            return key;}
        if (Col==2){
            key='8'; 
            return key;}
        if (Col==3){
            key='9'; 
            return key;}
    }
    
   if (Row == 1) {
        if (Col==1){
            key='*'; 
            return key;}
        if (Col==2){
            key='0'; 
            return key;}
        if (Col==3){
            key='#'; 
            return key;}
    }

    return key;
}

