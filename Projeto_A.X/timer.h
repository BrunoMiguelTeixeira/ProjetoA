#include <xc.h>
#include <stdint.h>

#ifndef TIMER_H
#define TIMER_H

/*  --------- Configure Timer Function --------- 
        fout = 2
        Kprescaler = 20*10^6 / ((65535+1)*fout) = 153 
        Prescaler mais próximo -> 256
        fout_presc = 20*10^6 / 256 = 78125
        PR2 = (78125 / 2) - 1 = 39061.5 -> 39062
    -------------------------------------------- */
/* 
    T1CON = 0;                  // Clear Timer 1 configuration
    T1CONbits.TCKPS = 3;        // 1:256 prescaler
    PR1 = 31250;                // 1Hz frequency
    TMR1 = 0;                   // Clear Timer 1 counter
    IFS0bits.T1IF = 0;          // Clear Timer 1 interrupt flag
    IEC0bits.T1IE = 1;          // Enable Timer 1 interrupt
    T1CONbits.ON = 1;           // Turn on Timer 1 */

struct TimerConfig{
    uint16_t prescaler;
    uint32_t targetFreq;
    uint32_t PR;
    uint8_t interrupt;
    uint8_t timer32bit;
}; 

extern struct TimerConfig timer1;
extern struct TimerConfig timer2;
extern struct TimerConfig timer3;
extern struct TimerConfig timer4; 
extern struct TimerConfig timer5;

void ConfigTimer1(uint32_t targetFreq, uint8_t interrupt);
void ConfigTimer2(uint32_t targetFreq, uint8_t interrupt, uint8_t timer32bit);
void ConfigTimer3(uint32_t targetFreq, uint8_t interrupt);
void ConfigTimer4(uint32_t targetFreq, uint8_t interrupt, uint8_t timer32bit);
void ConfigTimer5(uint32_t targetFreq, uint8_t interrupt);

void StartTimer1();
void StartTimer2();
void StartTimer3();
void StartTimer4();
void StartTimer5();

void StopTimer1();
void StopTimer2();
void StopTimer3();
void StopTimer4();
void StopTimer5();

uint8_t GetIntFlagTimer1();
uint8_t GetIntFlagTimer2();
uint8_t GetIntFlagTimer3();
uint8_t GetIntFlagTimer4();
uint8_t GetIntFlagTimer5();

void ClearIntFlagTimer1();
void ClearIntFlagTimer2();
void ClearIntFlagTimer3();
void ClearIntFlagTimer4();
void ClearIntFlagTimer5();

struct TimerConfig GetTimer1Config();
struct TimerConfig GetTimer2Config();
struct TimerConfig GetTimer3Config();
struct TimerConfig GetTimer4Config();
struct TimerConfig GetTimer5Config();


#endif // TIMER_H