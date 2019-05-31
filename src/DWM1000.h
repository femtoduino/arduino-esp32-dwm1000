#ifndef _DWM1000_H_
#define _DWM1000_H_

#include "DWM1000Constants.h"
#include "driver/CommunicationAbstract.h"
#include "driver/communication/SPICommunication.h"

class DWM1000Class {

    CommunicationAbstract * _comms;

public:
    DWM1000Class(CommunicationAbstract * comms): 
        _comms(comms)
        {

            // Initialize internal stuff
        };

    void begin();

    void end();
};

extern DWM1000Class DWM1000;
#endif