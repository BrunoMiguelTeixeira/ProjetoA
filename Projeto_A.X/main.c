#include "config_bits.h"
#include "uart.h"
#include "adc.h"
#include "sys_config.h"
#include <xc.h>
#include <stdio.h>

#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

int main(void){
    //PORTS
    TRISASET=0x0008; //LED for UART
    
    //SETUP UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
    //SETUP ADC
    ADC_init();
   
    while(ADC_input(ADC_CHAN)==-1){
        PutChar('T');
    }
    
    ADC_enable();
    
    //SETUP TIMERS
    
    //SETUP PWM
    
    //Variabels
    float val=0;
    
    while(1){
        IFS1bits.AD1IF = 0; // Reset interrupt flag
        AD1CON1bits.ASAM = 1; // Start conversion
        while (IFS1bits.AD1IF == 0); // Wait fo EOC
        val=ADC_read();
        //printf("%f\r\n",val);
        PutFloat(val);
        PutChar('\r');
        PutChar('\n');
    }
    return 0;
}