#ifndef _DECAWAVESPI_H_
#define _DECAWAVESPI_H_
#include <Arduino.h>
#include <SPI.h>

#include <stdio.h>
#include <stdlib.h>

#include "./DWM1000Constants.h"

class DecaWaveSPIClass {

    SPIClass * _spi;
    uint8_t _spi_bus;
    uint8_t _sck;
    uint8_t _miso;
    uint8_t _mosi;
    uint8_t _ss;
    uint8_t _irq;
    uint8_t _reset;
public:
    DecaWaveSPIClass(
        uint8_t spi_bus, 
        uint8_t sck, 
        uint8_t miso, 
        uint8_t mosi, 
        uint8_t ss, 
        uint8_t irq_pin, 
        uint8_t reset_pin) : 

        _spi_bus(spi_bus),
        _sck(sck),
        _miso(miso),
        _mosi(mosi),
        _ss(ss),
        _irq(irq_pin),
        _reset(reset_pin)

        {
            _spi = new SPIClass(_spi_bus);
            _spi->begin(_sck, _miso, _mosi, _ss);
            pinMode(_ss, OUTPUT);
        };

    void begin();
    /**
     * Transfer byte over SPI to DecaWave device.
     * See dw1000_user_manual_2.0.3.pdf
     * 
     * @param byte data The byte of data to send
     * @param bool begin Call SPI beginTransaction() before transfer, default is true.
     * @param bool end Call SPI endTransaction() after transfer, default is true.
     */
    byte transfer(byte data, bool begin = true, bool end = true);
    void end();
};

extern DecaWaveSPIClass DecaWaveSPI;
#endif