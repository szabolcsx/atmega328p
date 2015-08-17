#ifndef __LCD_H__
#define __LCD_H__

#include <inttypes.h>               // Requiered for uint8_t

typedef struct
{
    volatile uint8_t* D4;
    uint8_t P4;

    volatile uint8_t* D5;
    uint8_t P5;

    volatile uint8_t* D6;
    uint8_t P6;

    volatile uint8_t* D7;
    uint8_t P7;

    volatile uint8_t* RS;
    uint8_t PRS;

    volatile uint8_t* EN;
    uint8_t PEN;
} lcdHandle_t;

enum
{
    LCD_CLEAR_DISPLAY           = 0b00000001,
    LCD_RETURN_HOME             = 0b00000010,

    /* Entry Mode Set */
    LCD_INCREMENT               = 0b00000110,
    LCD_DECREMENT               = 0b00000100,
    LCD_SHIFT_ENABLE            = 0b00000101,
    LCD_SHIFT_DISABLE           = 0b00000100,

    /* Display ON/OFF Control */
    LCD_DISPLAY_ON              = 0b00001100,
    LCD_DISPLAY_OFF				= 0b00001000,
    LCD_CURSOR_ON				= 0b00001010,
    LCD_CURSOR_OFF				= 0b00001000,
    LCD_CURSOR_BLINK_ON			= 0b00001001,
    LCD_CURSOR_BLINK_OFF		= 0b00001000,

    /* Cursor or Display Shift */
    LCD_SHIFT_DISPLAY_LEFT      = 0b00011000,
    LCD_SHIFT_DISPLAY_RIGHT     = 0b00011100,

    /* Function Set */
    LCD_8BIT_BUS				= 0b00110000,
    LCD_4BIT_BUS				= 0b00100000,
    LCD_1LINE_MODE				= 0b00100000,
    LCD_2LINE_MODE				= 0b00101000,
    LCD_5X7_DOTS_FORMAT			= 0b00100000,
    LCD_5X10_DOTS_FORMAT		= 0b00100100,

    LCD_SET_CGRAM_ADDRESS       = 0b01000000,

    /* Set DDRAM Address */
    LCD_LINE1					= 0b10000000,
    LCD_LINE2					= 0b11000000
};

void lcdInit(lcdHandle_t* handle,
    unsigned char functionSet,
    unsigned char displayControl,
    unsigned char entryMode);
void lcdClear(lcdHandle_t* handle);
void lcdWrite(lcdHandle_t* handle,
    unsigned char data);
void lcdwNibble(lcdHandle_t* handle,
    unsigned char nibble);
void lcdwCmd(lcdHandle_t* handle,
    unsigned char command);
void lcdwChar(lcdHandle_t* handle,
    unsigned char character);
void lcdwString(lcdHandle_t* handle,
    char* string);
void lcdwStringNFill(lcdHandle_t* handle,
    char* string,
    char length);
void lcdwStringAt(lcdHandle_t* handle,
    unsigned char row,
    unsigned char column,
    char* string);
void lcdwInt(lcdHandle_t* handle,
    int data);
void lcdwLong(lcdHandle_t* handle,
    long int data);
void lcdwUInt(lcdHandle_t* handle,
    unsigned int data);
void lcdwULong(lcdHandle_t* handle,
    unsigned long int data);
void lcdFill(lcdHandle_t* handle,
    unsigned char character,
    char n);
void lcdAdvance(lcdHandle_t* handle,
    unsigned char row,
    unsigned char column);
void lcdInitBargraph(lcdHandle_t* handle);
void lcdPrintBargraphAt(lcdHandle_t* handle,
    unsigned char row,
    unsigned char column,
    unsigned long int level,
    unsigned long int maxLevel,
    unsigned char size);

#endif /* __LCD_H__ */
