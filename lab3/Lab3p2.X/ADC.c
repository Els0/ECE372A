/* 
 * File:   adc.c
 * Author: TEAM 206
 *
 * Created on 10/22/2015
 */

#include <xc.h>

void initADC(){
    
    ANSELBbits.ANSB0 = 0; 
    AD1CON1bits.FORM = 0;       // 16 unsigned integer
    AD1CON1bits.SSRC = 7;       // Auto-convert mode
    AD1CON1bits.ASAM = 1;       // Auto-sampling
    AD1CON2bits.VCFG = 0;       // Use board reference voltages
    AD1CON2bits.CSCNA = 0;      // Disable scanning
    AD1CON2bits.SMPI = 15;      // Interrupt at the 16th sample sequence
    AD1CON2bits.ALTS = 0;       // Only Mux A
    AD1CON3bits.ADRC = 0;       // Use PBCLK
    AD1CON3bits.SAMC = 31;      // 31 Tad per sample
    AD1CON3bits.ADCS = 0xFF;    // 512 times the PBCLK
    AD1CHSbits.CH0NA = 0;       // Use Vref- as negative reference
    AD1CHSbits.CH0SA = 0;       // Scan AN0 at least
    IFS0bits.AD1IF = 0;         // Turn off flag
    IEC0bits.AD1IE = 1;         // Set priority
    IPC5bits.AD1IP = 7;         // Set subpriority
    AD1CON1bits.ADON = 1;       // turn on the ADC
}

