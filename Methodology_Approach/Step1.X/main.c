/* 
 * File:   CKTimerPool
 * Author: Paulo Pedreiras
 *
 * Created on Jan 28, 2019
 * MPLAB X IDE v5.10 + XC32 v2.15
 *
 * Target: Digilent chipKIT MAx32 board 
 * Configurations:
 *      HSPLL; CPUCLK=80MHz, PBCLCK=40MHz; Watchdog timer disabled
 *      
 * Overview:
 *     Blinks led connected on port RA3 with a pace measured via timer 2 (pool mode)
 *     Port D5 is set as open drain and changes state at the same rate (useful e.g. for 3.3V-5V interface)
 *          *** Don't forget to use a pull-up resistor on this port ***
 *     Also illustrates how stdout can be redirected to the UART  
 *      
 *
 *  Revisions:
 *      2018-02-19: Initial release
 *      2019-01-28: Updated to MPLAB X IDE v5.10 + XC32 v2.15
 *      2023-03-02: Updated for XC 4.21 (added heap and removed legacy libc support).
 */

#include "../CKCommon/ConfigBits/config_bits.h" // NOTE!! Must precede project file includes

#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CKCommon/UART/uart.h" 

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

/*
 * 
 */
int main(int argc, char** argv) {

    // Set RA3 and D5 ports
    TRISAbits.TRISA3 = 0;  // A3 as output
    TRISDbits.TRISD5 = 0; // D5 a output
    ODCDbits.ODCD5 = 1; // D5 as open-drain

    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
      // Set timer
    T2CONbits.ON = 0; // Stop timer
    IFS0bits.T2IF=0; // Reset interrupt flag
    IPC2bits.T2IP=5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration ***
    IEC0bits.T2IE = 0; // Enable T2 interrupts
    // Timer period configuration
    T2CONbits.TCKPS = 7; //Divide by 256 pre-scaler
    T2CONbits.T32 = 0; // 16 bit timer operation
    PR2=0xFFFF; // Period set to approx 0.42 secs (40MHz/256 = 156kHz; 1/156k*65000 ~ 0.41)
    TMR2=0;
    
    T2CONbits.TON=1; // Start the timer
    
    // Loop
    while (1) {
         // Wait for timer interrupt flag
        while(IFS0bits.T2IF==0);

        // Reset int flag
        IFS0bits.T2IF=0;
    
        // Toggle output and signal event via UART
        PORTAbits.RA3 = !PORTAbits.RA3;
        PutChar('T');
    }

    
    
    
    return (EXIT_SUCCESS);
}