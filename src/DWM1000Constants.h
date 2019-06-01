#ifndef _DWM1000_CONSTANTS_H_
#define _DWM1000_CONSTANTS_H_
#include <Arduino.h>

#define NOTHING 0x00
#define MIN_SPI_SPEED 2000000 // 2 MHz
#define ESP32_SPI_SPEED 20000000 // 20 MHz
namespace Femto {
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
  public:
    static constexpr byte SPI_HEADER_READ = 0x00;
    static constexpr byte SPI_HEADER_WRITE = 0x80;
    static constexpr byte SPI_HEADER_READ_SUB = 0x40;
    static constexpr byte SPI_HEADER_WRITE_SUB = 0xC0;
    static constexpr byte SPI_HEADER_RW_SUB_EXT = 0x80;
    static constexpr byte SPI_HEADER_NO_SUB = 0xFF;

    static constexpr byte SYS_AUTO_CLOCK = 0x00;
    static constexpr byte SYS_XTI_CLOCK = 0x01;
    static constexpr byte SYS_PLL_CLOCK = 0x02;
    static constexpr byte TX_PLL_CLOCK = 0x20;
    static constexpr byte LDE_CLOCK = 0x03;

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
    // ------------------------------------- OFFSET in Register
    static constexpr DWM1000Reg EC_CTRL = {   0x00,   4 }; //  RW      External clock synchronisation counter configuration
    static constexpr DWM1000Reg EC_RXTC = {   0x04,   4 }; //  RO      External clock counter captured on RMARKER
    static constexpr DWM1000Reg EC_GOLP = {   0x08,   4 }; //  RO      External clock offset to first path 1 GHz counter
    static constexpr uint16_t PLLLDT_BIT =    0x02;        //  Bit
    // -------------------------------------
    static constexpr DWM1000Reg ACC_MEM = {   0x25, 4046}; //  RO      Read access to accumulator data
    static constexpr DWM1000Reg GPIO_CTRL ={  0x26,  44 }; //  RW      Peripheral register bus 1 access - GPIO control
    static constexpr DWM1000Reg DRX_CONF ={   0x27,  44 }; //  RW      Digital Receiver configuration
    static constexpr DWM1000Reg RF_CONF = {   0x28,  58 }; //  RW      Analog RF Configuration
    //                                        0x29         //  Reserved
    static constexpr DWM1000Reg TX_CAL =  {   0x2A,  52 }; //  RW      Transmitter calibration block

    static constexpr DWM1000Reg FS_CTRL = {   0x2B,  21 }; //  RW      Frequency synthesiser control block
    // -------------------------------------  OFFSET in Register
    static constexpr DWM1000Reg FS_RES1 = {   0x00,   7 }; //  RW      Frequency synthesiser – Reserved area 1
    static constexpr DWM1000Reg FS_PLLCFG={   0x07,   4 }; //  RW      Frequency synthesiser – PLL configuration
    static constexpr DWM1000Reg FS_PLLTUNE={  0x0B,   1 }; //  RW      Frequency synthesiser – PLL Tuning
    static constexpr DWM1000Reg FS_RES2 = {   0x0C,   1 }; //  RW      Frequency synthesiser – Reserved area 2
    static constexpr DWM1000Reg FS_XTALT ={   0x0E,   1 }; //  RW      Frequency synthesiser – Crystal trim. Bits 7:5 must always be set to binary “011”. Failure to maintain this value will result in DW1000 malfunction.
    static constexpr DWM1000Reg FS_RES3 = {   0x0F,   6 }; //  RW      Frequency synthesiser – Reserved area 3
    // -------------------------------------
    
    static constexpr DWM1000Reg AON =     {   0x2C,  12 }; //  RW      Always-On register set
    // -------------------------------------  OFFSET in Register
    static constexpr DWM1000Reg AON_WCFG ={   0x00,   2 }; //  RW      AON Wakeup Configuration Register
    static constexpr DWM1000Reg AON_CTRL ={   0x02,   1 }; //  RW      AON Control Register
    static constexpr DWM1000Reg AON_RDAT ={   0x03,   1 }; //  RW      AON Direct Access Read Data Result
    static constexpr DWM1000Reg AON_ADDR ={   0x04,   1 }; //  RW      AON Direct Access Address
    //                                        0x05         //  Reserved
    static constexpr DWM1000Reg AON_CFG0 ={   0x06,   4 }; //  RW      AON Configuration Register 0
    static constexpr DWM1000Reg AON_CFG1 ={   0x0A,   2 }; //  RW      AON Configuration Register 1
    // -------------------------------------
    static constexpr DWM1000Reg OTP_IF =  {   0x2D,  18 }; //  RW      One Time Programmable Memory Interface
    // -------------------------------------  OFFSET in Register
    static constexpr DWM1000Reg OTP_WDAT = {  0x00,   4 }; //  RW      OTP Write Data
    static constexpr DWM1000Reg OTP_ADDR = {  0x04,   2 }; //  RW      OTP Address
    static constexpr DWM1000Reg OTP_CTRL = {  0x06,   2 }; //  RW      OTP Control
    static constexpr DWM1000Reg OTP_STAT = {  0x08,   2 }; //  RW      OTP Status
    static constexpr DWM1000Reg OTP_RDAT = {  0x0A,   4 }; //  R       OTP Read Data
    static constexpr DWM1000Reg OTP_SRDAT ={  0x0E,   4 }; //  RW      OTP SR Read Data
    static constexpr DWM1000Reg OTP_SF =   {  0x12,   1 }; //  RW      OTP Special Function
    // -------------------------------------
    static constexpr DWM1000Reg LDE_CTRL ={   0x2E,   0 }; //  RW      Leading edge detection control block (No size)
    static constexpr DWM1000Reg DIG_DIAG ={   0x2F,  41 }; //  RW      Digital Diagnostics Interface
    //                                        0x30         //  Reserved
    //                                        0x31         //  Reserved
    //                                        0x32         //  Reserved
    //                                        0x33         //  Reserved
    //                                        0x34         //  Reserved
    //                                        0x35         //  Reserved
    static constexpr DWM1000Reg PMSC =    {   0x36,  48 }; //  RW      Power Management System Control Block
    // -------------------------------------  OFFSET in Register
    static constexpr DWM1000Reg PMSC_CTRL0 = {0x00,   4 }; //  RW      PMSC Control Register 0
    static constexpr DWM1000Reg PMSC_CTRL1 = {0x04,   4 }; //  RW      PMSC Control Register 1
    static constexpr DWM1000Reg PMSC_RES1  = {0x08,   4 }; //  RW      PMSC Reserved Area 1
    static constexpr DWM1000Reg PMSC_SNOZT = {0x0C,   1 }; //  RW      PMSC Snooze Time Register
    static constexpr DWM1000Reg PMSC_RES2  = {0x10,  22 }; //  RW      PMSC Reserved Area 2
    static constexpr DWM1000Reg PMSC_TXFSEQ ={0x26,   2 }; //  RW      PMSC Fine Grain TX Sequencing Control
    static constexpr DWM1000Reg PMSC_LEDC  = {0x28,   4 }; //  RW      PMSC LED Control Register
    static constexpr DWM1000Reg PMSC_SOFTRESET = { 0x03, 1}; // ???
    // -------------------------------------
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
}
extern Femto::DWM1000ConstantsClass DWM1000Constants;

#endif