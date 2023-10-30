#include "../include/objectUnitModel.hpp"

template <typename T>
ObjectUnitModel<T>::ObjectUnitModel()
{
    this->ObjectInfo = new ObjectMainInfo{
        reinterpret_cast<uint8_t*>(&this->BaseValue),
        VarTypeSize()
    };
}

template <typename T>
ObjectUnitModel<T>::ObjectUnitModel(uint16_t EEAddressBegin) : ObjectUnitModel()
{
    this->ObjectInfo->EEAddressBegin = EEAddressBegin;
    this->ObjectInfo->ForAllocInEE = true;
}

template <typename T>
ObjectUnitModel<T>::ObjectUnitModel(uint16_t EEAddress, uint8_t BitPosition) : ObjectUnitModel(EEAddress)
{
    this->ObjectInfo->IsBit = true;
    this->ObjectInfo->BitPosition = BitPosition;
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::_readFromEE()
{
    if (!IsAllocatedInEE)
        return this;

    if (ReadFromEEPtr && (*ReadFromEEPtr)(this->_eeSerializeOrNullptr()))
        this->Value = this->BaseValue;

    return this;
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::_writeIntoEE()
{
    if (!IsAllocatedInEE)
        return this;

    if (WriteInEEPtr != nullptr && (*WriteInEEPtr)(this->_eeSerializeOrNullptr()))
        this->Value = this->BaseValue;

    return this;
}

template <typename T>
ObjectMainInfo* ObjectUnitModel<T>::_eeSerializeOrNullptr()
{
    if (IsAllocatedInEE)
        return this->ObjectInfo;
    else
        return nullptr;
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::TryAllocateInEE()
{
    if (IsAllocatedInEE)
        return this;

    if (this->ObjectInfo->ForAllocInEE &&
        RegInEEPtr &&
        (*RegInEEPtr)(this->ObjectInfo))
        this->IsAllocatedInEE = true;

    return this;
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::SetRegInEE(SomeVarFunction RegInEE)
{
    this->RegInEE = RegInEE;
    this->RegInEEPtr = &this->RegInEE;

    return this;
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::SetWriteInEE(SomeVarFunction WriteInEE)
{
    this->WriteInEE = WriteInEE;
    this->WriteInEEPtr = &this->WriteInEE;

    return this;
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::SetReadFromEE(SomeVarFunction ReadFromEE)
{
    this->ReadFromEE = ReadFromEE;
    this->ReadFromEEPtr = &this->ReadFromEE;

    return this;
}

template <typename T>
boolean ObjectUnitModel<T>::AllocatedInEE()
{
    return this->IsAllocatedInEE;
}

template <typename T>
T ObjectUnitModel<T>::Base()
{
    return this->BaseValue;
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::AcceptChanges(T NewValue)
{
    this->Value = NewValue;
    return this->AcceptChanges();
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::AcceptChanges()
{
    this->BaseValue = !this->ObjectInfo->IsBit ? this->Value : (this->Value > 0 ? 1 : 0);
    return this->_writeIntoEE();
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::CancelChanges()
{
    return this->LoadValue();
}

template <typename T>
ObjectUnitModel<T>* ObjectUnitModel<T>::LoadValue()
{
    return this->_readFromEE();
}

template <typename T>
uint8_t ObjectUnitModel<T>::VarTypeSize()
{
    return sizeof(T);
}

template class ObjectUnitModel<int8_t>;
template class ObjectUnitModel<int16_t>;
template class ObjectUnitModel<int32_t>;
template class ObjectUnitModel<int64_t>;
template class ObjectUnitModel<uint8_t>;
template class ObjectUnitModel<uint16_t>;
template class ObjectUnitModel<uint32_t>;
template class ObjectUnitModel<uint64_t>;
template class ObjectUnitModel<double_t>;