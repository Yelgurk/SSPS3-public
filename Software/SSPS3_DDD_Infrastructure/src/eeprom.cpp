#include "../include/eeprom.hpp"

EEPROM::EEPROM(uint8_t sda, uint8_t scl)
{
    this->itcw = new TwoWire(0);
    this->itcw->setPins((this->_sda = sda), (this->_scl = scl));
    this->itcw->begin(this->_sda, this->_scl, 100000);
}

EEPROM::EEPROM(TwoWire* itcw)
{
    this->itcw = itcw;
}

boolean EEPROM::_readByte(uint16_t address, uint8_t* byte)
{
    this->itcw->beginTransmission(EEI2Caddr);

    this->itcw->write(highByte(address));
    this->itcw->write(lowByte(address));
    this->itcw->endTransmission();
    delay(4);

    this->itcw->requestFrom(EEI2Caddr, 1);
    *byte = this->itcw->read();

    return true;
}

boolean EEPROM::_writeByte(uint16_t address, uint8_t* byte)
{
    this->itcw->beginTransmission(EEI2Caddr);

	this->itcw->write(highByte(address));
	this->itcw->write(lowByte(address));
	this->itcw->write(*byte);     

	this->itcw->endTransmission();
    delay(10);

    return true;
}

boolean EEPROM::isConnected()
{
    this->itcw->beginTransmission(EEI2Caddr);
    return (this->itcw->endTransmission() == 0);
}

boolean EEPROM::_isAddrBitBusy(ObjectMainInfo* newObj, ObjectMainInfo* inVec)
{
    return !inVec->IsBit ? true : (inVec->BitPosition == newObj->BitPosition);
}

boolean EEPROM::_isAddrRangeIntersection(ObjectMainInfo* newObj, ObjectMainInfo* inVec)
{
    return !(
        (newObj->EEAddressBegin >= inVec->EEAddressBegin + (uint32_t)inVec->Size) ||
        (newObj->EEAddressBegin + (uint32_t)newObj->Size < inVec->EEAddressBegin)
    );
}

boolean EEPROM::_isFreeFor(ObjectMainInfo* newObj)
{
    for (ObjectMainInfo* inVec : this->ObjectsCollection)
        if (_isAddrRangeIntersection(newObj, inVec))
            if (!newObj->IsBit || _isAddrBitBusy(newObj, inVec))
                return false;

    return true;
}

boolean EEPROM::_isReg(ObjectMainInfo* obj)
{
    for (ObjectMainInfo* inVec : this->ObjectsCollection)
        if (obj == inVec)
            return true;

    return false;
}

boolean EEPROM::RegObjectInEE(ObjectMainInfo* Object)
{
    if (Object && _isFreeFor(Object))
    {
        ObjectsCollection.push_back(Object);
        return true;
    }
    return false;
}

boolean EEPROM::ReadObjectFromEE(ObjectMainInfo* Object)
{
    if (Object && _isReg(Object))
    {
        if (Object->IsBit && Object->Size == 1)
        {
            static uint8_t container = 0;
            _readByte (Object->EEAddressBegin, &container);
            *Object->RAMAddressBegin = (uint8_t)(container & (1 << Object->BitPosition) ? 1 : 0);
            return true;
        }
        else if (!Object->IsBit)
        {
            for (uint32_t index = 0; index < Object->Size; index++)
                _readByte (Object->EEAddressBegin + index, &Object->RAMAddressBegin[index]);
            return true;
        }
    }
    return false;
}

boolean EEPROM::WriteObjectIntoEE(ObjectMainInfo* Object)
{
    if (Object && _isReg(Object))
    {
        if (Object->IsBit && Object->Size == 1)
        {
            static uint8_t container = 0;
            _readByte (Object->EEAddressBegin, &container);

            container = *Object->RAMAddressBegin > 0 ?
                container |= (1 << Object->BitPosition) :
                container &= ~(1 << Object->BitPosition);
            _writeByte (Object->EEAddressBegin, &container);
            return true;
        }
        else if (!Object->IsBit)
        {
            for (uint32_t index = 0; index < Object->Size; index++)
                _writeByte (Object->EEAddressBegin + index, &Object->RAMAddressBegin[index]);
            return true;
        }
    }
    return false;
}