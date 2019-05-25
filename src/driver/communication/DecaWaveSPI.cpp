#include "DecaWaveSPI.h"


void DecaWaveSPIClass::begin() {
    this->_spi->begin();
}

byte DecaWaveSPIClass::transfer(byte data, bool begin, bool end) {

    byte received;

    if (begin == true) {
        this->_spi->beginTransaction(SPISettings(this->_ss, MSBFIRST, SPI_MODE0));
    }

    digitalWrite(this->_ss, LOW);
    received = this->_spi->transfer(data);
    digitalWrite(this->_ss, HIGH);

    if (end == true) {
        this->_spi->endTransaction();
    }
    return received;
}

void DecaWaveSPIClass::end() {

    this->_spi->end();
}