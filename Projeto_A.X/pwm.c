#include "pwm.h"
#include "timer.h"
#include "sys_config.h"
#include <xc.h>
#include <stdint.h>

extern struct TimerConfig timer1;
extern struct TimerConfig timer2;
extern struct TimerConfig timer3;
extern struct TimerConfig timer4;
extern struct TimerConfig timer5;

uint8_t ConfigPWM(uint8_t dutyCycle)
{
    if (timer2.PR == 0)
    {
        // Timer not initialized, Exception 1
        return 0x01;
    }

    OC1CON = 0;
    if (timer2.timer32bit == 1){
        OC1CONbits.OC32 = 1;        // 32-bit Timer source
    }

    OC1RS = ((timer2.PR + 1) * dutyCycle) / 100;
    OC1CONbits.OCTSEL = 0;      // Timer2 is the clock source for this Output Compare module
    OC1CONbits.OCM = 0b110;     // PWM mode on OC1; Fault pin disabled
    OC1CONbits.ON = 1;          // Enable OC1 module 

    return 0x00;
};