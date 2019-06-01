#ifndef _DWM1000_SPI_COMMUNICATION_H_
#define _DWM1000_SPI_COMMUNICATION_H_
#include <Arduino.h>
#include <SPI.h>

#include <stdio.h>
#include <stdlib.h>

#include "./DWM1000Constants.h"
#include "../CommunicationAbstract.h"

namespace Femto {
    // void SPICommunication_IRQ_Callback();
    /**
     * Communication (SPI) class. Implements the CommunicationAbstract class.
     * 
     * @author Femtoduino <support@femtoduino.com>
     * @since 0.0.0
     * @license MIT License
     * @copyright 2019 Femtoduino
     */
    class SPICommunicationClass : public CommunicationAbstract {

        SPIClass * _spi;
        uint8_t _spi_bus;
        uint8_t _sck;
        uint8_t _miso;
        uint8_t _mosi;
        uint8_t _ss;
        uint8_t _irq;
        uint8_t _reset;
        SPISettings _fast_spi_settings = SPISettings(ESP32_SPI_SPEED, MSBFIRST, SPI_MODE0);
        SPISettings _slow_spi_settings = SPISettings(MIN_SPI_SPEED, MSBFIRST, SPI_MODE0);
        SPISettings * _current_spi_settings = &_fast_spi_settings;

    public:

        SPICommunicationClass(
            uint8_t spi_bus, 
            uint8_t sck, 
            uint8_t miso, 
            uint8_t mosi, 
            uint8_t ss, 
            uint8_t irq_pin, 
            uint8_t reset) : 

            _spi_bus(spi_bus),
            _sck(sck),
            _miso(miso),
            _mosi(mosi),
            _ss(ss),
            _irq(irq_pin),
            _reset(reset)

            {
                _spi = new SPIClass(_spi_bus);
                
                pinMode(_ss, OUTPUT);
                // pinMode(_reset, INPUT); // Float?
                // pinMode(_irq, INPUT);

                _spi->begin(_sck, _miso, _mosi, _ss);
            };

        void begin();
        /**
         * Transfer byte over SPI to DecaWave device.
         * See dw1000_user_manual_2.0.3.pdf
         * 
         * @param byte data The byte of data to send
         * @param bool begin Call SPI beginTransaction() before transfer, default is true.
         * @param bool end Call SPI endTransaction() after transfer, default is true.
         * @return byte Returned data, if available.
         */
        byte transfer(byte data);
        void beginTransaction();
        void endTransaction();
        void end();

        void select();
        void mode(byte speed);

        void read(uint8_t header_length, byte header[], uint16_t data_size, byte data[]);
        void write(uint8_t header_length, byte header[], uint16_t data_size, byte data[]);
    };
}
extern Femto::SPICommunicationClass SPICommunication;
#endif