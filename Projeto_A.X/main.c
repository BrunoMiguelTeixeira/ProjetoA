#include "config_bits.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "pwm.h"
#include "sys_config.h"
#include <sys/attribs.h>
#include <xc.h>
#include <stdio.h>


volatile float val = 2;

void __ISR (_TIMER_3_VECTOR, IPL6SRS) T3Interrupt(void)
{
    ADC_start();
    while(ADC_IF() == 0);
    val = ADC_read();
    PutFloat(val,4);
    PutChar('\r');
    PutChar('\n');
    ClearIntFlagTimer3();
}

void __ISR (_TIMER_2_VECTOR, IPL5SRS) T2Interrupt(void)
{
    int pwm = (val/3.3)*100;
    ConfigPWM(pwm);
    PutInt(pwm);
    PutChar('\r');
    PutChar('\n');
    ClearIntFlagTimer2();
}


int main(void){
    //PORTS
    //PutStringn("Hello");
    TRISASET = 0x0008; //LED for UART
    
    // Config Digital Pin 2 as output
    TRISEbits.TRISE8 = 0;       // Set Digital Pin 2
    LATEbits.LATE8 = 0;         // Turn off Digital Pin 2
    
    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK;
    
    /* Enable Interrupt Exceptions */
    // set the CP0 status IE bit high to turn on interrupts globally
    __builtin_enable_interrupts();
    
    //SETUP UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
    //SETUP ADC
    ADC_init();
   
    while(ADC_input(ADC_CHAN) == -1){
        PutChar('T');
    }
    
    ADC_enable();
    
    //SETUP TIMERS
    ConfigTimer3(SAMPL_FREQ_HZ,1);      // Input
    ConfigTimer2(PWM_FREQ_HZ,1,0);      // Output      
    
    // STARTUP TIMER
    StartTimer2();
    StartTimer3();
    PutInt(timer3.PR);
    PutChar('\r');
    PutChar('\n');

    // Variables
    while(1);
    /*
    while(1){
        while(GetIntFlagTimer2() == 0){}
        ClearIntFlagTimer2();
        LATEbits.LATE8 = !LATEbits.LATE8;     // Toggle Digital Pin 2
        PutChar('+');
    };
    while(1){
        while(GetIntFlagTimer2() == 0){};
        ADC_start();
        while(ADC_IF() == 0);
        ClearIntFlagTimer2();
        val=ADC_read();
        PutFloat(val,2);
        PutChar('\r');
        PutChar('\n');
    }*/
    return 0;
}