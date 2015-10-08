/*
 * File:   lcd.c
 * Author: gvanhoy
 *
 * Created on December 31, 2014, 1:39 PM
 */

#include <xc.h>
#include "lcd.h"
#include "timer.h"

void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
}


void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){

}

void printCharLCD(char c) {
}

void initLCD(void) {
}

void printStringLCD(const char* s) {
}

void clearLCD(){
}

//X is down, Y is across.
void moveCursorLCD(unsigned char x, unsigned char y){
}

//made so that the LCD can be easily tested.
void testLCD(){
}