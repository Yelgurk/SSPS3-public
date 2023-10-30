#include <Arduino.h>
#include "../../SSPS3_DDD_Core/include/DBService.hpp"
#include "../../SSPS3_DDD_Core/include/IOService.hpp"
#include "../../SSPS3_DDD_Domain/include/taskModel.hpp"
#include "./UIService.hpp"
#include "./NaviService.hpp"
#include "./NotificationService.hpp"

#ifndef TaskService_hpp
#define TaskService_hpp

#define TRIG_BLOW_AWAIT_MAX_SS              5
#define TRIG_PROG_WJACKET_DRAIN_MAX_SS      30
#define TRIG_PROG_IN_PAUSE_MAX_SS           3600
#define AWAIT_NEXT_TASK_BEFORE_CANCEL_SS    60 * 10 //60 sec * 10 min
#define PROC_1CELSIUS_UP_IN_MM              2
#define PROC_1CELSIUS_DOWN_IN_MM            (double_t)1.5

class TaskService
{
private:
    DBService *DB;
    IOService *IO;
    UIService *UI;
    NaviService *NS;
    NIService *NIS;

    TaskModel * CurrentTask = nullptr;

    void _hard_reset_detect(boolean forced = false);
    boolean _runned_task_recovery();
    void _off_all_relays();
    int32_t _time_to_run_templ(uint8_t index);
    int32_t _time_to_run_autoH(uint8_t index);
    boolean _run_pasteurizing(uint8_t index, boolean recovery = false);
    boolean _run_heating(uint8_t index, boolean recovery = false);
    boolean _run_chilling();

    int16_t _templ_pasteur_chill_diff(uint8_t index);
    int16_t _templ_chilling_heat_diff(uint8_t index);

    int8_t _next_task_supervisor(boolean *out_task_exists, boolean *out_task_pasteur);
    boolean _380V_supervisor();
    boolean _waterJ_supervisor();
    boolean _pause_limit_supervisor();
    void _update_finish_time(DateTime * Ref, uint32_t IncMM);

    void _prep_rt_counters(unsigned long trigger_stop = 0);
    unsigned long
        rt_trigger_prev = 0,
        rt_trigger_curr = 0,
        rt_trigger_cntr = 0,
        rt_trigger_stop = 0,
        rt_trigger_await = 0;
    double_t power_lm = 0.0;

public:
    TaskService(DBService** DB, IOService** IO, UIService** UI, NaviService** NS, NIService** NIS);
    boolean startup_executed = false;

    TaskModel   *Task_StartUp = nullptr,              // load saved vars
                *Task_TurnOffBlowTask = nullptr,      // off blow process
                *Task_TurnOffCurrTask = nullptr,      // off all outputs (after stop)
                *Task_TurnOffNextTask = nullptr,      // off next planned task (for today)
                *Task_Await = nullptr,                // display await + update info (after end task/blowing)         
                *Task_LiquidPasteurizing = nullptr,   // pasteurizing cycle
                *Task_LiquidHeating = nullptr,        // heating cycle
                *Task_LiquidChilling = nullptr,       // chilling cycle
                *Task_LiquidBlowing = nullptr;        // blowing procedure

    void update_datetime(boolean forced = false);
    void set_task(TaskModel * NewTask);
    boolean run_pasteurizing();
    boolean run_heating();
    boolean run_chilling();
    boolean run_blowing(uint8_t selected_blow_pattern, boolean blowgun_call = false);
    void stop_task();
    void WorkTS();
    TaskType task_type();
};

#endif