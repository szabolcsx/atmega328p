#include <util/delay.h>

#include <avr/eeprom.h>

//int EEMEM asd = 0;

#include "lcd2.h"
#include "sfr_helper.h"

void lcdInit(lcdHandle_t* handle,
    unsigned char functionSet,
    unsigned char displayControl,
    unsigned char entryMode)
{
    _delay_ms(40);
    _CB(*handle->EN, handle->PEN);
	_CB(*handle->RS, handle->PRS);
	lcdwNibble(handle, 0x03);
	_delay_ms(5);
	lcdwNibble(handle, 0x03);
	_delay_ms(5);
	lcdwNibble(handle, 0x03);
	_delay_ms(5);
	lcdwNibble(handle, 0x02);
	lcdWrite(handle, functionSet); // Function set
	lcdWrite(handle, LCD_CLEAR_DISPLAY); // Clear display
	lcdWrite(handle, entryMode); // Entry mode set
	lcdWrite(handle, displayControl); // Display on/off
}

void lcdClear(lcdHandle_t* handle)
{
    _CB(*handle->EN, handle->PEN);
	_CB(*handle->RS, handle->PRS);
	lcdWrite(handle, 0b00000001);
	_delay_ms(2);
}

void lcdWrite(lcdHandle_t* handle,
    unsigned char data)
{
    _delay_ms(1);
	lcdwNibble(handle, (data >> 4) & 0x0F);
	lcdwNibble(handle, data & 0x0F);
}

void lcdwNibble(lcdHandle_t* handle,
    unsigned char nibble)
{
    nibble &= 0x0F;
    _NB(*handle->D4, handle->P4, _V(nibble, 0));
    _NB(*handle->D4, handle->P5, _V(nibble, 1));
    _NB(*handle->D4, handle->P6, _V(nibble, 2));
    _NB(*handle->D4, handle->P7, _V(nibble, 3));

    _SB(*handle->EN, handle->PEN);
	asm("nop");
	_CB(*handle->EN, handle->PEN);
}

void lcdwCmd(lcdHandle_t* handle,
    unsigned char command)
{
    _CB(*handle->EN, handle->PEN);
	_CB(*handle->RS, handle->PRS);
    lcdWrite(handle, command);
}

void lcdwChar(lcdHandle_t* handle,
    unsigned char character)
{
    _CB(*handle->EN, handle->PEN);
	_SB(*handle->RS, handle->PRS);
    lcdWrite(handle, character);
}

void lcdwString(lcdHandle_t* handle,
    char* string)
{
    while(*string)
    {
        lcdwChar(handle, *(string++));
    }
}

void lcdwStringNFill(lcdHandle_t* handle,
    char* string,
    char length)
{
    while(*string)
    {
        lcdwChar(handle, *(string++));
        length--;
    }

    if(length > 0)
    {
        lcdFill(handle, ' ', length);
    }
}

void lcdwStringAt(lcdHandle_t* handle,
    unsigned char row,
    unsigned char column,
    char* string)
{
    lcdAdvance(handle, row, column);
    lcdwString(handle, string);
}

void lcdwInt(lcdHandle_t* handle,
    int data)
{
    if(data < 0)
    {
        lcdwChar(handle, '-');
        data *= -1;
    }

    lcdwUInt(handle, data);
}

void lcdwLong(lcdHandle_t* handle,
    long int data)
{
    if(data < 0)
    {
        lcdwChar(handle, '-');
        data *= -1;
    }

    lcdwUInt(handle, data);
}

void lcdwUInt(lcdHandle_t* handle,
    unsigned int data)
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
		lcdwChar(handle, buffer[size] + 48);
}

void lcdwULong(lcdHandle_t* handle,
    unsigned long int data)
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
		lcdwChar(handle, buffer[size] + 48);
}

void lcdFill(lcdHandle_t* handle,
    unsigned char character,
    char n)
{
    for(; n > 0; n--)
    {
        lcdwChar(handle, character);
    }
}

void lcdAdvance(lcdHandle_t* handle,
    unsigned char row,
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

    lcdwCmd(handle, row + column - 1);
}

void lcdInitBargraph(lcdHandle_t* handle)
{
    lcdwCmd(handle, LCD_SET_CGRAM_ADDRESS);

    // 100% Segment
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);

    // 20% Segment
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b10000);
    lcdwChar(handle, 0b10101);
    lcdwChar(handle, 0b10000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);

    // 40% Segment
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11000);
    lcdwChar(handle, 0b11101);
    lcdwChar(handle, 0b11000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);

    // 60% Segment
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11100);
    lcdwChar(handle, 0b11101);
    lcdwChar(handle, 0b11100);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);

    // 80% Segment
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11110);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b11110);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);

    // Dots
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b10101);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b11111);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);

#ifdef LCD_BARGRAPH_BEGIN_END
    // Begin
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00001);
    lcdwChar(handle, 0b00001);
    lcdwChar(handle, 0b00101);
    lcdwChar(handle, 0b00001);
    lcdwChar(handle, 0b00001);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);

    // End
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b10000);
    lcdwChar(handle, 0b10000);
    lcdwChar(handle, 0b10100);
    lcdwChar(handle, 0b10000);
    lcdwChar(handle, 0b10000);
    lcdwChar(handle, 0b00000);
    lcdwChar(handle, 0b00000);
#endif /* LCD_BARGRAPH_BEGIN_END */
}

void lcdPrintBargraphAt(lcdHandle_t* handle,
    unsigned char row,
    unsigned char column,
    lcdBargraphDescriptor_t* descriptor)
{
    lcdAdvance(handle, row, column);

#ifdef LCD_BARGRAPH_BEGIN_END
    lcdwChar(handle, 0x06);
    size -= 2;
#endif /* LCD_BARGRAPH_BEGIN_END */
    if(descriptor->level >= descriptor->maxLevel)
    {
        lcdFill(handle, 0x00, descriptor->size);
    }
    else
    {
        unsigned long int length = descriptor->level * descriptor->size * 5 / descriptor->maxLevel;
        unsigned char lastChar = length % 5;

        lcdFill(handle, 0x00, length / 5);
        length = descriptor->size - length / 5;
        if(lastChar > 0)
        {
            length--;
            lcdwChar(handle, lastChar);
        }

        lcdFill(handle, 0x05, length);
    }
#ifdef LCD_BARGRAPH_BEGIN_END
        lcdwChar(handle, 0x07);
#endif /* LCD_BARGRAPH_BEGIN_END */
}
