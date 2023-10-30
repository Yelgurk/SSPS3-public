#include <Arduino.h>
#include <vector>
#include <numeric>

#ifndef objectUnitModel_hpp
#define objectUnitModel_hpp

using namespace std;

struct ObjectMainInfo
{
    uint8_t* RAMAddressBegin;
    uint8_t Size;
    uint16_t EEAddressBegin;
    boolean ForAllocInEE;
    boolean IsBit;
    uint8_t BitPosition;

    ObjectMainInfo(
        uint8_t* RAMAddressBegin,
        uint16_t Size,
        uint16_t EEAddressBegin = 0,
        boolean ForAllocInEE = false,
        boolean IsBit = false,
        uint8_t BitPosition = 0)
    {
        this->RAMAddressBegin = RAMAddressBegin;
        this->Size = Size;
        this->EEAddressBegin = EEAddressBegin;
        this->ForAllocInEE = ForAllocInEE;
        this->IsBit = IsBit;
        this->BitPosition = BitPosition;
    }
};

typedef function<boolean(ObjectMainInfo* ObjectMainInfo)> SomeVarFunction;

template <typename T>
class ObjectUnitModel
{
public: //must be private. opened for test
    T BaseValue;
    ObjectMainInfo* ObjectInfo;
    boolean IsAllocatedInEE = false;

    SomeVarFunction RegInEE;
    SomeVarFunction* RegInEEPtr = nullptr;

    SomeVarFunction WriteInEE;
    SomeVarFunction* WriteInEEPtr = nullptr;

    SomeVarFunction ReadFromEE;
    SomeVarFunction* ReadFromEEPtr = nullptr; 

    ObjectUnitModel* _readFromEE();
    ObjectUnitModel* _writeIntoEE();
    ObjectMainInfo* _eeSerializeOrNullptr();
    
public:
    T Value;
    T Base();

    ObjectUnitModel();
    ObjectUnitModel(uint16_t EEAddress);
    ObjectUnitModel(uint16_t EEAddress, uint8_t BitPosition);
    ObjectUnitModel* SetRegInEE(SomeVarFunction RegInEE);
    ObjectUnitModel* SetWriteInEE(SomeVarFunction WriteInEE);
    ObjectUnitModel* SetReadFromEE(SomeVarFunction ReadFromEE);
    
    boolean AllocatedInEE();
    ObjectUnitModel* TryAllocateInEE();
    ObjectUnitModel* AcceptChanges(T NewValue);
    ObjectUnitModel* AcceptChanges();
    ObjectUnitModel* CancelChanges(); 
    ObjectUnitModel* LoadValue();
    uint8_t VarTypeSize();
};

#endif