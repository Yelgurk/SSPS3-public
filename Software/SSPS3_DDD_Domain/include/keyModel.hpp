#include <Arduino.h>
#include <vector>
#include <queue>

#ifndef keyModel_hpp
#define keyModel_hpp

using namespace std;

#define PRESS_DELAY_MS          50
#define PRESS_DETECTED_MS       800
#define PRESS_PAUSE_SQUA_CNT    12
#define PRESS_PAUSE_MIN         4

/*
enum class KeyType {
    L_STACK_4   = 0,
    L_STACK_3   = 4,
    L_STACK_2   = 8,
    L_STACK_1   = 12,
    R_STACK_4   = 1,
    R_STACK_3   = 5,
    R_STACK_2   = 9,
    R_STACK_1   = 13,
    LEFT_TOP    = 2,
    LEFT_BOT    = 10,
    RIGHT_TOP   = 11,
    RIGHT_BOT   = 15,
    LEFT        = 6,
    TOP         = 3,
    RIGHT       = 7,
    BOTTOM      = 14
};
*/

enum class KeyType {
    L_STACK_4   = 0,
    L_STACK_3   = 2,
    L_STACK_2   = 3,
    L_STACK_1   = 1,
    R_STACK_4   = 12,
    R_STACK_3   = 14,
    R_STACK_2   = 15,
    R_STACK_1   = 13,
    LEFT_TOP    = 4,
    LEFT_BOT    = 7,
    RIGHT_TOP   = 11,
    RIGHT_BOT   = 9,
    LEFT        = 6,
    TOP         = 8,
    RIGHT       = 10,
    BOTTOM      = 5
};

typedef function<void()> ButtonAction;

class KeyModel
{
private:
    KeyType type;
    boolean Old = false;
    boolean Curr = false;

    ButtonAction OnClick;
    ButtonAction* OnClickPtr = nullptr;

    ButtonAction OnPress;
    ButtonAction* OnPressPtr = nullptr;

    ButtonAction OnRelease;
    ButtonAction* OnReleasePtr = nullptr;

    uint32_t PressMS = 0;
    uint32_t LastPressMSCall = 0;
    
    boolean _canCall(uint32_t KBCallFrqMs);
    vector<uint32_t> CallRange;

public:
    KeyModel(KeyType type, ButtonAction OnClick);
    KeyModel(KeyType type, ButtonAction OnClick, ButtonAction OnPress);
    KeyModel(KeyType type, ButtonAction OnClick, ButtonAction OnPress, ButtonAction OnRelease);
    boolean State();
    KeyType Type();
    void AcceptState(boolean State, uint32_t KBCallFrqMs);
};

#endif