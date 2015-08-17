#ifndef _IO_MAPPING_H__
#define _IO_MAPPING_H__

#include <avr/io.h>

typedef struct
{
	uint8_t B0:1;
	uint8_t B1:1;
	uint8_t B2:1;
	uint8_t B3:1;
	uint8_t B4:1;
	uint8_t B5:1;
	uint8_t B6:1;
	uint8_t B7:1;
} bits;

#define PORT_B (* (volatile bits *) &PORTB)
#define PIN_B (* (volatile bits *) &PINB)
#define DDR_B (* (volatile bits *) &DDRB)

#define PORT_C (* (volatile bits *) &PORTC)
#define PIN_C (* (volatile bits *) &PINC)
#define DDR_C (* (volatile bits *) &DDRC)

#define PORT_D (* (volatile bits *) &PORTD)
#define PIN_D (* (volatile bits *) &PIND)
#define DDR_D (* (volatile bits *) &DDRD)


#define LCD_RS  PORT_D.B4

#define LCD_EN  PORT_D.B5

#define LCD_D4  PORT_D.B0
#define LCD_D5  PORT_D.B1
#define LCD_D6  PORT_D.B2
#define LCD_D7  PORT_D.B3

#endif /* _IO_MAPPING_H__ */
