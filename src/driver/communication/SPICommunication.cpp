#include "SPICommunication.h"

/**
 * Communication (SPI) class. Implements the CommunicationAbstract class.
 * 
 * @author Femtoduino <support@femtoduino.com>
 * @since 0.0.0
 * @license MIT License
 * @copyright 2019 Femtoduino
 */

void SPICommunicationClass::begin() {
    this->_spi->begin();
}

byte SPICommunicationClass::transfer(byte data, bool begin, bool end) {

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

void SPICommunicationClass::end() {

    this->_spi->end();
}