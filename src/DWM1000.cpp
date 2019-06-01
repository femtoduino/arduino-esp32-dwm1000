#include "DWM1000.h"
#include "DWM1000Constants.h"
#include <Arduino.h>

namespace Femto {
    void DWM1000Class::begin() {

        // Begin transaction

        DWM1000Class::_comms->begin();
    }

    void DWM1000Class::end() {
        DWM1000Class::_comms->end();
    }

    void DWM1000Class::reset() {
        // Software reset
        _disableSequencing();
        // Clear AON and WakeUp configuration
        _writeRegister(
            DWM1000ConstantsClass::AON.id, 
            DWM1000ConstantsClass::AON_WCFG.id,
            0x00,
            DWM1000ConstantsClass::AON_WCFG.length
        );
        _writeRegister(
            DWM1000ConstantsClass::AON.id,
            DWM1000ConstantsClass::AON_CFG0.id, 
            0x00,
            DWM1000ConstantsClass::AON_CFG0.length
        );

        // TODO change this with uploadToAON
        _writeRegister(
            DWM1000ConstantsClass::AON.id,
            DWM1000ConstantsClass::AON_CTRL.id,
            0x00,
            DWM1000ConstantsClass::AON_CTRL.length
        );
        _writeRegister(
            DWM1000ConstantsClass::AON.id,
            DWM1000ConstantsClass::AON_CTRL.id,
            0x02,
            DWM1000ConstantsClass::AON_CTRL.length
        );
        // ------
        
        // (b) Clear SOFTRESET to all zeros
        _writeRegister(
            DWM1000ConstantsClass::PMSC.id,
            DWM1000ConstantsClass::PMSC_SOFTRESET.id,
            0x00,
            DWM1000ConstantsClass::PMSC_SOFTRESET.length
        );
        delay(1);

        // (c) Set SOFTRESET to all ones
        _writeRegister(
            DWM1000ConstantsClass::PMSC.id,
            DWM1000ConstantsClass::PMSC_SOFTRESET.id,
            0xF0,
            DWM1000ConstantsClass::PMSC_SOFTRESET.length
        );

    }

    void DWM1000Class::_disableSequencing() {
        enableClock(DWM1000ConstantsClass::SYS_XTI_CLOCK);
        byte zero[2];
        _writeValueToBytes(zero, 0x0000, 2);
        _writeBytes(
            DWM1000ConstantsClass::PMSC.id, 
            DWM1000ConstantsClass::PMSC_CTRL1.id, 
            zero, 
            2
        );
    }

    std::string DWM1000Class::getDevId() {

        std::string result = "";
        char _result[128];

        byte data[DWM1000ConstantsClass::DEV_ID.length];

        _readBytes(
            DWM1000ConstantsClass::DEV_ID.id, 
            DWM1000ConstantsClass::SPI_HEADER_NO_SUB, 
            data, 
            DWM1000ConstantsClass::DEV_ID.length
        );

        sprintf(
            _result, 
            "%02X - model: %d, version: %d, revision: %d", 
            (uint16_t)((data[3] << 8) | data[2]), 
            data[1], 
            (data[0] >> 4) & 0x0F, 
            data[0] & 0x0F);

        // Serial.println(_result);
        result = _result;

        

        return result;
    }
    /**
     * [DWM1000Class::enableClock From arduino-dwm1000-ng DW1000Ng.cpp::_enableClock()]
     */
    void DWM1000Class::enableClock(byte clock) {
        byte pmscctrl0[ DWM1000ConstantsClass::PMSC.length ];

        memset(pmscctrl0, 0, DWM1000ConstantsClass::PMSC.length);

        // Read bytes
        // header[0] = DWM1000ConstantsClass::SPI_HEADER_READ_SUB | DWM1000ConstantsClass::PMSC.id;
        _readBytes(
            DWM1000ConstantsClass::PMSC.id, 
            DWM1000ConstantsClass::PMSC_CTRL0.id, 
            pmscctrl0, 
            DWM1000ConstantsClass::PMSC_CTRL0.length
        );
        
        if (clock == DWM1000ConstantsClass::SYS_AUTO_CLOCK) {
            pmscctrl0[0] = DWM1000ConstantsClass::SYS_AUTO_CLOCK;
            pmscctrl0[1] &= 0xFE;
        } else if (clock == DWM1000ConstantsClass::SYS_XTI_CLOCK) {
            pmscctrl0[0] &= 0xFC;
            pmscctrl0[0] |= DWM1000ConstantsClass::SYS_XTI_CLOCK;
        } else if (clock == DWM1000ConstantsClass::SYS_PLL_CLOCK) {
            pmscctrl0[0] &= 0xFC;
            pmscctrl0[0] |= DWM1000ConstantsClass::SYS_PLL_CLOCK;
        } else if (clock == DWM1000ConstantsClass::TX_PLL_CLOCK) {
            pmscctrl0[0] &= 0xCF;
            pmscctrl0[0] |= DWM1000ConstantsClass::TX_PLL_CLOCK;
        } else if (clock == DWM1000ConstantsClass::LDE_CLOCK) {
            pmscctrl0[0] = DWM1000ConstantsClass::SYS_XTI_CLOCK;
            pmscctrl0[1] = 0x03;
        }

        _writeBytes(
            DWM1000ConstantsClass::PMSC.id, 
            DWM1000ConstantsClass::PMSC_CTRL0.id, 
            pmscctrl0, 
            2
        );
    }

    void DWM1000Class::configureXtalTrim() {
        byte fsxtalt[DWM1000ConstantsClass::FS_XTALT.length];
        byte buf_otp[4];
        _readBytesOTP(0x01E, buf_otp); //0x01E -> byte[0]=XTAL_Trim

        if (buf_otp[0] == 0) {
            // No trim value available from OTP, use midrange value of 0x10
            _writeValueToBytes(
                fsxtalt, 
                ((0x10 & 0x1F) | 0x60), 
                DWM1000ConstantsClass::FS_XTALT.length
            );
        } else {
            _writeValueToBytes(
                fsxtalt, 
                ((buf_otp[0] & 0x1F) | 0x60),
                DWM1000ConstantsClass::FS_XTALT.length
            );
        }

        // Write the configuration back to the chip
        _writeBytes(
            DWM1000ConstantsClass::FS_CTRL.id,
            DWM1000ConstantsClass::FS_XTALT.id,
            fsxtalt,
            DWM1000ConstantsClass::FS_XTALT.length
        );
    }

    void DWM1000Class::loadTemperature() {
        byte buf_otp[4];
        _readBytesOTP(0x009, buf_otp);
        _tmeas23C = buf_otp[0];

        Serial.print("loadTemperature:");
        Serial.println(_tmeas23C);
    }

    void DWM1000Class::loadVBAT() {
        byte buf_otp[4];
        _readBytesOTP(0x008, buf_otp);
        _vmeas3v3 = buf_otp[0];

        Serial.print("loadVBAT:");
        Serial.println(_vmeas3v3);
    }

    /**
     * [DWM1000Class::_readBytes See arduino-dw1000-ng, DW1000Ng.cpp::_readBytes() and SPIporting.cpp::readFromSPI()]
     * @param byte cmd              The registry byte command
     * @param uint16_t offset       The registry offset
     * @param byte data[]           Data buffer to be populated by this call.
     * @param uint16_t data_size    Size of data buffer.
     */
    void DWM1000Class::_readBytes(byte cmd, uint16_t offset, byte data[], uint16_t data_size) {
        byte header[3];
        uint8_t header_length = 1;

        if (offset == DWM1000ConstantsClass::SPI_HEADER_NO_SUB) {
            header[0] = DWM1000ConstantsClass::SPI_HEADER_READ | cmd;
        } else {
            header[0] = DWM1000ConstantsClass::SPI_HEADER_READ_SUB | cmd;

            if (offset < 128) {
                header[1] = (byte) offset;
                header_length++;
            } else {
                header[1] = DWM1000ConstantsClass::SPI_HEADER_RW_SUB_EXT | (byte) offset;
                header[2] = (byte)(offset >> 7);
                header_length += 2;
            }
        }

        _comms->read(header_length, header, data_size, data);

    }

    void DWM1000Class::_readBytesOTP(uint16_t address, byte data[]) {
        byte addressBytes[DWM1000ConstantsClass::OTP_ADDR.length];

        addressBytes[0] = (address & 0xFF);
        addressBytes[1] = ((address >> 8) & 0xFF);

        // Set address
        _writeBytes(
            DWM1000ConstantsClass::OTP_IF.id,
            DWM1000ConstantsClass::OTP_ADDR.id, 
            addressBytes,
            DWM1000ConstantsClass::OTP_ADDR.length
        );

        // Switch into read mode
        _writeByte(
            DWM1000ConstantsClass::OTP_IF.id,
            DWM1000ConstantsClass::OTP_CTRL.id,
            0x03 // OTPRDEN | OTPREAD
        );
        _writeByte(
            DWM1000ConstantsClass::OTP_IF.id,
            DWM1000ConstantsClass::OTP_CTRL.id,
            0x01 // OTPRDEN
        );

        // Read value/block - 4 bytes
        _readBytes(
            DWM1000ConstantsClass::OTP_IF.id,
            DWM1000ConstantsClass::OTP_RDAT.id,
            data,
            DWM1000ConstantsClass::OTP_RDAT.length
        );

        // End read mode
        _writeByte(
            DWM1000ConstantsClass::OTP_IF.id,
            DWM1000ConstantsClass::OTP_CTRL.id,
            0x00
        );

    }

    void DWM1000Class::_writeRegister(byte cmd, uint16_t offset, uint32_t data, uint16_t data_size) {
        byte dataBytes[data_size];
        _writeValueToBytes(dataBytes, data, data_size);
        _writeBytes(cmd, offset, dataBytes, data_size);
    }

    void DWM1000Class::_writeByte(byte cmd, uint16_t offset, byte data) {
        _writeBytes(cmd, offset, &data, 1);
    }

    void DWM1000Class::_writeBytes(byte cmd, uint16_t offset, byte data[], uint16_t data_size) {
        byte header[3];
        uint8_t header_length = 1;

        if (offset == DWM1000ConstantsClass::SPI_HEADER_NO_SUB) {
            header[0] = DWM1000ConstantsClass::SPI_HEADER_WRITE | cmd;
        } else {
            header[0] = DWM1000ConstantsClass::SPI_HEADER_WRITE_SUB | cmd;

            if (offset < 128) {
                header[1] = (byte) offset;
                header_length++;
            } else {
                header[1] = DWM1000ConstantsClass::SPI_HEADER_RW_SUB_EXT | (byte) offset;
                header[2] = (byte)(offset >> 7);
                header_length += 2;
            }
        }

        _comms->write(header_length, header, data_size, data);
    }

    void DWM1000Class::_writeValueToBytes(byte data[], uint64_t val, uint8_t n) {
        for (uint8_t index = 0; index < n; index++) {
            data[index] = ((val >> (index * 8)) & 0xFF);
        }
    }

    void DWM1000Class::_writeBit(byte bitRegister, uint16_t RegisterOffset, uint16_t bitRegister_LEN, uint16_t selectedBit, boolean value) {
        uint16_t idx;
        uint8_t bitPosition;

        idx = selectedBit / 8;

        if (idx >= bitRegister_LEN) {
            return; // TODO proper error handling: out of bounds
        }

        byte targetByte;
        memset(&targetByte, 0, 1);
        bitPosition = selectedBit % 8;
        _readBytes(bitRegister, RegisterOffset + idx, &targetByte, 1);

        if (value) {
            bitSet(targetByte, bitPosition);
        } else {
            bitClear(targetByte, bitPosition);
        }

        if (RegisterOffset == DWM1000ConstantsClass::SPI_HEADER_NO_SUB) {
            RegisterOffset = 0x00;
        }

        _writeBytes(bitRegister, RegisterOffset + idx, &targetByte, 1);
    }

    void DWM1000Class::_manageLDE() {
        // Transfwer any LDO tune values
        byte ldoTune[DWM1000ConstantsClass::OTP_RDAT.length];
        uint16_t LDOTUNE_ADDRESS = 0x04;
        _readBytesOTP(LDOTUNE_ADDRESS, ldoTune);

        if (ldoTune[0] != 0) {
            // TODO tuning available. Copy over to RAM. Use OTP_LDO bit
        }
        // Tell the chip to load the LDE microcode
        // TODO remove clock related code (PMSC_CTRL) as handled separately
        byte pmscctrl0[DWM1000ConstantsClass::PMSC_CTRL0.length];
        byte otpctrl[DWM1000ConstantsClass::OTP_CTRL.length];

        memset(pmscctrl0, 0, DWM1000ConstantsClass::PMSC_CTRL0.length);
        memset(otpctrl, 0, DWM1000ConstantsClass::OTP_CTRL.length);

        _readBytes(
            DWM1000ConstantsClass::PMSC.id,
            DWM1000ConstantsClass::PMSC_CTRL0.id,
            pmscctrl0,
            DWM1000ConstantsClass::PMSC_CTRL0.length
        );

        _readBytes(
            DWM1000ConstantsClass::OTP_IF.id,
            DWM1000ConstantsClass::OTP_CTRL.id,
            otpctrl,
            DWM1000ConstantsClass::OTP_CTRL.length
        );

        pmscctrl0[0] = 0x01;
        pmscctrl0[1] = 0x03;
        otpctrl[0] = 0x00;
        otpctrl[1] = 0x80;

        _writeBytes(
            DWM1000ConstantsClass::PMSC.id,
            DWM1000ConstantsClass::PMSC_CTRL0.id,
            pmscctrl0,
            2
        );
        
        // uCode
        enableClock(DWM1000ConstantsClass::LDE_CLOCK);

    }

    void DWM1000Class::_readNetworkIdAndDeviceAddress() {
        _readBytes(
            DWM1000ConstantsClass::PANADR.id,
            DWM1000ConstantsClass::SPI_HEADER_NO_SUB,
            _networkAndAddress,
            DWM1000ConstantsClass::PANADR.length
        );
    }

    void DWM1000Class::_readSystemConfigurationRegister() {
        _readBytes(
            DWM1000ConstantsClass::SYS_CFG.id,
            DWM1000ConstantsClass::SPI_HEADER_NO_SUB,
            _syscfg,
            DWM1000ConstantsClass::SYS_CFG.length
        );
    }

    void DWM1000Class::_readChannelControlRegister() {
        _readBytes(
            DWM1000ConstantsClass::CHAN_CTRL.id,
            DWM1000ConstantsClass::SPI_HEADER_NO_SUB,
            _chanctrl,
            DWM1000ConstantsClass::CHAN_CTRL.length
        );
    }

    void DWM1000Class::_readTransmitFrameControlRegister() {
        _readBytes(
            DWM1000ConstantsClass::TX_FCTRL.id,
            DWM1000ConstantsClass::SPI_HEADER_NO_SUB,
            _txfctrl,
            DWM1000ConstantsClass::TX_FCTRL.length
        );
    }

    void DWM1000Class::_readSystemEventStatusRegister() {
        _readBytes(
            DWM1000ConstantsClass::SYS_STATUS.id,
            DWM1000ConstantsClass::SPI_HEADER_NO_SUB,
            _sysstatus,
            DWM1000ConstantsClass::SYS_STATUS.length
        );
    }
}