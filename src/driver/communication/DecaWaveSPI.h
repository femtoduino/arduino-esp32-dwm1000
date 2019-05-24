#ifndef _DECAWAVESPI_H_
#define _DECAWAVESPI_H_

#include <SPI.h>

#include <stdio.h>
#include <stdlib.h>

#include "./DWM1000Constants.h"

class DecaWaveSPIClass {
    SPIClass _spi;
    int _irq;
    int _reset;
public:
    DecaWaveSPIClass(SPIClass spi, int irq_pin, int reset_pin) : 
        _spi(spi),
        _irq(irq_pin),
        _reset(reset_pin)
        { };

    void begin();
    uint32_t transfer(uint32_t data);
    void end();
};

extern DecaWaveSPIClass DecaWaveSPI;
#endif