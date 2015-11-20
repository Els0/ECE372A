/* 
 * File:   pwm.h
 * Author: gvanhoy
 *
 * Created on October 8, 2015, 9:14 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void initPWM();
void initPWM2();
void initHBridgeInputs();
void ToggleMode(int CurrentState);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */