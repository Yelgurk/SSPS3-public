#include <Arduino.h>
#include <Wire.h>
#include "../../SSPS3_DDD_Domain/include/objectUnitModel.hpp"

#ifndef eeprom_hpp
#define eeprom_hpp

using namespace std;

#define EEI2Caddr   0x50

class EEPROM
{
public: //must be private. opened for test
    TwoWire *itcw;
    boolean InitSuccess = false;
    uint8_t _sda = 0,
            _scl = 0;

    boolean _isAddrBitBusy(ObjectMainInfo* newObj, ObjectMainInfo* inVec);
    boolean _isAddrRangeIntersection(ObjectMainInfo* newObj, ObjectMainInfo* inVec);
    boolean _isFreeFor(ObjectMainInfo* newObj);
    boolean _isReg(ObjectMainInfo* obj);
    vector<ObjectMainInfo*> ObjectsCollection;

    boolean _readByte(uint16_t address, uint8_t* byte);
    boolean _writeByte(uint16_t address, uint8_t* byte);

public:
    EEPROM(uint8_t sda, uint8_t scl);
    EEPROM(TwoWire* itcw);
    boolean isConnected();

    boolean RegObjectInEE(ObjectMainInfo* Object);
    boolean ReadObjectFromEE(ObjectMainInfo* Object);
    boolean WriteObjectIntoEE(ObjectMainInfo* Object);
};

#endif