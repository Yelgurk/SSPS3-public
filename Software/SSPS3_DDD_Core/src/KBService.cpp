#include "../include/KBService.hpp"

KBService::KBService(uint8_t sda, uint8_t scl)
{
    this->itcw = new TwoWire(0);
    this->itcw->setPins(sda, scl);
    this->itcw->begin(sda, scl, 100000);
}

KBService::KBService(TwoWire* itcw)
{
    this->itcw = itcw;
}

boolean KBService::_msDispatcher()
{
    if ((msNow = millis()) - msOld >= KB_CALL_FRQ_MS)
    {
        msOld = msNow;
        return true;
    }

    return false;
}

boolean KBService::IsConnected()
{
    return KeyPad->isConnected();
}

void KBService::InitPeriphery()
{
    this->KeyPad = new I2CKeyPad(ADDR_KB4X4PCF, this->itcw);
    this->KeyPad->begin();
}

KBService* KBService::SetKBTemplate(vector<KeyModel>* kbTemplate)
{
    if (this->kbTemplate != nullptr)
        for (uint8_t index = 0; index < this->kbTemplate->size(); index++)
            (*this->kbTemplate)[index].AcceptState(false, KB_CALL_FRQ_MS);

    this->kbTemplate = kbTemplate;
    return this;
}

KeyModel* KBService::ActiveKey()
{
    for (uint8_t keyNum = 0; keyNum < kbTemplate->size(); keyNum++)
        if ((&(*kbTemplate)[keyNum])->State() == true)
            return &(*kbTemplate)[keyNum];

    return nullptr;
}

KeyboardCallback KBService::ReadKB()
{
    boolean key_matched = false;
    boolean dispatcher = _msDispatcher();

    if (KeyPadInterrupt || dispatcher)
    {
        uint8_t index = KeyPad->getKey();

        for (uint8_t handler = 0; handler < kbPattern.size(); handler++)
        {
            KeyModel* pattern  = &kbPattern[handler];
            KeyModel* press    = nullptr;

            if (kbTemplate != nullptr)
                for (uint8_t match = 0; match < kbTemplate->size(); match++)
                    if ((*kbTemplate)[match].Type() == pattern->Type())
                    {
                        press = &(*kbTemplate)[match];
                        key_matched = true;
                        break;
                    }

            if (index != 16 && pattern->Type() == static_cast<KeyType>(index))
            {
                if (press != nullptr && press->State() == pattern->State())
                    press->AcceptState(true, KB_CALL_FRQ_MS);

                pattern->AcceptState(true, KB_CALL_FRQ_MS);
            }
            else
            {
                if (press != nullptr)
                    press->AcceptState(false, KB_CALL_FRQ_MS);
                pattern->AcceptState(false, KB_CALL_FRQ_MS);
            }
        }

        KeyPadInterrupt = false;
        return dispatcher ? KeyboardCallback::Dispatcher : KeyboardCallback::KBPress;
    }
    else if (KeyPadInterrupt && kbTemplate == nullptr)
        KeyPadInterrupt = false;
            
    return KeyboardCallback::Delay;
}