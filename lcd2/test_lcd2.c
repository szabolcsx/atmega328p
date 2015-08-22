#include <avr/io.h>
#include <util/delay.h>
#include "lcd2.h"
#include "uart.h"

lcdHandle_t lcdHandle = {
    &PORTD, 6, // D4
    &PORTD, 7, // D5
    &PORTD, 2, // D6
    &PORTD, 3, // D7
    &PORTD, 4, // RS
    &PORTD, 5  // EN
};

lcdBargraphDescriptor_t lcdBargraphDescriptor = {
    0,
    100,
    16
};

int main(void)
{
    DDRD = 0xFF;
    lcdInit(&lcdHandle,
        LCD_4BIT_BUS | LCD_2LINE_MODE | LCD_5X7_DOTS_FORMAT,
        LCD_DISPLAY_ON,
        LCD_INCREMENT);

    uartInit(BAUD_PS(9600));
    uartEnableTx();

    lcdwStringAt(&lcdHandle, 1, 1, "Hello world.");
    lcdInitBargraph(&lcdHandle);

    uartwString("Hello world!\n");

    while(1)
    {

        lcdPrintBargraphAt(&lcdHandle, 2, 1, &lcdBargraphDescriptor);
        /*
        _delay_ms(1000);
        lcdwCmd(&lcdHandle, LCD_DISPLAY_OFF);
        _delay_ms(1000);
        lcdwCmd(&lcdHandle, LCD_DISPLAY_ON);
        */


        lcdBargraphDescriptor.level += 1;
        uartwULong(lcdBargraphDescriptor.level);
        uartwLong(-lcdBargraphDescriptor.level);
        uartwChar('\n');

        if(lcdBargraphDescriptor.level >= lcdBargraphDescriptor.maxLevel)
        {
            lcdBargraphDescriptor.level = 0;
        }

        _delay_ms(100);
    }

    return 0;
}
