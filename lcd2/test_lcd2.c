#include <avr/io.h>
#include <util/delay.h>
#include "lcd2.h"

lcdHandle_t lcdHandle = {
    &PORTD, 0, // D4
    &PORTD, 1, // D5
    &PORTD, 2, // D6
    &PORTD, 3, // D7
    &PORTD, 4, // RS
    &PORTD, 5  // EN
};

int main(void)
{
    DDRD = 0xFF;
    lcdInit(&lcdHandle,
        LCD_4BIT_BUS | LCD_2LINE_MODE | LCD_5X7_DOTS_FORMAT,
        LCD_DISPLAY_ON,
        LCD_INCREMENT);

    lcdwStringAt(&lcdHandle, 1, 1, "Hello world.");
    lcdInitBargraph(&lcdHandle);

    while(1)
    {
        lcdPrintBargraphAt(&lcdHandle, 2, 1, 54, 100, 16);
        /*
        _delay_ms(1000);
        lcdwCmd(&lcdHandle, LCD_DISPLAY_OFF);
        _delay_ms(1000);
        lcdwCmd(&lcdHandle, LCD_DISPLAY_ON);
        */
    }

    return 0;
}
