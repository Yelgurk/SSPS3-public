#include <Arduino.h>
#include <functional>

#ifndef controlUnitModel_hpp
#define controlUnitModel_hpp

using namespace std;
using namespace std::placeholders;

typedef function<boolean(uint8_t)> ReadBooleanFunction;
typedef function<int16_t(uint8_t)> ReadUintFunction;
typedef function<void(uint8_t, boolean)> WriteBooleanFunction;

enum class ControlMode { Input, Output };
enum class ControlType { Digital, Analog };

class ControlUnitBase 
{
protected:
    ControlMode mode;
    ControlType type;
    ReadUintFunction        GetUFunc;
    ReadBooleanFunction     GetBFunc;
    ReadUintFunction        ValueFunc;
    function<void()>        ReadFunc;

public:
    ControlUnitBase(
        ControlMode mode,
        ControlType type,
        ReadUintFunction    GetUFunc,
        ReadBooleanFunction GetBFunc,
        function<void()>    ReadFunc
    ) : mode(mode),
        type(type),
        GetUFunc(GetUFunc),
        GetBFunc(GetBFunc),
        ReadFunc(ReadFunc)
    {}

    ControlMode Mode();
    ControlType Type();
    boolean Boolean();
    int16_t Value();
    ControlUnitBase* Read();
};

template <typename T>
class ControlUnitModel : public ControlUnitBase
{
private:
    T GenericTValue;
    uint8_t Pin = 0;
    boolean IsReversed = false;

    ReadBooleanFunction InputBooleanFunction;
    ReadBooleanFunction *InputBooleanFunctionPtr = nullptr;

    ReadUintFunction InputIntFunction;
    ReadUintFunction *InputIntFunctionPtr = nullptr;

    WriteBooleanFunction OutputBooleanFunction;
    WriteBooleanFunction *OutputBooleanFunctionPtr = nullptr;

public:
    ControlUnitModel(uint8_t Pin, ControlMode Mode, ControlType Type);
    ControlUnitModel* setReadInt32Functions(ReadUintFunction function);
    ControlUnitModel* setReadBooleanFunction(ReadBooleanFunction function);
    ControlUnitModel* setWriteBooleanFunction(WriteBooleanFunction function);    
    ControlUnitModel* setReversed(boolean IsReversed);
    ControlUnitModel* write(boolean State);
    ControlUnitModel* read();
    T get_value();
};

#endif