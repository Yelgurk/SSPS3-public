#include <Arduino.h>
#include <I2CKeyPad.h>
#include <functional>
#include <vector>
#include "../../SSPS3_DDD_Domain/include/keyModel.hpp"

#ifndef KBService_hpp
#define KBService_hpp

enum class KeyboardCallback { Delay, Dispatcher, KBPress };

using namespace std;

#define ESP_KEY_INT_PIN 21
#define KB_CALL_FRQ_MS  100
#define ADDR_KB4X4PCF   0x21

class KBService
{
private:
    I2CKeyPad* KeyPad;
    TwoWire* itcw;

    vector<KeyModel>* kbTemplate = nullptr;
    vector<KeyModel> kbPattern
    {
        KeyModel(KeyType::L_STACK_4, []() {}),
        KeyModel(KeyType::L_STACK_3, []() {}),
        KeyModel(KeyType::L_STACK_2, []() {}),
        KeyModel(KeyType::L_STACK_1, []() {}),
        KeyModel(KeyType::R_STACK_4, []() {}),
        KeyModel(KeyType::R_STACK_3, []() {}),
        KeyModel(KeyType::R_STACK_2, []() {}),
        KeyModel(KeyType::R_STACK_1, []() {}),
        KeyModel(KeyType::LEFT_TOP,  []() {}),
        KeyModel(KeyType::LEFT_BOT,  []() {}),
        KeyModel(KeyType::RIGHT_TOP, []() {}),
        KeyModel(KeyType::RIGHT_BOT, []() {}),
        KeyModel(KeyType::LEFT,      []() {}),
        KeyModel(KeyType::TOP,       []() {}),
        KeyModel(KeyType::RIGHT,     []() {}),
        KeyModel(KeyType::BOTTOM,    []() {})
    };
    
    uint64_t msOld = 0,
             msNow = 0;
    boolean _msDispatcher();

public:
    KBService(uint8_t sda, uint8_t scl);
    KBService(TwoWire* itcw);
    volatile boolean KeyPadInterrupt = false;

    boolean IsConnected();
    void InitPeriphery();
    KBService* SetKBTemplate(vector<KeyModel>* kbTemplate);
    KeyModel* ActiveKey();
    KeyboardCallback ReadKB();
};

#endif