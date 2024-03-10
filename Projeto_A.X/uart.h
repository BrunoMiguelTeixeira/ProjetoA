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
void PutInt(int Integer);
void PutFloat(float Float,uint8_t val);
void PutString(char *Char);
void PutStringn(char *Char);
void nPutString(char *Char);
uint8_t GetButton(uint8_t *Enter_press);
#endif