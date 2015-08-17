#define F_CPU   8000000UL

#include "adc.h"
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

unsigned long int adcResult = 0;
unsigned int counter = 0;

int main()
{
    DDRB = 0xFF;
    DDRD = 0xFF;
    DDRC = 0x00;

    lcdInit(LCD_4BIT_BUS | LCD_2LINE_MODE | LCD_5X7_DOTS_FORMAT,
        LCD_DISPLAY_ON,
        LCD_INCREMENT);

    lcdInitBargraph();

    adcSetVoltageReference(ADC_VR_AVCC);
    adcSetPrescaler(ADC_PRESCALER128);
    adcEnable();

    adcStartConvert(ADC_CHANNEL0);

    PORTB |= (1 << PB0);

    while(1)
    {
        if(((ADCSRA >> ADSC) & 1) == 0)
        {
            PORTB ^= 1 << PB0;
            adcResult = ADC;
            adcResult = adcRead();
            adcStartConvert(ADC_CHANNEL0);

            adcResult = adcResult * 5000 / 1024;
        }

        lcdwStringAt(1, 1, "U ");
        lcdPrintBargraphAt(1, 3, adcResult, 5000, 7);
        lcdwChar(' ');
        lcdwInt(adcResult);
        lcdwStringNFill("mV", 5);

        lcdwStringAt(2, 1, "I ");
        lcdPrintBargraphAt(2, 3, adcResult, 5000, 7);
        lcdwChar(' ');
        lcdwInt(adcResult);
        lcdwStringNFill("mA", 5);

        _delay_ms(1);

        counter++;

        if(counter >= 5)
        {
            counter = 0;

        }
    }

    return 0;
}
