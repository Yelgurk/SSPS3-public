#include "../include/IOService.hpp"

IOService::IOService(uint8_t sda, uint8_t scl)
{
    this->itcw = new TwoWire(0);
    this->itcw->setPins(sda, scl);
    this->itcw->begin(sda, scl, 100000);
}

IOService::IOService(TwoWire* itcw)
{
    this->itcw = itcw;
}

void IOService::_initVariables()
{
    _initPcfIO(this->Relay_1, 7, ControlMode::Output);
    _initPcfIO(this->Relay_2, 6, ControlMode::Output);
    _initPcfIO(this->Relay_3, 4, ControlMode::Output);
    _initPcfIO(this->Relay_4, 5, ControlMode::Output);
    _initPcfIO(this->Relay_5, 3, ControlMode::Output);
    _initPcfIO(this->Relay_6, 2, ControlMode::Output);
    _initPcfIO(this->Relay_7, 1, ControlMode::Output);
    _initPcfIO(this->Relay_8, 0, ControlMode::Output);

    _initPcfIO(this->OptIn_1, 3, ControlMode::Input);
    _initPcfIO(this->OptIn_2, 2, ControlMode::Input);
    _initPcfIO(this->OptIn_3, 1, ControlMode::Input);
    _initPcfIO(this->OptIn_4, 0, ControlMode::Input);
    _initPcfIO(this->OptIn_5, 4, ControlMode::Input);
    _initPcfIO(this->OptIn_6, 5, ControlMode::Input);
    _initPcfIO(this->OptIn_7, 6, ControlMode::Input);
    _initPcfIO(this->OptIn_8, 7, ControlMode::Input);

    _initAdsIn(this->vAnIn_1, 0);
    _initAdsIn(this->vAnIn_2, 1);
    _initAdsIn(this->vAnIn_3, 2);
    _initAdsIn(this->vAnIn_4, 3);

    _initEspIO(this->LCD_BL, 42, ControlMode::Output);
    _initEspIO(this->RF_UHF, 14, ControlMode::Output);
    _initEspIO(this->SIMCOM, 41, ControlMode::Output);

    InputControls.push_back(OptIn_1);
    InputControls.push_back(OptIn_2);
    InputControls.push_back(OptIn_3);
    InputControls.push_back(OptIn_4);
    InputControls.push_back(OptIn_5);
    InputControls.push_back(OptIn_6);
    InputControls.push_back(OptIn_7);
    InputControls.push_back(OptIn_8);
    InputControls.push_back(vAnIn_1);
    InputControls.push_back(vAnIn_2);
    InputControls.push_back(vAnIn_3);
    InputControls.push_back(vAnIn_4);

    Relay_Heater        = *&Relay_8;
    Relay_Mixer         = *&Relay_7;
    Relay_WaterJ        = *&Relay_6;
    Relay_Blowgun       = *&Relay_5;
    
    OptIn_WaterJ        = *&OptIn_4;
    OptIn_StopBTN       = *&OptIn_5;
    OptIn_MixerCrash    = *&OptIn_6;
    OptIn_380V          = *&OptIn_7;
    OptIn_Blowgun       = *&OptIn_8;

    vAnIn_Battery       = *&vAnIn_3;
    vAnIn_LiqTempC      = *&vAnIn_1;

    OptIn_StopBTN->setReversed(true);
}

void IOService::_subscribeToADS(ControlUnitModel<int16_t>* &control, ADS1015* ads)
{
    control->setReadInt32Functions(bind([ads](uint8_t pin) { return ads->readADC(pin); }, _1));
}

void IOService::_subscribeToPCF(ControlUnitModel<boolean>* &control, PCF8574* pcf)
{
    control
        ->setReadBooleanFunction(bind([pcf](uint8_t pin) { return static_cast<boolean>(pcf->read(pin)); }, _1))
        ->setWriteBooleanFunction(bind([pcf](uint8_t pin, boolean value) { pcf->write(pin, value); }, _1, _2));
}

void IOService::_initEspIO(ControlUnitModel<boolean>* &control, uint8_t pin, ControlMode mode)
{
    pinMode(pin, mode == ControlMode::Output ? OUTPUT : INPUT);
    (control = new ControlUnitModel<boolean>(pin, mode, ControlType::Digital))
        ->setReadBooleanFunction(bind([](uint8_t pin) { return static_cast<boolean>(digitalRead(pin)); }, _1))
        ->setWriteBooleanFunction(bind([](uint8_t pin, boolean value) { digitalWrite(pin, value); }, _1, _2));
}

void IOService::_initPcfIO(ControlUnitModel<boolean>* &control, uint8_t pin, ControlMode mode)
{
    PCF8574* master = mode == ControlMode::Input ? this->OptocouplerPCF : this->RelayPCF;

    _subscribeToPCF((control = new ControlUnitModel<boolean>(pin, mode, ControlType::Digital)), master);
    if (mode == ControlMode::Output)
    {
        control->setReversed(true);
        control->write(false);
    }
}

void IOService::_initAdsIn(ControlUnitModel<int16_t>* &control, uint8_t pin)
{
    _subscribeToADS((control = new ControlUnitModel<int16_t>(pin, ControlMode::Input, ControlType::Analog)), this->VDividerADS);
}

boolean IOService::_msDispatcher()
{
    if ((msNow = millis()) - msOld >= SIN_CALL_FRQ_MS)
    {
        msOld = msNow;
        return true;
    }

    return false;
}

boolean IOService::_msSafeDispatcher(uint64_t *now, uint64_t *old, uint64_t delay_ss)
{
    if ((*now = millis()) - *old >= delay_ss * 1000)
    {
        *old = *now;
        return true;
    }

    return false;
}

boolean IOService::IsConnected()
{
    return (
        RelayPCF->isConnected() &&
        OptocouplerPCF->isConnected() &&
        VDividerADS->isConnected()
    );
}

IOService* IOService::InitPeriphery()
{
    this->RelayPCF          = new PCF8574(ADDR_RelayPCF,        this->itcw);
    this->OptocouplerPCF    = new PCF8574(ADDR_OptocouplerPCF,  this->itcw);
    this->VDividerADS       = new ADS1015(ADDR_VDividerADS,     this->itcw);
    this->RelayPCF->begin();
    this->OptocouplerPCF->begin();
    this->VDividerADS->begin();

    VDividerADS->setMode(0);
    VDividerADS->setGain(2);
    _initVariables();

    return this;
}

boolean IOService::ReadIN()
{
    if (DInInterrupt || _msDispatcher())
    {
        for (ControlUnitBase* &control : InputControls)
            control->Read();

        DInInterrupt = false;
        return true;
    }
            
    return false;
}

boolean IOService::SafeIO()
{
    if (_msSafeDispatcher(&msHSafeNow, &msHSafeOld, HEATERS_TOGGLE_DEL_SS))
        this->Relay_Heater->write(_relay_safe_heater);

    return false;
}

void IOService::SafeToggleHeater(boolean state)
{
    this->_relay_safe_heater = state;
}