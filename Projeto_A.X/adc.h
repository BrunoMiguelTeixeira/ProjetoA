#ifndef __ADC_H__
#define __ADC_H__


typedef enum{AN0=0,AN1,AN2,AN3,AN4,AN5,AN6,AN7,AN8,AN9,AN10,AN11,AN12,AN13,AN14,AN15
}ADCchannels;

void ADC_init(void);
int ADC_input(uint16_t a);
void ADC_enable(void);
uint16_t ADC_read(void);
uint8_t ADC_IF(void);
void ADC_start(void);
#endif