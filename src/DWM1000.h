#ifndef _DWM1000_H_
#define _DWM1000_H_

#include <stdio.h>
#include <stdlib.h>

#include "DWM1000Constants.h"
#include "driver/CommunicationAbstract.h"
#include "driver/communication/SPICommunication.h"
namespace Femto {
    class DWM1000Class {

        CommunicationAbstract * _comms;
        byte _vmeas3v3 = 0;
        byte _tmeas23C = 0;

        byte _sysstatus[DWM1000ConstantsClass::SYS_STATUS.length];
        byte _syscfg[DWM1000ConstantsClass::SYS_CFG.length];
        byte _networkAndAddress[DWM1000ConstantsClass::PANADR.length];
        byte _chanctrl[DWM1000ConstantsClass::CHAN_CTRL.length];
        byte _txfctrl[DWM1000ConstantsClass::TX_FCTRL.length];

    public:
        DWM1000Class(CommunicationAbstract * comms): 
            _comms(comms)
            {

                // Initialize internal stuff
                _comms->select();
                reset();
                _comms->mode(0);
                enableClock(DWM1000ConstantsClass::SYS_XTI_CLOCK);
                delay(5);

                // Configure the CPLL lock detect
                _writeBit(
                    DWM1000ConstantsClass::EXT_SYNC.id,
                    DWM1000ConstantsClass::EC_CTRL.id,
                    DWM1000ConstantsClass::EC_CTRL.length,
                    DWM1000ConstantsClass::PLLLDT_BIT,
                    true
                );

                configureXtalTrim();
                _manageLDE();

                loadVBAT();
                loadTemperature();

                enableClock(DWM1000ConstantsClass::SYS_AUTO_CLOCK);
                delay(5);

                _comms->mode(1);

                _readNetworkIdAndDeviceAddress();
                _readSystemConfigurationRegister();
                _readChannelControlRegister();
                _readTransmitFrameControlRegister();
                _readSystemEventStatusRegister();


                /* Cleared AON:CFG1(0x2C:0x0A) for proper operation of deepSleep */
                _writeRegister(
                    DWM1000ConstantsClass::AON.id, 
                    DWM1000ConstantsClass::AON_CFG1.id, 
                    0x00, 
                    DWM1000ConstantsClass::AON_CFG1.length
                );

                Serial.println("DWM1000Class instantiated!");
            };

        void begin();

        void end();

        std::string getDevId();

        void reset();

        void enableClock(byte clock);
        void configureXtalTrim();
        void loadTemperature();
        void loadVBAT();

        void _readBytes(byte cmd, uint16_t offset, byte data[], uint16_t data_size);
        void _readBytesOTP(uint16_t address, byte data[]);
        void _writeRegister(byte cmd, uint16_t offset, uint32_t data, uint16_t data_size);
        void _writeByte(byte cmd, uint16_t offset, byte data);
        void _writeBytes(byte cmd, uint16_t offset, byte data[], uint16_t data_size);
        void _writeBit(byte bitRegister, uint16_t RegisterOffset, uint16_t bitRegister_LEN, uint16_t selectedBit, boolean value);
        void _writeValueToBytes(byte data[], uint64_t val, uint8_t n);
        void _disableSequencing();
        void _manageLDE();

        void _readNetworkIdAndDeviceAddress();
        void _readSystemConfigurationRegister();
        void _readChannelControlRegister();
        void _readTransmitFrameControlRegister();
        void _readSystemEventStatusRegister();
    };
}
extern Femto::DWM1000Class DWM1000;
#endif