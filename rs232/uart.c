#include "uart.h"
#include "sfr_helper.h"

#include <avr/io.h>

inline void uartInit(uint16_t baudPs)
{
    _SB(DDRD, PD1);
	_CB(DDRD, PD0);
    UBRR0H = ((baudPs) & 0xF00);
	UBRR0L = (uint8_t) ((baudPs) & 0xFF);
}

inline void uartEnableTx(void)
{
    _SB(UCSR0B, TXEN0);
}

inline void uartDisableTx(void)
{
    _CB(UCSR0B, TXEN0);
}

inline void uartEnableRx(void)
{
    _SB(UCSR0B, RXEN0);
}

inline void uartDisableRx(void)
{
    _CB(UCSR0B, RXEN0);
}

inline void uartEnableTxInterrupt(void)
{
    _SB(UCSR0B, TXCIE0);
}

inline void uartDisableTxInterrupt(void)
{
    _CB(UCSR0B, TXCIE0);
}

inline void uartEnableRxInterrupt(void)
{
    _SB(UCSR0B, RXCIE0);
}

inline void uartDisableRxInterrupt(void)
{
    _CB(UCSR0B, RXCIE0);
}

void uartwChar(uint8_t data)
{
    while(!_V(UCSR0A, UDRE0));
    UDR0 = (uint8_t)data;
}

uint8_t uartrChar(void)
{
    while (!_V(UCSR0A, RXC0));
	return (uint8_t) UDR0;
}

void uartwString(const char* str)
{
    while (*str != '\0')
	{
		uartwChar(*(str++));
	}
}

const char* uartrString(void)
{
    static char rxstr[16];
	static char* temp;
	temp = rxstr;

	while((*temp = uartrChar()) != '\n')
	{
		++temp;
	}

	return rxstr;
}
