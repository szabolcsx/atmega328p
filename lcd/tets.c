#include "lcd.h"
#include "global.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char counter = 0;
unsigned long int counter2 = 0;

typedef struct
{
    unsigned handlePinChange0:1;
} interruptFlags_t;

typedef struct
{
    unsigned handleShortButtonPress:1;
    unsigned handleLongButtonPress:1;
} buttonPressFlags_t;

typedef struct
{
    unsigned counterShortButtonPressTick:1;
    unsigned counterLongButtonPressTick:1;
    unsigned counterLongButtonPressSampleTick:1;
} counterFlags_t;

volatile interruptFlags_t interruptFlags;
volatile buttonPressFlags_t buttonPressFlags;
volatile counterFlags_t counterFlags;

volatile unsigned int counterShortButtonPress = 0;
volatile unsigned int counterLongButtonPress = 0;
volatile unsigned int counterLongButtonPressSample = 0;

volatile unsigned int counterOneSec = 0;

char lastPhase = 0;
char currentPhase = 0;

int main(void)
{
    DDRB = 0x00;
    PORTC = 0x00;
    DDRD = 0xFF;
    lcdInit(LCD_4BIT_BUS | LCD_2LINE_MODE | LCD_5X7_DOTS_FORMAT,
        LCD_DISPLAY_ON,
        LCD_INCREMENT);

    lcdInitBargraph();

    PCICR |= 1 << PCIE0;
    PCMSK0 |= 1 << PCINT0;

    TCCR0A |= 1 << WGM01;
	OCR0A = 149;
    TIMSK0 |= (1 << OCIE0A);

	TCCR0B |= (1 << CS01) | (1 << CS00); // 1:64 prescaler

    sei();

    while(1)
    {
        if(counter2 > 10000000)
        {
            counter2 = 0;
        }

        //lcdPrintBargraphAt(1, 1, counter, 100, 16);
        lcdAdvance(1, 1);
        lcdwULong(counter2);
        lcdPrintBargraphAt(2, 1, counter2, 10000000, 16);
        lcdFill(' ', 10);

        if(interruptFlags.handlePinChange0)
        {
            interruptFlags.handlePinChange0 = 0;

            if(PINB & 1)
            {
                _delay_ms(30);
                if(PINB & 1)
                {
                    counter = 0;
                    counterFlags.counterShortButtonPressTick = 1;
                }
            }
        }

        if(buttonPressFlags.handleShortButtonPress)
        {
            buttonPressFlags.handleShortButtonPress = 0;

            if((PINB & 1) == 0)
            {
                counter2 += 50000;
                counterFlags.counterShortButtonPressTick = 0;
                counterShortButtonPress = 0;
                counterLongButtonPress = 0;
                counterLongButtonPressSample = 0;
            }
            else
            {
                counterFlags.counterLongButtonPressTick = 1;
            }
        }

        if(buttonPressFlags.handleLongButtonPress)
        {
            buttonPressFlags.handleLongButtonPress = 0;

            if((PINB & 1))
            {;
                counter2 += 100000;
            }
            else
            {
                counterFlags.counterLongButtonPressSampleTick = 0;
                counterLongButtonPressSample = 0;
            }
        }
    }

    return 0;
}

ISR(TIMER0_COMPA_vect)
{
    counterShortButtonPress += counterFlags.counterShortButtonPressTick;
    counterLongButtonPress += counterFlags.counterLongButtonPressTick;
    counterLongButtonPressSample += counterFlags.counterLongButtonPressSampleTick;
    counterOneSec++;

    if(counterShortButtonPress >= 10)
    {
        counterShortButtonPress = 0;
        buttonPressFlags.handleShortButtonPress = 1;
    }

    if(counterLongButtonPress >= 500)
    {
        counterLongButtonPress = 0;
        buttonPressFlags.handleLongButtonPress = 1;
        counterFlags.counterLongButtonPressSampleTick = 1;
    }

    if(counterLongButtonPressSample >= 10)
    {
        counterLongButtonPressSample = 0;
        buttonPressFlags.handleLongButtonPress = 1;
    }

    if(counterOneSec >= 1000)
    {
        counterOneSec = 0;
        counter += 10;
    }
}

ISR(PCINT0_vect)
{
    interruptFlags.handlePinChange0 = 1;
}
