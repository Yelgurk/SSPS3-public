#include <Arduino.h>
#include <PCF8574.h>
#include <ADS1X15.h>
#include <functional>
#include <vector>
#include "../../SSPS3_DDD_Domain/include/controlUnitModel.hpp"

#ifndef IOService_hpp
#define IOService_hpp

using namespace std;
using namespace std::placeholders;

#define ESP_DIN_INT_PIN         38
#define SIN_CALL_FRQ_MS         500
#define HEATERS_TOGGLE_DEL_SS   20
#define WJACKET_TOGGLE_DEL_SS   10

#define ADDR_RelayPCF           0x20
#define ADDR_OptocouplerPCF     0x27
#define ADDR_VDividerADS        0x48

#define SENS_HV_LV_ADC(voltage) ((voltage * 1.0) / 21500.0 * 1500.0 * 1000.0)
#define SENS_BATT_MINV          22.8
#define SENS_BATT_MAXV          25.0
#define SENS_BATT_MINADC        (double_t)SENS_HV_LV_ADC(SENS_BATT_MINV)
#define SENS_BATT_MAXADC        (double_t)SENS_HV_LV_ADC(SENS_BATT_MAXV)
#define SENS_BATT_STATE(adcv)   (int16_t)(adcv < SENS_BATT_MINADC ? 0 : (adcv > SENS_BATT_MAXADC ? 100 : (100.0 / (SENS_BATT_MAXADC - SENS_BATT_MINADC) * (adcv * 1.0 - SENS_BATT_MINADC))))

#define SENS_TEMPC_4MA_ADC      373.0
#define SENS_TEMPC_20MA_ADC     1865.0
#define SENS_TEMPC_MIN_C        -50
#define SENS_TEMPC_MAX_C        150
#define SENS_TEMPC_STATE(adcv)  (((SENS_TEMPC_MAX_C - SENS_TEMPC_MIN_C) * 1.0 / (SENS_TEMPC_20MA_ADC - SENS_TEMPC_4MA_ADC) * (adcv - SENS_TEMPC_4MA_ADC)) + SENS_TEMPC_MIN_C)

class IOService
{
private:
    PCF8574* RelayPCF;
    PCF8574* OptocouplerPCF;
    ADS1015* VDividerADS;

    TwoWire* itcw;
    void _initVariables();
    void _subscribeToADS(ControlUnitModel<int16_t>* &control, ADS1015* ads);
    void _subscribeToPCF(ControlUnitModel<boolean>* &control, PCF8574* pcf);
    void _initEspIO(ControlUnitModel<boolean>* &control, uint8_t pin, ControlMode type);
    void _initPcfIO(ControlUnitModel<boolean>* &control, uint8_t pin, ControlMode type);
    void _initAdsIn(ControlUnitModel<int16_t>* &control, uint8_t pin);
    
    uint64_t msOld = 0,
             msNow = 0;
    boolean _msDispatcher();

    boolean _relay_safe_heater = false,
            _relay_safe_jacket = false;

    uint64_t msHSafeOld = 0,
             msHSafeNow = 0,
             msJSafeOld = 0,
             msJSafeNow = 0;
    boolean _msSafeDispatcher(uint64_t *now, uint64_t *old, uint64_t delay_ss);

public:
    IOService(uint8_t sda, uint8_t scl);
    IOService(TwoWire* itcw);
    volatile boolean DInInterrupt = false;

    boolean IsConnected();
    IOService* InitPeriphery();
    boolean ReadIN();
    boolean SafeIO();
    void SafeToggleHeater(boolean state);
    //void SafeToggleJacket(boolean state);

    vector<ControlUnitBase*> InputControls;

    ControlUnitModel<boolean>   *Relay_1,
                                *Relay_2,
                                *Relay_3,
                                *Relay_4,
                                *Relay_5,
                                *Relay_6,
                                *Relay_7,
                                *Relay_8,
                                *OptIn_1,
                                *OptIn_2,
                                *OptIn_3,
                                *OptIn_4,
                                *OptIn_5,
                                *OptIn_6,
                                *OptIn_7,
                                *OptIn_8,
                                *LCD_BL,
                                *RF_UHF,
                                *SIMCOM;

    ControlUnitModel<int16_t>   *vAnIn_1,
                                *vAnIn_2,
                                *vAnIn_3,
                                *vAnIn_4;

    ControlUnitModel<boolean>   *Relay_Heater,
                                *Relay_Mixer,
                                *Relay_WaterJ,
                                *Relay_Blowgun;

    ControlUnitModel<boolean>   *OptIn_WaterJ,
                                *OptIn_StopBTN,
                                *OptIn_MixerCrash,
                                *OptIn_380V,
                                *OptIn_Blowgun;

    ControlUnitModel<int16_t>   *vAnIn_Battery,
                                *vAnIn_LiqTempC;
};

#endif