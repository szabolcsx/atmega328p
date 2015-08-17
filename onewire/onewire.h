#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

#include <stdint.h>

typedef struct
{
    volatile uint8_t* port;
    volatile uint8_t* ddr;
    volatile uint8_t* pin;
    uint8_t n;
} owConnection_t;

uint8_t owRead(owConnection_t* conn);
void owWrite(owConnection_t* conn,
    uint8_t data);

uint8_t owReset(owConnection_t* conn);
void owReadROM(owConnection_t* conn,
    uint8_t buf[8]);
void owSearchROM(owConnection_t* conn,
    uint8_t* buf,
    uint8_t* count,
    uint8_t alarm);
void owMatchROM(owConnection_t* conn,
    uint8_t rom[8]);
void owSkipROM(owConnection_t* conn);
void owReadScratchpad(owConnection_t* conn,
    uint8_t* buf,
    uint16_t len);
void owWriteScratchpad(owConnection_t* conn,
    uint8_t* buf,
    uint16_t len);
void owCopyScratchpad(owConnection_t* conn);

uint8_t owCalcCRC(uint8_t* data,
    uint16_t len);


#endif /* __ONEWIRE_H__ */
