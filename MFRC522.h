/******************************************************************************/
/*!
  MFRC522.h - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
  Based on code Dr.Leong (WWW.B2CQSHOP.COM) and Miguel Balboa (circuitito.com).

  Created by Bjarte Johansen on 2013.09.23
*/
/******************************************************************************/
#include <Arduino.h>
#include <SPI.h>



/******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_LEN 16   // Maximum length of an array.

// MF522 MFRC522 error codes.
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2

// MF522 Command word
#define MFRC522_IDLE              0x00               //NO action; Cancel the current command
#define MFRC522_MEM               0x01               //Store 25 byte into the internal buffer.
#define MFRC522_GENID             0x02               //Generates a 10 byte random ID number.
#define MFRC522_CALCCRC           0x03               //CRC Calculate or selftest.
#define MFRC522_TRANSMIT          0x04               //Transmit data
#define MFRC522_NOCMDCH           0x07               //No command change.
#define MFRC522_RECEIVE           0x08               //Receive Data
#define MFRC522_TRANSCEIVE        0x0C               //Transmit and receive data,
#define MFRC522_AUTHENT           0x0E               //Authentication Key
#define MFRC522_SOFTRESET         0x0F               //Reset

// Mifare_One card command word
# define MF_REQIDL          0x26               // find the antenna area does not enter hibernation
# define MF_REQALL          0x52               // find all the cards antenna area
# define MF_ANTICOLL        0x93               // anti-collision
# define MF_SElECTTAG       0x93               // election card
# define MF_AUTHENT1A       0x60               // authentication key A
# define MF_AUTHENT1B       0x61               // authentication key B
# define MF_READ            0x30               // Read Block
# define MF_WRITE           0xA0               // write block
# define MF_DECREMENT       0xC0               // debit
# define MF_INCREMENT       0xC1               // recharge
# define MF_RESTORE         0xC2               // transfer block data to the buffer
# define MF_TRANSFER        0xB0               // save the data in the buffer
# define MF_HALT            0x50               // Sleep


//And MF522 The error code is returned when communication
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2

//------------------ MFRC522 registers---------------
//Page 0:Command and Status
#define     Reserved00            0x00
#define     CommandReg            0x01
#define     CommIEnReg            0x02
#define     DivlEnReg             0x03
#define     CommIrqReg            0x04
#define     DivIrqReg             0x05
#define     ErrorReg              0x06
#define     Status1Reg            0x07
#define     Status2Reg            0x08
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     Reserved01            0x0F
//Page 1:Command
#define     Reserved10            0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     Reserved11            0x1A
#define     Reserved12            0x1B
#define     MifareReg             0x1C
#define     Reserved13            0x1D
#define     Reserved14            0x1E
#define     SerialSpeedReg        0x1F
//Page 2:CFG
#define     Reserved20            0x20
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     Reserved21            0x23
#define     ModWidthReg           0x24
#define     Reserved22            0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsPReg	          0x28
#define     ModGsPReg             0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
//Page 3:TestRegister
#define     Reserved30            0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39
#define     TestDAC2Reg           0x3A
#define     TestADCReg            0x3B
#define     Reserved31            0x3C
#define     Reserved32            0x3D
#define     Reserved33            0x3E
#define     Reserved34	      	  0x3F
//-----------------------------------------------

class MFRC522 {
 public:
  MFRC522(int sad, int reset);

  bool isCard();
  bool readCardSerial();
  uint8_t getFirmwareVersion();

  void begin();
  void reset();
  void writeToRegister(uint8_t addr, uint8_t val);
  void antennaOn(void);
  uint8_t readFromRegister(uint8_t addr);
  void setBitMask(uint8_t reg, uint8_t mask);
  void clearBitMask(uint8_t reg, uint8_t mask);
  void calculateCRC(uint8_t *pIndata, uint8_t len, uint8_t *pOutData);
  uint8_t requestCard(uint8_t mode, uint8_t *type);
  uint8_t commandCard(uint8_t command, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen);
  uint8_t anticollision(uint8_t *serial);
  uint8_t selectTag(uint8_t *serial);
  uint8_t authenticate(uint8_t mode, uint8_t block, uint8_t *key, uint8_t *serial);
  uint8_t readFromCard(uint8_t blockAddr, uint8_t *recvData);
  uint8_t writeToCard(uint8_t blockAddr, uint8_t *writeData);
  void haltCard();

 private:
  uint8_t _sad, _reset;
};
