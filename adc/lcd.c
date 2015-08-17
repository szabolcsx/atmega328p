#include "global.h"
#include "io_mapping.h"
#include <util/delay.h>

#include "lcd.h"

void lcdInit(unsigned char functionSet,
    unsigned char displayControl,
    unsigned char entryMode)
{
    _delay_ms(40);
    LCD_EN = 0;
	LCD_RS = 0;
	lcdwNibble(0x03);
	_delay_ms(5);
	lcdwNibble(0x03);
	_delay_ms(5);
	lcdwNibble(0x03);
	_delay_ms(5);
	lcdwNibble(0x02);
	lcdWrite(functionSet); // Function set
	lcdWrite(LCD_CLEAR_DISPLAY); // Clear display
	lcdWrite(entryMode); // Entry mode set
	lcdWrite(displayControl); // Display on/off
}

void lcdClear(void)
{
    LCD_EN = 0;
	LCD_RS = 0;
	lcdWrite(0b00000001);
	_delay_ms(2);
}

void lcdWrite(unsigned char data)
{
    _delay_ms(1);
	lcdwNibble((data >> 4) & 0x0F);
	lcdwNibble(data & 0x0F);
}

void lcdwNibble(unsigned char nibble)
{
    nibble &= 0x0F;
	LCD_D4 = nibble & 1;
	LCD_D5 = (nibble >> 1) & 1;
	LCD_D6 = (nibble >> 2) & 1;
	LCD_D7 = (nibble >> 3) & 1;
	LCD_EN = 1;
	asm("nop");
	LCD_EN = 0;
}

void lcdwCmd(unsigned char command)
{
    LCD_EN = 0;
	LCD_RS = 0;
    lcdWrite(command);
}

void lcdwChar(unsigned char character)
{
    LCD_EN = 0;
    LCD_RS = 1;
    lcdWrite(character);
}

void lcdwString(char* string)
{
    while(*string)
    {
        lcdwChar(*(string++));
    }
}

void lcdwStringNFill(char* string,
    char length)
{
    while(*string)
    {
        lcdwChar(*(string++));
        length--;
    }

    if(length > 0)
    {
        lcdFill(' ', length);
    }
}

void lcdwStringAt(unsigned char row,
    unsigned char column,
    char* string)
{
    lcdAdvance(row, column);
    lcdwString(string);
}

void lcdwInt(int data)
{
    if(data < 0)
    {
        lcdwChar('-');
        data *= -1;
    }

    lcdwUInt(data);
}

void lcdwLong(long int data)
{
    if(data < 0)
    {
        lcdwChar('-');
        data *= -1;
    }

    lcdwUInt(data);
}

void lcdwUInt(unsigned int data)
{
    char buffer[5];
	int size = 0;

	do
	{
		buffer[size] = data % 10;
		data /= 10;
		size++;
	} while (data > 0);

	for(size--; size >= 0; size--)
		lcdwChar(buffer[size] + 48);
}

void lcdwULong(unsigned long int data)
{
    char buffer[10];
	int size = 0;

	do
	{
		buffer[size] = data % 10;
		data /= 10;
		size++;
	} while (data > 0);

	for(size--; size >= 0; size--)
		lcdwChar(buffer[size] + 48);
}

void lcdFill(unsigned char character,
    char n)
{
    for(; n > 0; n--)
    {
        lcdwChar(character);
    }
}

void lcdAdvance(unsigned char row,
    unsigned char column)
{
    switch(row)
    {
        case 1:
            row = LCD_LINE1;
            break;

        case 2:
            row = LCD_LINE2;
            break;

        default:
            return;
    }

    lcdwCmd(LCD_XY(row, column));
}

void lcdInitBargraph(void)
{
    lcdwCmd(LCD_SET_CGRAM_ADDRESS);

    // 100% Segment
    lcdwChar(0b00000);
    lcdwChar(0b11111);
    lcdwChar(0b11111);
    lcdwChar(0b11111);
    lcdwChar(0b11111);
    lcdwChar(0b11111);
    lcdwChar(0b00000);
    lcdwChar(0b00000);

    // 20% Segment
    lcdwChar(0b00000);
    lcdwChar(0b11111);
    lcdwChar(0b10000);
    lcdwChar(0b10101);
    lcdwChar(0b10000);
    lcdwChar(0b11111);
    lcdwChar(0b00000);
    lcdwChar(0b00000);

    // 40% Segment
    lcdwChar(0b00000);
    lcdwChar(0b11111);
    lcdwChar(0b11000);
    lcdwChar(0b11101);
    lcdwChar(0b11000);
    lcdwChar(0b11111);
    lcdwChar(0b00000);
    lcdwChar(0b00000);

    // 60% Segment
    lcdwChar(0b00000);
    lcdwChar(0b11111);
    lcdwChar(0b11100);
    lcdwChar(0b11101);
    lcdwChar(0b11100);
    lcdwChar(0b11111);
    lcdwChar(0b00000);
    lcdwChar(0b00000);

    // 80% Segment
    lcdwChar(0b00000);
    lcdwChar(0b11111);
    lcdwChar(0b11110);
    lcdwChar(0b11111);
    lcdwChar(0b11110);
    lcdwChar(0b11111);
    lcdwChar(0b00000);
    lcdwChar(0b00000);

    // Dots
    lcdwChar(0b00000);
    lcdwChar(0b11111);
    lcdwChar(0b00000);
    lcdwChar(0b10101);
    lcdwChar(0b00000);
    lcdwChar(0b11111);
    lcdwChar(0b00000);
    lcdwChar(0b00000);

#ifdef LCD_BARGRAPH_BEGIN_END
    // Begin
    lcdwChar(0b00000);
    lcdwChar(0b00001);
    lcdwChar(0b00001);
    lcdwChar(0b00101);
    lcdwChar(0b00001);
    lcdwChar(0b00001);
    lcdwChar(0b00000);
    lcdwChar(0b00000);

    // End
    lcdwChar(0b00000);
    lcdwChar(0b10000);
    lcdwChar(0b10000);
    lcdwChar(0b10100);
    lcdwChar(0b10000);
    lcdwChar(0b10000);
    lcdwChar(0b00000);
    lcdwChar(0b00000);
#endif /* LCD_BARGRAPH_BEGIN_END */
}

void lcdPrintBargraphAt(unsigned char row,
    unsigned char column,
    unsigned long int level,
    unsigned long int maxLevel,
    unsigned char size)
{
    lcdAdvance(row, column);

#ifdef LCD_BARGRAPH_BEGIN_END
    lcdwChar(0x06);
    size -= 2;
#endif /* LCD_BARGRAPH_BEGIN_END */
    if(level >= maxLevel)
    {
        lcdFill(0x00, size);
    }
    else
    {
        unsigned long int length = level * size * 5 / maxLevel;
        unsigned char lastChar = length % 5;

        lcdFill(0x00, length / 5);
        length = size - length / 5;
        if(lastChar > 0)
        {
            length--;
            lcdwChar(lastChar);
        }

        lcdFill(0x05, length);
    }
#ifdef LCD_BARGRAPH_BEGIN_END
        lcdwChar(0x07);
#endif /* LCD_BARGRAPH_BEGIN_END */
}
