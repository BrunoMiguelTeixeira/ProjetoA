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
    ClearIntFlagTimer3();
}

void __ISR (_TIMER_2_VECTOR, IPL5SRS) T2Interrupt(void)
{
    int pwm = (val/3.3)*100;
    ConfigPWM1(2,pwm);
    ClearIntFlagTimer2();
}


int main(void){
    //TRIS
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
    //StartTimer2();
    //StartTimer3();
    // Variables
    uint8_t choice=0;
    uint8_t memchoice=-1;
    uint8_t catcher;
    uint8_t menu=1;
    uint8_t wait;
    int total;
    while(1)
    {
        switch(choice){
            case 0:     //MAIN MENU
                if (memchoice!=0){
                    printf("\e[1;1H\e[2J");                     //Clear screen.
                    PutStringn("MENU:");
                    PutStringn("1-Change OC channel;");
                    PutStringn("2-Change ADC channel;");
                    nPutString("OPTION: ");
                    memchoice=0;
                    menu=0;
                    choice=99;
                    break;
                }
                else{
                    if(val<3 && val>0 ){            //Make sure the choice is valid   
                        choice=val;
                        memchoice=-1;
                        menu=1;
                        break;
                    }
                    else                            //If wrong value warn user.
                    {
                        PutStringn(" WRONG VALUE!");
                        PutString("OPTION: ");
                        choice=99;
                        break;
                    }
                }
            case 1:     //Option 1 
                if (memchoice!=1){
                    printf("\e[1;1H\e[2J");
                    PutStringn("PWM OC CHANNEL OPTION [1..5]");
                    PutString("Choose OC Channel: ");
                    memchoice=1;
                    menu=0;
                }
                else{
                    if(val<6 && val>0 ){
                        choice=0;
                        menu=1;
                        break;
                    }
                }
                choice=99;
                break;
            case 2:     //Option 2
                if (memchoice!=2){
                    printf("\e[1;1H\e[2J");
                    PutStringn("ADC CHANNEL OPTION AN[0...15]");
                    PutString("Choose Channel: ");
                    memchoice=choice;
                    choice=99;
                    menu=0;
                }
                else{
                    if(val<15 && val>-1 ){            //Make sure the choice is valid
                        choice=0;
                        memchoice=-1;
                        menu=1;
                        break;
                    }
                    else{
                        PutStringn(" WRONG VALUE!");
                        PutString("Choose Channel: ");
                        choice=99;
                        break;
                    }
                }
                break;
            case 99:                                  //choice case
                if (menu==1){
                    choice=GetButton(1);
                }
                else{
                    wait=1;
                    total=0;
                    while(wait){
                        val=GetButton(&wait);
                        if(-1<val && val<10){
                            PutInt(val);
                            total=val+(total*10);
                        }
                    }
                    val=total;
                    choice=memchoice;
                }
                break;
            default:
                break;
        }
    };
    return 0;
}