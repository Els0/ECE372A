/* 
 * File:   timer.h
 * Author: TEAM 206
 *
 * Created on 10/22/2015
 */

#ifndef INITTIMER_H
#define	INITTIMER_H

//Timer 2 will be used for the PWM.
void initTimer2(); 
void delayUs2(unsigned int delay);

//Timer 1 will be used for all the other delays.
void initTimer1();
void delayUs(unsigned int delay);



#endif	/* INITTIMER_H */