#ifndef _LCD_H__
#define _LCD_H__

#define LCD_CLEAR_DISPLAY	0b00000001
#define LCD_RETURN_HOME		0b00000010

/* Entry Mode Set */
#define LCD_ENTRY_MODE_SET_BYTE		0b00000100
#define LCD_INCREMENT				0b00000110
#define LCD_DECREMENT				LCD_ENTRY_MODE_SET_BYTE
#define LCD_SHIFT_ENABLE			0b00000101
#define LCD_SHIFT_DISABLE			LCD_ENTRY_MODE_SET_BYTE

/* Display ON/OFF Control */
#define LCD_DISPLAY_CONTROL_BYTE		0b00001000
#define LCD_DISPLAY_ON					0b00001100
#define LCD_DISPLAY_OFF					LCD_DISPLAY_CONTROL_BYTE
#define LCD_CURSOR_ON					0b00001010
#define LCD_CURSOR_OFF					LCD_DISPLAY_CONTROL_BYTE
#define LCD_CURSOR_BLINK_ON				0b00001001
#define LCD_CURSOR_BLINK_OFF			LCD_DISPLAY_CONTROL_BYTE

/* Cursor or Display Shift */
#define LCD_CURSOR_DISPLAY_SHIFT_BYTE   0b00010000
#define LCD_SHIFT_DISPLAY_LEFT          0b00011000
#define LCD_SHIFT_DISPLAY_RIGHT         0b00011100

/* Function Set */
#define LCD_FUNCTION_SET_BYTE		0b00100000
#define LCD_8BIT_BUS				0b00110000
#define LCD_4BIT_BUS				LCD_DISPLAY_CONTROL_BYTE
#define LCD_1LINE_MODE				LCD_DISPLAY_CONTROL_BYTE
#define LCD_2LINE_MODE				0b00101000
#define LCD_5X7_DOTS_FORMAT			LCD_DISPLAY_CONTROL_BYTE
#define LCD_5X10_DOTS_FORMAT		0b00100100

#define LCD_SET_CGRAM_ADDRESS       0b01000000

/* Set DDRAM Address */
#define LCD_SET_DDRAM_ADDRESS_BYTE	0b10000000
#define LCD_LINE1					LCD_SET_DDRAM_ADDRESS_BYTE
#define LCD_LINE2					0b11000000
#define LCD_XY(y, x)				(x + y - 1)


void lcdInit(unsigned char functionSet,
    unsigned char displayControl,
    unsigned char entryMode);
void lcdClear(void);
void lcdWrite(unsigned char data);
void lcdwNibble(unsigned char nibble);
void lcdwCmd(unsigned char command);
void lcdwChar(unsigned char character);
void lcdwString(char* string);
void lcdwStringNFill(char* string,
    char length);
void lcdwStringAt(unsigned char row,
    unsigned char column,
    char* string);
void lcdwInt(int data);
void lcdwLong(long int data);
void lcdwUInt(unsigned int data);
void lcdwULong(unsigned long int data);
void lcdFill(unsigned char character,
    char n);
void lcdAdvance(unsigned char row,
    unsigned char column);
void lcdInitBargraph(void);
void lcdPrintBargraphAt(unsigned char row,
    unsigned char column,
    unsigned long int level,
    unsigned long int maxLevel,
    unsigned char size);

#endif /* _LCD_H__ */
