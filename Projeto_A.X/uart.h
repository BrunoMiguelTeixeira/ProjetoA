#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

// Define return codes
#define UART_SUCCESS 0
#define UART_FAIL -1;
#define UART_BR_NOT_SUP -2
#define UART_PBCLOCK_NOT_SUP -3

// Define prototypes (public interface)
int UartInit(uint64_t pbclock, uint32_t br);
int UartClose(void);
int GetChar(uint8_t *byte);
void PutChar(uint8_t txChar);

/*******************************************************************
 * Function: PutInt()
 * Precondition:
 * Input:       Integer
 * Output:      None
 * Side Effects:None
 * Overview:    Puts the integer has a char and into UART tx reg for transmission.
 * Note:        None
 *******************************************************************/
void PutInt(int Integer);

/*******************************************************************
 * Function: PutFloat()
 * Precondition:
 * Input:       Float
 * Output:      None
 * Side Effects:None
 * Overview:    Puts the float has a char and into UART tx reg for transmission.
 * Note:        None
 *******************************************************************/
void PutFloat(float Float,uint8_t val);

/********************************************************************
* Function: 	PutString()
* Precondition: 
* Input: 		*Char
* Output:		None
* Side Effects:	None.
* Overview:     Breaks the string into Char and puts it into UART tx reg for transmission
* Note:		 	None.
********************************************************************/
void PutString(char *Char);


/********************************************************************
* Function: 	PutStringn()
* Precondition: 
* Input: 		*Char
* Output:		None
* Side Effects:	None.
* Overview:     Breaks the string into Char,add '\r' '\n' at the end and puts it into UART tx reg for transmission
* Note:		 	None.
********************************************************************/
void PutStringn(char *Char);


/********************************************************************
* Function: 	nPutString()
* Precondition: 
* Input: 		*Char
* Output:		None
* Side Effects:	None.
* Overview:     Breaks the string into Char,add '\r' '\n' at the beginning and puts it into UART tx reg for transmission
* Note:		 	None.
********************************************************************/
void nPutString(char *Char);


/*******************************************************************
 * Function: GetInt()
 * Precondition:
 * Input:       None
 * Output:      unsigned integer
 * Side Effects:None
 * Overview:    Reads user number inputs untill Enter is pressed.
 * Note:        None
 *******************************************************************/
uint8_t GetInteger(void);
#endif