/* 
 * File:   switch.c
 * Author: oscarmoralesvera
 *
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0
#define S_ON 1
#define S_OFF 0

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;  //Configure digital input
    CNPUDbits.CNPUD6 = S_ON;   //Pull up resistor
}