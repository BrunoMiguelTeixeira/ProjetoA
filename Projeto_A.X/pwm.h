#include <xc.h>
#include <stdint.h>

#ifndef PWM_H
#define PWM_H

// Array for each OC module, that includes the necessary registers
extern struct listOC;

/**
 * PWM Configuration for OC1
 * 
 * Configures the PWM for the OC1 pin, by selecting the timer to be used and the duty cycle.
 *
 * @param timerSelect The timer to be used for the PWM;
 * @param dutyCycle The duty cycle for the PWM;
*/
uint8_t ConfigPWM(uint8_t ocSelect, uint8_t timerSelect, uint8_t dutyCycle);

void ConfigDutyCycle(uint8_t ocSelect, uint8_t dutyCycle);

#endif	/* PWM_H */