#include <xc.h>
#include <stdint.h>

#ifndef PWM_H
#define PWM_H

/**
 * PWM Configuration for OC1
 * 
 * Configures the PWM for the OC1 pin, by selecting the timer to be used and the duty cycle.
 *
 * @param timerSelect The timer to be used for the PWM;
 * @param dutyCycle The duty cycle for the PWM;
*/
uint8_t ConfigPWM1(uint8_t timerSelect, uint8_t dutyCycle);

/**
 * PWM Configuration for OC2
 * 
 * Configures the PWM for the OC2 pin, by selecting the timer to be used and the duty cycle.
 *
 * @param timerSelect The timer to be used for the PWM;
 * @param dutyCycle The duty cycle for the PWM;
*/
uint8_t ConfigPWM2(uint8_t timerSelect, uint8_t dutyCycle);

/**
 * PWM Configuration for OC3
 * 
 * Configures the PWM for the OC3 pin, by selecting the timer to be used and the duty cycle.
 *
 * @param timerSelect The timer to be used for the PWM;
 * @param dutyCycle The duty cycle for the PWM;
*/
uint8_t ConfigPWM3(uint8_t timerSelect, uint8_t dutyCycle);

/**
 * PWM Configuration for OC4
 * 
 * Configures the PWM for the OC4 pin, by selecting the timer to be used and the duty cycle.
 *
 * @param timerSelect The timer to be used for the PWM;
 * @param dutyCycle The duty cycle for the PWM;
*/
uint8_t ConfigPWM4(uint8_t timerSelect, uint8_t dutyCycle);

/**
 * PWM Configuration for OC5
 * 
 * Configures the PWM for the OC5 pin, by selecting the timer to be used and the duty cycle.
 *
 * @param timerSelect The timer to be used for the PWM;
 * @param dutyCycle The duty cycle for the PWM;
*/
uint8_t ConfigPWM5(uint8_t timerSelect, uint8_t dutyCycle);

void UpdatePWM(uint8_t timerSelect,uint8_t dutyCycle);
#endif	/* PWM_H */