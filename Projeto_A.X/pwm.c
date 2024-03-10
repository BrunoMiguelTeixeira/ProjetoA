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

volatile struct listOC{
    volatile uint32_t *OCxCON;
    volatile uint32_t *OCxR;
    volatile uint32_t *OCxRS;
} OC[5] = {
    {&OC1CON, &OC1R, &OC1RS},
    {&OC2CON, &OC2R, &OC2RS},
    {&OC3CON, &OC3R, &OC3RS},
    {&OC4CON, &OC4R, &OC4RS},
    {&OC5CON, &OC5R, &OC5RS}
};

void ConfigDutyCycle(uint8_t ocSelect, uint8_t dutyCycle)
{
    OC[ocSelect - 1].OCxRS = ((timer2.PR + 1) * dutyCycle) / 100;
}

uint8_t ConfigPWM(uint8_t ocSelect, uint8_t timerSelect, uint8_t dutyCycle)
{
    struct TimerConfig timerSelected;

    if (ocSelect > 5){
        return 0x01;    // OC not available, Exception 1
    }
    if (dutyCycle > 100){
        return 0x02;    // Duty Cycle out of range, Exception 2
    }
    if (timerSelect > 3 && timerSelect < 2){
        return 0x03;    // Timer not available, Exception 3
    }

    OC[ocSelect - 1].OCxCON = 0;
    OC[ocSelect - 1].OCxR = 0;
    OC[ocSelect - 1].OCxRS = 0;

    /* if (timerSelected.timer32bit == 1){
        OC[ocSelect - 1].OCxCONbits.OC32 = 1;                              // 32-bit Timer source
    } */    

    /*  
        ON       = 1: Enable Output Compare
        FRZ      = 0: PWM continues in CPU Freeze mode
        SIDL     = 0
        [12:6]   = 000000
        OC32     = 0: 16-bit Timer source
        [3]      = 0
        OCTSEL   = 0: Timer 2 is the clock source for this OC
        OCM[2:0] = 110: PWM mode on OCx; Fault pin disabled
    */

    OC[ocSelect - 1].OCxRS = ((timer2.PR + 1) * dutyCycle) / 100;
    if (timerSelect == 2) { timerSelected = timer2; OC[ocSelect - 1].OCxCON = 0b1000000000000110;}
    if (timerSelect == 3) { timerSelected = timer3; OC[ocSelect - 1].OCxCON = 0b1000000000001110;}

    return 0x00;
};