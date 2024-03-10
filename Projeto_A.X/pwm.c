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

uint8_t ConfigPWM1(uint8_t timerSelect, uint8_t dutyCycle)
{
    struct TimerConfig timerSelected;
    if (timerSelect == 2)         { timerSelected = timer2; OC1CONbits.OCTSEL = 0; }
    else if (timerSelect == 3)    { timerSelected = timer3; OC1CONbits.OCTSEL = 1;}
    else{
        return 0x02;    // Timer not available, Exception 2
    }
    if (timerSelected.PR == 0){
        return 0x01;    // Timer not initialized, Exception 1
    }

    OC1CON = 0;
    if (timerSelected.timer32bit == 1){
        OC1CONbits.OC32 = 1;        // 32-bit Timer source
    }

    OC1RS = ((timerSelected.PR + 1) * dutyCycle) / 100;
    OC1CONbits.OCM = 0b110;     // PWM mode on OC1; Fault pin disabled
    OC1CONbits.ON = 1;          // Enable OC1 module 
    // Start PWM generation
    T2CONbits.TON=1; // Start the timer
    return 0x00;
};
void UpdatePWM(uint8_t timerSelect,uint8_t dutyCycle){
    struct TimerConfig timerSelected;
    timerSelected = timer2;
    OC1RS = ((timerSelected.PR + 1) * dutyCycle) / 100;
}

uint8_t ConfigPWM2(uint8_t timerSelect, uint8_t dutyCycle)
{
    struct TimerConfig timerSelected;
    if (timerSelect == 2)         { timerSelected = timer2; OC2CONbits.OCTSEL = 0; }
    else if (timerSelect == 3)    { timerSelected = timer3; OC2CONbits.OCTSEL = 1;}
    else{
        return 0x02;    // Timer not available, Exception 2
    }
    if (timerSelected.PR == 0){
        return 0x01;    // Timer not initialized, Exception 1
    }

    OC2CON = 0;
    if (timerSelected.timer32bit == 1){
        OC2CONbits.OC32 = 1;        // 32-bit Timer source
    }

    OC2RS = ((timerSelected.PR + 1) * dutyCycle) / 100;
    OC2CONbits.OCM = 0b110;     // PWM mode on OC2; Fault pin disabled
    OC2CONbits.ON = 1;          // Enable OC2 module 

    return 0x00;
};

uint8_t ConfigPWM3(uint8_t timerSelect, uint8_t dutyCycle)
{
    struct TimerConfig timerSelected;
    if (timerSelect == 2)         { timerSelected = timer2; OC3CONbits.OCTSEL = 0; }
    else if (timerSelect == 3)    { timerSelected = timer3; OC3CONbits.OCTSEL = 1;}
    else{
        return 0x02;    // Timer not available, Exception 2
    }
    if (timerSelected.PR == 0){
        return 0x01;    // Timer not initialized, Exception 1
    }

    OC3CON = 0;
    if (timerSelected.timer32bit == 1){
        OC3CONbits.OC32 = 1;        // 32-bit Timer source
    }

    OC3RS = ((timerSelected.PR + 1) * dutyCycle) / 100;
    OC3CONbits.OCM = 0b110;     // PWM mode on OC3; Fault pin disabled
    OC3CONbits.ON = 1;          // Enable OC3 module 

    return 0x00;
};

uint8_t ConfigPWM4(uint8_t timerSelect, uint8_t dutyCycle)
{
    struct TimerConfig timerSelected;
    if (timerSelect == 2)         { timerSelected = timer2; OC4CONbits.OCTSEL = 0; }
    else if (timerSelect == 3)    { timerSelected = timer3; OC4CONbits.OCTSEL = 1;}
    else{
        return 0x02;    // Timer not available, Exception 2
    }
    if (timerSelected.PR == 0){
        return 0x01;    // Timer not initialized, Exception 1
    }

    OC4CON = 0;
    if (timerSelected.timer32bit == 1){
        OC4CONbits.OC32 = 1;        // 32-bit Timer source
    }

    OC4RS = ((timerSelected.PR + 1) * dutyCycle) / 100;
    OC4CONbits.OCM = 0b110;     // PWM mode on OC4; Fault pin disabled
    OC4CONbits.ON = 1;          // Enable OC4 module 

    return 0x00;
};

uint8_t ConfigPWM5(uint8_t timerSelect, uint8_t dutyCycle)
{
    struct TimerConfig timerSelected;
    if (timerSelect == 2)         { timerSelected = timer2; OC5CONbits.OCTSEL = 0; }
    else if (timerSelect == 3)    { timerSelected = timer3; OC5CONbits.OCTSEL = 1;}
    else{
        return 0x02;    // Timer not available, Exception 2
    }
    if (timerSelected.PR == 0){
        return 0x01;    // Timer not initialized, Exception 1
    }

    OC5CON = 0;
    if (timerSelected.timer32bit == 1){
        OC5CONbits.OC32 = 1;        // 32-bit Timer source
    }

    OC5RS = ((timerSelected.PR + 1) * dutyCycle) / 100;
    OC5CONbits.OCM = 0b110;     // PWM mode on OC5; Fault pin disabled
    OC5CONbits.ON = 1;          // Enable OC5 module 

    return 0x00;
};
