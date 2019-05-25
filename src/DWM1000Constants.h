#ifndef _DWM1000CONSTANTS_H_
#define _DWM1000CONSTANTS_H_
#include <Arduino.h>

#define NOTHING 0x00

struct DWM1000Reg
{
    uint16_t id;
    uint16_t length;
};

// See dw1000_user_manual_2.03.pdf
/*
Note the “Type” mnemonic in the table above has the following meaning:
• RO – Read Only,
• RW – Read and Write,
• SRW – Special type of Read and Write, refer to individual register description for details,
• ROD –Read Only part of RX Double buffered swinging set of RX frame related information,
• RWD – Read and Write part of RX Double buffered swinging set of RX frame related information.
*/

class DWM1000ConstantsClass {

  //                                        ID      length   Type    Description
  static constexpr DWM1000Reg DEV_ID =  {   0x00,   4 }; //  RO      Device Identifier - includes device type and revision info
  static constexpr DWM1000Reg EUI =     {   0x01,   8 }; //  RW      Extended Unique Identifier
  //                                        0x02         //  Reserved
  static constexpr DWM1000Reg PANADR =  {   0x03,   4 }; //  RW      PAN Identifier and Short Address
  static constexpr DWM1000Reg SYS_CFG = {   0x04,   4 }; //  RW      System Configuration bitmap
  //                                        0x05         //  Reserved
  static constexpr DWM1000Reg SYS_TIME ={   0x06,   5 }; //  RO      System Time Counter (40-bit)
  //                                        0x07         //  Reserved
  static constexpr DWM1000Reg TX_FCTRL ={   0x08,   5 }; //  RW      Transmit Frame Control
  static constexpr DWM1000Reg TX_BUFFER={   0x09, 1024}; //  RW      Transmit Data Buffer
  static constexpr DWM1000Reg DX_TIME = {   0x0A,   5 }; //  RW      Delayed Send or Receive Time (40-bit)
  //                                        0x0B         //  Reserved
  static constexpr DWM1000Reg RX_FWTO = {   0x0C,   2 }; //  RW      Receive Frame Wait Timeout Period
  static constexpr DWM1000Reg SYS_CTL = {   0x0D,   4 }; //  SRW     System Control Register
  static constexpr DWM1000Reg SYS_MASK ={   0x0E,   4 }; //  RW      System Event Mask Register
  static constexpr DWM1000Reg SYS_STATUS={  0x0F,   5 }; //  RW      System Event Status 
  static constexpr DWM1000Reg RX_FINFO ={   0x10,   4 }; //  ROD     RX Frame Information (in double buffer set)
  static constexpr DWM1000Reg RX_BUFFER={   0x11, 1024}; //  RWD     Receive Data Buffer (in double buffer set)
  static constexpr DWM1000Reg RX_FQUAL ={   0x12,   8 }; //  ROD     Rx Frame Quality information (in double buffer set)
  static constexpr DWM1000Reg RX_TTCKI ={   0x13,   4 }; //  ROD     Receiver Time Tracking Interval (in double buffer set)
  static constexpr DWM1000Reg RX_TTCKO ={   0x14,   5 }; //  ROD     Receiver Time Tracking Offset (in double buffer set)

  static constexpr DWM1000Reg RX_TIME = {   0x15,  14 }; //  ROD     Receive Message Time of Arrival (in double buffer set)
  //                                        0x16         //  Reserved
  static constexpr DWM1000Reg TX_TIME = {   0x17,  10 }; //  RO      Transmit Message Time of Sending
  static constexpr DWM1000Reg TX_ANTD = {   0x18,   2 }; //  RW      16-bit Delay from Transmit to Antenna
  static constexpr DWM1000Reg SYS_STATE={   0x19,   5 }; //  RO      System State information
  static constexpr DWM1000Reg ACK_RESP_T={  0x1A,   4 }; //  RW      Acknowledgement Time and Response Time
  //                                        0x1B         //  Reserved
  //                                        0x1C         //  Reserved
  static constexpr DWM1000Reg RX_SNIFF ={   0x1D,   4 }; //  RW      Pulsed Preamble Reception Configuration
  static constexpr DWM1000Reg TX_POWER ={   0x1E,   4 }; //  RW      TX Power Control
  static constexpr DWM1000Reg CHAN_CTRL={   0x1F,   4 }; //  RW      Channel Control
  //                                        0x20         //  Reserved
  static constexpr DWM1000Reg USR_SFD = {   0x21,  41 }; //  RW      User-specified short/long TX/RX SFD sequences
  //                                        0x22         //  Reserved
  static constexpr DWM1000Reg AGC_CTRL ={   0x23,  32 }; //  RW      Automatic Gain Control configuration
  static constexpr DWM1000Reg EXT_SYNC ={   0x24,  12 }; //  RW      External synchronisation control
  static constexpr DWM1000Reg ACC_MEM = {   0x25, 4046}; //  RO      Read access to accumulator data
  static constexpr DWM1000Reg GPIO_CTRL ={  0x26,  44 }; //  RW      Peripheral register bus 1 access - GPIO control
  static constexpr DWM1000Reg DRX_CONF ={   0x27,  44 }; //  RW      Digital Receiver configuration
  static constexpr DWM1000Reg RF_CONF = {   0x28,  58 }; //  RW      Analog RF Configuration
  //                                        0x29         //  Reserved
  static constexpr DWM1000Reg TX_CAL =  {   0x2A,  52 }; //  RW      Transmitter calibration block
  static constexpr DWM1000Reg FS_CTRL = {   0x2B,  21 }; //  RW      Frequency synthesiser control block
  static constexpr DWM1000Reg AON =     {   0x2C,  12 }; //  RW      Always-On register set
  static constexpr DWM1000Reg OTP_IF =  {   0x2D,  18 }; //  RW      One Time Programmable Memory Interface
  static constexpr DWM1000Reg LDE_CTRL ={   0x2E,   0 }; //  RW      Leading edge detection control block (No size)
  static constexpr DWM1000Reg DIG_DIAG ={   0x2F,  41 }; //  RW      Digital Diagnostics Interface
  //                                        0x30         //  Reserved
  //                                        0x31         //  Reserved
  //                                        0x32         //  Reserved
  //                                        0x33         //  Reserved
  //                                        0x34         //  Reserved
  //                                        0x35         //  Reserved
  static constexpr DWM1000Reg PMSC =    {   0x36,  48 }; //  RW      Power Management System Control Block
  //                                        0x37         //  Reserved
  //                                        0x38         //  Reserved
  //                                        0x39         //  Reserved
  //                                        0x3A         //  Reserved
  //                                        0x3B         //  Reserved
  //                                        0x3C         //  Reserved
  //                                        0x3D         //  Reserved
  //                                        0x3E         //  Reserved
  //                                        0x3F         //  Reserved

};

extern DWM1000ConstantsClass DWM1000Constants;

#endif