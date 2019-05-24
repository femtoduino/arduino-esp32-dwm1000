#ifndef _DWM1000_H_
#define _DWM1000_H_

#include "./driver/communication/DecaWaveSPI.h"

class DWM1000Class {

    DecaWaveSPIClass _spi;

public:
    DWM1000Class(DecaWaveSPIClass spi): 
        _spi(spi)
        {};

    void begin();

    void end();
};

extern DWM1000Class DWM1000;
#endif