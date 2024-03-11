#ifndef __ADC_H__
#define __ADC_H__


typedef enum{AN0=0,AN1,AN2,AN3,AN4,AN5,AN6,AN7,AN8,AN9,AN10,AN11,AN12,AN13,AN14,AN15
}ADCchannels;


/*******************************************************************
 * Function: ADC_init()
 * Precondition:
 * Input:       None
 * Output:      None
 * Side Effects:None
 * Overview:    Starts ADC with predetermined options and settings.
 * Note:        None
 *******************************************************************/
void ADC_init(void);

/*******************************************************************
 * Function: ADC_input()
 * Precondition:
 * Input:       Unsigned integer
 * Output:      Integer
 * Side Effects:None
 * Overview:    Function to choose ADC output pin.
 * Note:        None
 *******************************************************************/
int ADC_input(uint16_t a);


/*******************************************************************
 * Function: ADC_enable()
 * Precondition:
 * Input:       None
 * Output:      None
 * Side Effects:None
 * Overview:    Function enables ADC.
 * Note:        None
 *******************************************************************/
void ADC_enable(void);

/*******************************************************************
 * Function: ADC_read()
 * Precondition:
 * Input:       None
 * Output:      Float
 * Side Effects:None
 * Overview:    Function reads ADC BUF0 and outputs has float.
 * Note:        None
 *******************************************************************/
float ADC_read(void);

/*******************************************************************
 * Function: ADC_IF()
 * Precondition:
 * Input:       None
 * Output:      Unsigned Integer
 * Side Effects:None
 * Overview:    Resets ADC Interruption Flag.
 * Note:        None
 *******************************************************************/
uint8_t ADC_IF(void);

/*******************************************************************
 * Function: ADC_start()
 * Precondition:
 * Input:       None
 * Output:      None
 * Side Effects:None
 * Overview:    ADC starts conversion.
 * Note:        None
 *******************************************************************/
void ADC_start(void);
#endif