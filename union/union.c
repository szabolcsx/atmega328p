#define F_CPU   8000000UL

#include <avr/io.h>
#include <util/delay.h>

typedef union
{
    struct
    {
        uint8_t B0:1;
        uint8_t B1:1;
        uint8_t B2:1;
        uint8_t B3:1;
        uint8_t B4:1;
        uint8_t B5:1;
        uint8_t B6:1;
        uint8_t B7:1;
    };
    uint8_t raw;
} register_t;

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
} bitfield_t;

#define REGISTER(r) register_t* r##Bits = (register_t*)&r
#define BITS(r) (*(volatile bitfield_t*)&r)

#define PORTBBits BITS(PORTB)

//volatile REGISTER(DDRB);
//volatile REGISTER(PORTB);

typedef struct
{
    unsigned flag1:1;
    unsigned flag2:1;
    unsigned flag3:1;
    unsigned flag4:1;
    unsigned flag5:1;
    unsigned flag6:1;
    unsigned flag7:1;
    unsigned flag8:1;
    unsigned flag9:1;
    unsigned flag10:1;
} status_flags_t;

status_flags_t status_flags;

int main()
{
    PORTBBits.B0 = 1;
    //DDRB |= 1;

    status_flags.flag1 = 1;
    status_flags.flag2 = 1;
    status_flags.flag3 = 1;
    status_flags.flag4 = 1;
    status_flags.flag5 = 1;
    status_flags.flag6 = 1;
    status_flags.flag7 = 1;
    status_flags.flag8 = 1;
    status_flags.flag9 = 1;
    status_flags.flag10 = 1;

    while(1)
    {
        PORTBBits.B0 ^= 1;
        //PORTB ^= 1;
        _delay_ms(1000);
    }

    return 0;
}
