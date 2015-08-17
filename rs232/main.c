#include <avr/io.h>
#include "uart.h"


int main(void)
{
    uartInit(BAUD_PS(9600));

    uartEnableTx();
    uartEnableRx();

    uartwString("Hello world!");

    while(1)
    {
        uartwString(uartrString());
        uartwChar('\r');
        uartwChar('\n');
    }

    return 0;
}
