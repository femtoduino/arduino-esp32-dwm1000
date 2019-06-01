#include "SPICommunication.h"

namespace Femto {
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

byte SPICommunicationClass::transfer(byte data) {

    byte received;

    received = this->_spi->transfer(data);

    return received;
}

void SPICommunicationClass::beginTransaction() {
    
    this->_spi->beginTransaction(*_current_spi_settings);
    digitalWrite(this->_ss, LOW);
}

void SPICommunicationClass::endTransaction() {
    digitalWrite(this->_ss, HIGH);
    this->_spi->endTransaction();
}

void SPICommunicationClass::end() {

    this->_spi->end();
}

void SPICommunicationClass::select() {
    // this->_spi->usingInterrupt(digitalPinToInterrupt(this->_irq));
    pinMode(this->_ss, OUTPUT);
    digitalWrite(this->_ss, HIGH);
}


void SPICommunicationClass::mode(byte speed) {
    if (speed == 0) {
        _current_spi_settings = & _slow_spi_settings;
    } else {
        _current_spi_settings = & _fast_spi_settings;
    }
}

void SPICommunicationClass::read(uint8_t header_length, byte header[], uint16_t data_size, byte data[]) {
    this->beginTransaction();

    // Send the headers first
    for (byte index = 0; index < header_length; index++) {
        this->transfer(header[index]);
    }

    for (byte index = 0; index < data_size; index++) {
        // Read the data
        data[index] = this->transfer(0x00);
    }

    delayMicroseconds(5);
    this->endTransaction();
}

void SPICommunicationClass::write(uint8_t header_length, byte header[], uint16_t data_size, byte data[]) {
    this->beginTransaction();

    // Send the headers first
    for (byte index = 0; index < header_length; index++) {
        this->transfer(header[index]);
    }

    for (byte index = 0; index < data_size; index++) {
        // Write the data
        this->transfer(data[index]);
    }

    delayMicroseconds(5);
    this->endTransaction();
}

// void SPICommunication_IRQ_Callback() {
//     Serial.println("+INTERRUPT+");
//     //_readBytes(SYS_STATUS, NO_SUB, _sysstatus, LEN_SYS_STATUS);
// }

}