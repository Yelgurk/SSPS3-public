#include "../include/keyModel.hpp"

KeyModel::KeyModel(KeyType type, ButtonAction OnClick)
{
    this->OnClick = OnClick;
    this->OnClickPtr = &(this->OnClick);

    this->type = type;

    for(uint32_t limiter = PRESS_PAUSE_SQUA_CNT; limiter > 0 && limiter >= PRESS_PAUSE_MIN; limiter -= 2)
        CallRange.push_back(
            CallRange.size() == 0 ?
            (PRESS_DETECTED_MS) :
            (CallRange.back() + PRESS_DELAY_MS * limiter)
        );
}

KeyModel::KeyModel(KeyType type, ButtonAction OnClick, ButtonAction OnPress) :
KeyModel(type, OnClick) 
{
    this->OnPress = OnPress;
    this->OnPressPtr = &(this->OnPress);
}

KeyModel::KeyModel(KeyType type, ButtonAction OnClick, ButtonAction OnPress, ButtonAction OnRelease) :
KeyModel(type, OnClick, OnPress)
{
    this->OnRelease = OnRelease;
    this->OnReleasePtr = &(this->OnRelease);
}

boolean KeyModel::_canCall(uint32_t KBCallFrqMs)
{
    if (LastPressMSCall == 0)
    {
        LastPressMSCall = PressMS;
        return true;
    }
    else
        for (uint32_t limiter : CallRange)
            if (limiter > LastPressMSCall && limiter <= PressMS)
            {
                if (CallRange.back() == limiter)
                    PressMS = limiter - (PRESS_DELAY_MS * PRESS_PAUSE_MIN);
                LastPressMSCall = PressMS;
                return true;
            }

    return false;
}

boolean KeyModel::State()
{
    return this->Curr;
}

KeyType KeyModel::Type()
{
    return this->type;
}


void KeyModel::AcceptState(boolean State, uint32_t KBCallFrqMs)
{
    Old = Curr;
    Curr = State;

    PressMS = Curr ? PressMS + KBCallFrqMs : 0;
    LastPressMSCall = Curr ? LastPressMSCall : 0;
    
    if (!Old && Curr && OnClickPtr != nullptr && _canCall(KBCallFrqMs))
    {
        OnClick();
    }
    else if (Old && Curr && _canCall(KBCallFrqMs))
    {
        if (OnPressPtr != nullptr)
            OnPress();
        else
            OnClick();
    }
    else if (Old && !Curr && OnReleasePtr != nullptr)
    {
        OnRelease();
    }
}