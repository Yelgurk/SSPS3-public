#include <Arduino.h>
#include <./dateTimeModel.hpp>

#ifndef taskmodel_hpp
#define taskmodel_hpp

using namespace std;

enum class TaskType {
    System,
    Await,
    LiquidPasteurizing,
    LiquidHeating,
    LiquidChilling,
    LiquidBlowing
};

class TaskModel
{
private:
    TaskType type = TaskType::Await;
    function<boolean()> TaskFunction;

public:
    TaskModel(TaskType type, function<boolean()> TaskFunction);
    TaskType Type();
    boolean Iteration();
};

#endif