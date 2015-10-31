/*
 * File:   lcd.c
 * Author: TEAM 206
 *
 * Created on 10/22/2015
 */


#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define LCD_D4  LATEbits.LATE7  // LCD_ D4 = LATEbits and are use for the pins
#define LCD_D5  LATEbits.LATE5  //
#define LCD_D6  LATEbits.LATE3  //
#define LCD_D7  LATEbits.LATE1  //
#define LCD_RS  LATCbits.LATC4 //
#define LCD_E   LATCbits.LATC2  //**************************

#define TRIS_D7 TRISEbits.TRISE1      // Set them as an output
#define TRIS_D6 TRISEbits.TRISE3      //
#define TRIS_D5 TRISEbits.TRISE5      //
#define TRIS_D4 TRISEbits.TRISE7      //
#define TRIS_RS TRISCbits.TRISC4     //
#define TRIS_E  TRISCbits.TRISC2      //***********************

#define INPUT   1
#define OUTPUT  0

void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower) {
    //TODO:

    if (lower == 1) { // deciding to sent the 4 first bits

        LCD_D4 = (word & 0x01); //D4 sending the first 4 bits of the word(1 byte = 8 bits)
        LCD_D5 = ((word & 0x02) >> 1); //D5
        LCD_D6 = ((word & 0x04) >> 2); //D6
        LCD_D7 = ((word & 0x08) >> 3); //D7 ****************************


    } else {

        LCD_D4 = ((word & 0x10) >> 4); //D4 sending the rest 4 bits of the word(1 byte = 8 bits)
        LCD_D5 = ((word & 0x20) >> 5); //D5
        LCD_D6 = ((word & 0x40) >> 6); //D6
        LCD_D7 = ((word & 0x80) >> 7); //D7 *******************************

    }
    LCD_RS = commandType; //commandType = 1 OR 0 look at Data Sheet
    delayUs(1);
    LCD_E = 1;
    delayUs(1);
    LCD_E = 0;
    delayUs(delayAfter);
}

void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter) {

    writeFourBits(word, commandType, 1, 0); //Sending the uppper bits
    writeFourBits(word, commandType, delayAfter, 1); //Sending the lower bits


}

void printCharLCD(char c) {

    writeLCD(c, 1, 40); //Using writeLCD function to print a c into the LCD
}

void initLCD(void) {

    TRIS_D7 = OUTPUT; //Setting the ports to OUTPUTs
    TRIS_D6 = OUTPUT; //
    TRIS_D5 = OUTPUT; //
    TRIS_D4 = OUTPUT; //
    TRIS_RS = OUTPUT; //
    TRIS_E = OUTPUT; // ************************

    int i = 0; // Loop needed to make a delay of 1.64 ms
    for (i = 0; i < 100; i++) { //
        delayUs(150); //***********************
    }
    // writeFourBits & writeLCD are need to initialize look at LCD Data Sheet

    writeFourBits(0x30, 0, 4100, 0);
    writeFourBits(0x30, 0, 100, 0);
    writeLCD(0x32, 0, 40);
    writeLCD(0x28, 0, 40);
    writeLCD(0x08, 0, 40);
    writeLCD(0x01, 0, 1640);
    writeLCD(0x06, 0, 40);
    writeLCD(0x0E, 0, 40);
}

void printStringLCD(const char* s) {
    //Loop printing the first 8 bits of the char *s
    int i = 0;
    for (i = 0; i < strlen(s); i++)
        printCharLCD(s[i]);
}

void clearLCD() {

    writeLCD(0x01, 0, 1640); // command use to clear the LCD
}

void moveCursorLCD(unsigned char x, unsigned char y) {

    if (y == 0) // LCD has to row: Row 0 and Row 1
        y = 0;  //When y== 0, but the y=0 to use the first row
    else
        y = 0x40; // if y!=0 then it equals 1; giving the value of 4 with is needed to use the second row (Data Sheet)
    writeLCD(0x80 + x + y, 0, 46); //using writeLCD function to move the crusor in the LCD
}

void testLCD() {
    int i = 0;
    printCharLCD('c');
    for (i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    for (i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for (i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for (i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
}