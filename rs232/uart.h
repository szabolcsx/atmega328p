#ifndef __UART_H__
#define __UART_H__

#include <inttypes.h>

#define BAUD_RATE   9600
#define BAUD_PS(BR) (F_CPU/16)/BR - 1

inline void uartInit(uint16_t baudPs);
inline void uartEnableTx(void);
inline void uartDisableTx(void);
inline void uartEnableRx(void);
inline void uartDisableRx(void);
inline void uartEnableTxInterrupt(void);
inline void uartDisableTxInterrupt(void);
inline void uartEnableRxInterrupt(void);
inline void uartDisableRxInterrupt(void);
void uartwChar(uint8_t data);
uint8_t uartrChar(void);
void uartwString(const char* str);
const char* uartrString(void);

#endif /* __UART_H__ */
