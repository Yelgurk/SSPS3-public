#include "../include/TaskService.hpp"

void TaskService::_hard_reset_detect(boolean forced)
{
    if (DB->ee_vars_inited->Value == 0 ||
        DB->ee_vars_inited->Value > 1 ||
        forced)
    {
        if (DB->ee_vars_inited->Value > 1)
            DB->RWCounterClear();
        DB->SetDefaultValues();
        DB->ee_vars_inited->AcceptChanges(1);
        update_datetime(true);
    }
}

void TaskService::_off_all_relays()
{
    IO->SafeToggleHeater(false);

    IO->Relay_Heater->write(false);
    IO->Relay_WaterJ->write(false);
    IO->Relay_Mixer->write(false);
    IO->Relay_Blowgun->write(false);
}

int32_t TaskService::_time_to_run_templ(uint8_t index)
{
    (*DB->DT_Comparator) = (*DB->DT_RTC);
    DB->DT_Comparator->time->SetTime(
        (*DB->ee_templ_arr_startHH[index])->Value,
        (*DB->ee_templ_arr_startMM[index])->Value,
        0
    );

    return DB->DT_Comparator->DiffDateTimeInSS(DB->DT_RTC, false);
}

int32_t TaskService::_time_to_run_autoH(uint8_t index)
{
    (*DB->DT_Comparator) = (*DB->DT_RTC);
    DB->DT_Comparator->time->SetTime(
        (*DB->ee_autoH_arr_startHH[index])->Value,
        (*DB->ee_autoH_arr_startMM[index])->Value,
        0
    );
    
    return DB->DT_Comparator->DiffDateTimeInSS(DB->DT_RTC, false);
}

boolean TaskService::_run_heating(uint8_t index, boolean recovery)
{
    // check is tempC sensor error or CANCEL (return false)

    if (DB->ram_mixer_crash_trigger->Value == 1)
    {
        NIS->display_message(Message::MixerCrash, Icon::Error);
        return false;
    }

    if (!recovery)
    {
        if (task_type() != TaskType::Await)
            return false;

        if (DB->ram_380V_is_connected->Value == 0)
        {
            NIS->display_message(Message::V380IsOff, Icon::Warning);
            return false;
        }

        if (DB->ram_stop_btn_pressed->Value == 1)
            return false;

        if (index > 0)
            (*DB->ee_autoH_arr_runned[index - 1])->AcceptChanges(1);
    }

    UI->show_scr_task();
    NS->navi_scr_task->template_set();

    DB->ee_autoH_is_running->AcceptChanges(1);
    DB->ee_autoH_choise->AcceptChanges(index);

    if (!recovery)
    {
        DB->ee_task_is_paused->AcceptChanges(0);
        DB->ee_progr_waterJ_filled_yet->AcceptChanges(0);
        DB->ee_progr_tempC_reached_yet->AcceptChanges(0);

        int16_t tempC_diff =
            static_cast<int16_t>((*DB->ee_autoH_arr_heat_tempC[index])->Value) -
            static_cast<int16_t>(DB->ram_liquid_tempC->Value);
        
        (*DB->DT_TaskCallTime) = (*DB->DT_RTC);
        _update_finish_time(DB->DT_RTC,
            DB->ee_autoH_choise->Value == 0 ?
                (tempC_diff < 0 ? 0 : tempC_diff * PROC_1CELSIUS_UP_IN_MM) :
                (tempC_diff < 0 ? 0 : tempC_diff * PROC_1CELSIUS_UP_IN_MM +
                (*DB->ee_autoH_arr_duratMM[DB->ee_autoH_choise->Value - 1])->Value)
        );

        DB->DTImportExport(
            DB->DT_TaskCallTime,
            DB->ee_task_callMin,
            DB->ee_task_callHH,
            DB->ee_task_callDD,
            DB->ee_task_callMonth,
            DB->ee_task_callYYYY,
            false
        );

        DB->DTImportExport(
            DB->DT_TaskProgrStart,
            DB->ee_task_startMin,
            DB->ee_task_startHH,
            DB->ee_task_startDD,
            DB->ee_task_startMonth,
            DB->ee_task_startYYYY,
            false
        );

        DB->DTImportExport(
            DB->DT_TaskFinish,
            DB->ee_task_finishMin,
            DB->ee_task_finishHH,
            DB->ee_task_finishDD,
            DB->ee_task_finishMonth,
            DB->ee_task_finishYYYY,
            false
        );
    }

    _prep_rt_counters(TRIG_PROG_IN_PAUSE_MAX_SS * 1000);

    this->UI->TaskC.vs_set_theme_start();
    this->UI->TaskC.vs_set_name(
        index == 0 ?
        "Подогрев" :
        "Автонагрев #" + to_string(index)
    );
    this->UI->TaskC.vs_set_mode(ProgrMode::Heating);
    this->UI->TaskC.vs_set_start_ss(DB->DT_TaskCallTime->TimeInSS());
    this->UI->TaskC.vs_set_finish_ss(DB->DT_TaskFinish->TimeInSS());

    this->_off_all_relays();

    this->CurrentTask = this->Task_LiquidHeating;
    return true;
}

boolean TaskService::_380V_supervisor()
{
    if (DB->ram_380V_is_connected->Value == 0)
    {
        NIS->display_message(Message::V380IsOff, Icon::Warning);

        if (DB->ee_task_is_paused->Value == 0)
        {
            DB->ee_task_is_paused->AcceptChanges(1);
            (*DB->DT_TaskPaused) = (*DB->DT_RTC);

            DB->ee_task_pauseMin->AcceptChanges(DB->DT_TaskPaused->time->MM());
            DB->ee_task_pauseHH->AcceptChanges(DB->DT_TaskPaused->time->HH());
            DB->ee_task_pauseDD->AcceptChanges(DB->DT_TaskPaused->date->DD());
            DB->ee_task_pauseMonth->AcceptChanges(DB->DT_TaskPaused->date->MM());
            DB->ee_task_pauseYYYY->AcceptChanges(DB->DT_TaskPaused->date->YYYY());

            rt_trigger_await = 0;
            rt_trigger_prev = rt_trigger_curr = millis();
        }
        else
        {
            rt_trigger_await += (rt_trigger_curr = millis()) - rt_trigger_prev;
            rt_trigger_prev = rt_trigger_curr;
        }

        return false;
    }

    return true;
}

boolean TaskService::_waterJ_supervisor()
{
    if (DB->ram_water_in_jacket->Value == 0)
    {
        if (DB->ee_task_is_paused->Value == 0 &&
            rt_trigger_cntr < TRIG_PROG_WJACKET_DRAIN_MAX_SS * 1000)
        {
            rt_trigger_cntr += (rt_trigger_curr = millis()) - rt_trigger_prev;
            rt_trigger_prev = rt_trigger_curr;
            return true;
        }
        else if (DB->ee_task_is_paused->Value == 0)
        {
            DB->ee_task_is_paused->AcceptChanges(1);
            (*DB->DT_TaskPaused) = (*DB->DT_RTC);

            DB->ee_task_pauseMin->AcceptChanges(DB->DT_TaskPaused->time->MM());
            DB->ee_task_pauseHH->AcceptChanges(DB->DT_TaskPaused->time->HH());
            DB->ee_task_pauseDD->AcceptChanges(DB->DT_TaskPaused->date->DD());
            DB->ee_task_pauseMonth->AcceptChanges(DB->DT_TaskPaused->date->MM());
            DB->ee_task_pauseYYYY->AcceptChanges(DB->DT_TaskPaused->date->YYYY());

            rt_trigger_await = 0;
            rt_trigger_prev = rt_trigger_curr = millis();
            return false;
        }
        else
        {
            NIS->display_message(Message::WaterJ, Icon::Warning);
            
            rt_trigger_await += (rt_trigger_curr = millis()) - rt_trigger_prev;
            rt_trigger_prev = rt_trigger_curr;
            return false;
        }
    }

    rt_trigger_cntr = 0;
    rt_trigger_prev = millis();
    return true;
}

boolean TaskService::_pause_limit_supervisor()
{
    if (DB->ee_task_is_paused->Value == 1)
    {
        this->UI->TaskC.vs_set_theme_pause();

        if (rt_trigger_await >= rt_trigger_stop)
        {
            NIS->display_message(Message::LongPause, Icon::Error);
            NIS->display_message(Message::ErrorTaskFinish, Icon::Warning);
            return false;
        }

        if (DB->ram_water_in_jacket->Value == 1 &&
            DB->ram_380V_is_connected->Value == 1)
        {
            DB->ee_task_is_paused->AcceptChanges(0);
            DB->DT_TaskFinish->time->IncSeconds(DB->DT_RTC->DiffDateTimeInSS(DB->DT_TaskPaused));
            
            // set resume theme for current task block
            UI->TaskC.vs_set_theme_resume();
            NIS->UserActivity();
        }
        else
            return true;
    }
    
    rt_trigger_await = 0;
    return true;
}

void TaskService::_prep_rt_counters(unsigned long trigger_stop)
{
    rt_trigger_prev = rt_trigger_curr = millis();
    rt_trigger_await = rt_trigger_cntr = 0;
    rt_trigger_stop = trigger_stop;
}

int8_t TaskService::_next_task_supervisor(boolean *out_task_exists, boolean *out_task_pasteur)
{
    boolean task_executed = false,
            task_exists = false,
            task_pasteur = false;
    uint32_t incoming_task_ss = 24 * 60 * 60;
    int8_t task_index = -1;

    for (uint8_t index = 0;
        index < this->DB->ee_templ_arr_runned.size() &&
        !task_executed;
        index++)
    {
        if ((*this->DB->ee_templ_arr_mode[index + 1])->Value != 0 &&
            (*this->DB->ee_templ_arr_runned[index])->Value == 0)
        {
            if (this->_time_to_run_templ(index) > 0 &&
                this->_time_to_run_templ(index) < incoming_task_ss)
            {
                incoming_task_ss = this->_time_to_run_templ(index);
                task_exists = true;
                task_pasteur = true;
                task_index = index;
            }

            if (this->_time_to_run_templ(index) <= 0 && 
                this->_time_to_run_templ(index) >= -AWAIT_NEXT_TASK_BEFORE_CANCEL_SS) //await range in ss by rtc
            {
                task_executed = true;
                task_pasteur = true;
                task_index = index;
                this->_run_pasteurizing(index + 1);
                this->NIS->display_message(Message::TryCallTask, Icon::Info);
            }
        }
    }

    for (uint8_t index = 0;
        index < this->DB->ee_autoH_arr_runned.size() &&
        !task_executed;
        index++)
    {
        if ((*this->DB->ee_autoH_arr_mode[index])->Value != 0 &&
            (*this->DB->ee_autoH_arr_runned[index])->Value == 0)
        {
            if (this->_time_to_run_autoH(index) > 0 &&
                this->_time_to_run_autoH(index) < incoming_task_ss)
            {
                incoming_task_ss = this->_time_to_run_autoH(index);
                task_exists = true;
                task_index = index;
                task_pasteur = false;
            }

            if (this->_time_to_run_autoH(index) <= 0 && 
                this->_time_to_run_autoH(index) >= -AWAIT_NEXT_TASK_BEFORE_CANCEL_SS) //await range in ss by rtc
            {
                task_executed = true;
                task_index = index;
                task_pasteur = false;
                this->_run_heating(index + 1);
                this->NIS->display_message(Message::TryCallTask, Icon::Info);
            }
        }
    }

    *out_task_exists = task_exists;
    *out_task_pasteur = task_pasteur;
    return task_index;
}

TaskService::TaskService(DBService** DB, IOService** IO, UIService** UI, NaviService** NS, NIService** NIS)
{
    this->DB = *DB;
    this->IO = *IO;
    this->UI = *UI;
    this->NS = *NS;
    this->NIS = *NIS;

    Task_StartUp = new TaskModel(TaskType::System, [this]()
    {
        _hard_reset_detect();
        
        if (!_runned_task_recovery())
            this->CurrentTask = Task_Await;
        
        return false;
    });

    Task_TurnOffBlowTask = new TaskModel(TaskType::System, [this]()
    {
        _off_all_relays();

        this->UI->progr_blowing(1, 1, 1);
        this->UI->blowing_state = BlowingState::Available;

        this->CurrentTask = Task_Await;
        return false;
    });

    Task_TurnOffCurrTask = new TaskModel(TaskType::System, [this]()
    {
        _off_all_relays();

        this->DB->ee_progr_is_running->AcceptChanges(0);
        this->DB->ee_autoH_is_running->AcceptChanges(0);

        this->UI->TaskC.vs_set_theme_finish();
        this->CurrentTask = Task_Await;
        return false;
    });

    Task_TurnOffNextTask = new TaskModel(TaskType::System, [this]()
    {
        // _off_all_relays();

        // find/search algorithm for setting off flag

        boolean task_exists = false,
                task_pasteur = false;
        int8_t task_index = _next_task_supervisor(&task_exists, &task_pasteur);

        if (task_index >= 0)// >= 0 && task_exists)
        {
            if (task_pasteur)
                (*this->DB->ee_templ_arr_runned[task_index])->AcceptChanges(1);
            else
                (*this->DB->ee_autoH_arr_runned[task_index])->AcceptChanges(1);
        }

        this->CurrentTask = Task_Await;
        return false;
    });

    Task_Await = new TaskModel(TaskType::Await, [this]()
    {
        if (this->NS->page() == NaviPage::Settings)
            return false;

        this->_hard_reset_detect();
        
        boolean task_exists = false,
                task_pasteur = false;
        int8_t task_index = _next_task_supervisor(&task_exists, &task_pasteur);

        string next_task_state = "";

        if (task_index < 0)// || !task_exists)
            next_task_state = "Задачи отсутствуют";
        else
        {
            uint8_t task_await_HH = task_pasteur ? 
                (*this->DB->ee_templ_arr_startHH[task_index])->Value :
                (*this->DB->ee_autoH_arr_startHH[task_index])->Value;

            uint8_t task_await_MM = task_pasteur ? 
                (*this->DB->ee_templ_arr_startMM[task_index])->Value :
                (*this->DB->ee_autoH_arr_startMM[task_index])->Value;

            next_task_state = "След: ";
            next_task_state += task_pasteur ? "пастер #" : "нагрев #";
            next_task_state += to_string(task_index + 1) + " в ";
            next_task_state += to_string(task_await_HH) + ":";
            next_task_state += task_await_MM < 10 ? "0" : "";
            next_task_state += to_string(task_await_MM);
        }

        this->UI->AwaitInfoC.set_nextTask(next_task_state);

        return false;
    });

    Task_LiquidPasteurizing = new TaskModel(TaskType::LiquidPasteurizing, [this]()
    {
	/* demo. hidden */
    });

    Task_LiquidHeating = new TaskModel(TaskType::LiquidHeating, [this]()
    {
        this->UI->TaskC.vs_set_gone_ss(this->DB->DT_RTC->DiffDateTimeInSS(this->DB->DT_TaskCallTime));
        this->UI->TaskC.vs_set_heating_tempC((*this->DB->ee_autoH_arr_heat_tempC[this->DB->ee_autoH_choise->Value])->Value);

        if (this->DB->ram_mixer_crash_trigger->Value == 1)
        {
            this->stop_task();
            this->NIS->display_message(Message::ErrorTaskFinish, Icon::Info);
            this->NIS->display_message(Message::MixerCrash, Icon::Error);
        }

        // check: is await (1 hours) time for solving problem elapsed. false(not solved) => stop task
        if (!_pause_limit_supervisor())
        {
            this->stop_task();
            return false;
        }

        // check: is 380v connected. false => start bg timer from 1 hour
        if (!_380V_supervisor())
        {
            this->UI->TaskC.vs_set_theme_pause();
            this->_off_all_relays();
            return false;
        }

        // power is connected => run mixer
        this->IO->Relay_Mixer->write(true);

        if (this->DB->ee_task_is_paused->Value == 0)
            this->UI->TaskC.vs_set_theme_resume();

        // water jacket "background" contol
        if (this->DB->ee_progr_waterJ_filled_yet->Value == 1 && !_waterJ_supervisor())
        {
            this->UI->TaskC.vs_set_theme_pause();
            //this->IO->Relay_Heater->write(false);
            this->IO->SafeToggleHeater(false);

            this->IO->Relay_WaterJ->write(true);
            return false;
        }
        else if (this->DB->ram_water_in_jacket->Value == 1)
            this->IO->Relay_WaterJ->write(false);
        else
            this->IO->Relay_WaterJ->write(true);

        // if paused, break instructions here, else continue heating proc
        //if (this->DB->ee_task_is_paused->Value == 1)
        //    return false;
        //else
        //    this->UI->TaskC.vs_set_theme_resume();
            
        
        // does water jacked was filled once at the begining for controlling part (previous code block)
        if (this->DB->ee_progr_waterJ_filled_yet->Value == 0 &&
            this->DB->ram_water_in_jacket->Value == 1)
        {
            this->DB->ee_progr_waterJ_filled_yet->AcceptChanges(1);
            (*this->DB->DT_TaskProgrStart) = (*this->DB->DT_RTC);

            this->DB->DTImportExport(
                this->DB->DT_TaskProgrStart,
                this->DB->ee_task_startMin,
                this->DB->ee_task_startHH,
                this->DB->ee_task_startDD,
                this->DB->ee_task_startMonth,
                this->DB->ee_task_startYYYY,
                false
            );
        }
        else if (this->DB->ee_progr_waterJ_filled_yet->Value == 0)
            return false;

        // heaters controlling part. if temp was reached on template #0 => finish task
        if ((*this->DB->ee_autoH_arr_heat_tempC[this->DB->ee_autoH_choise->Value])->Value > 
            this->DB->ram_liquid_tempC->Value)
        {
            //this->IO->Relay_Heater->write(true);
            this->IO->SafeToggleHeater(true);
        }
        else
        {
            //this->IO->Relay_Heater->write(false);
            this->IO->SafeToggleHeater(false);

            if (this->DB->ee_autoH_choise->Value == 0)
            {
                return true;
            }
            else if (this->DB->ee_progr_tempC_reached_yet->Value == 0)
            {
                this->DB->ee_progr_tempC_reached_yet->AcceptChanges(1);
                
                _update_finish_time(
                    this->DB->DT_RTC,
                    ((*this->DB->ee_autoH_arr_duratMM[this->DB->ee_autoH_choise->Value - 1])->Value)
                );
            }
        }

        // ui info update by selected heat template (index). 0 => by operator, only heat
        if (this->DB->ee_autoH_choise->Value == 0)
        {
            _update_finish_time(
                this->DB->DT_RTC,
                PROC_1CELSIUS_UP_IN_MM *
                ((*this->DB->ee_autoH_arr_heat_tempC[this->DB->ee_autoH_choise->Value])->Value -
                this->DB->ram_liquid_tempC->Value)
            );
        }
        else if (this->DB->ee_task_is_paused->Value == 0 &&
                (*this->DB->DT_RTC) > (*this->DB->DT_TaskFinish) && 
                this->DB->ram_liquid_tempC->Value >= ((*this->DB->ee_autoH_arr_heat_tempC[this->DB->ee_autoH_choise->Value])->Value - 1))
        {
            return true;
        }

        // ui progress bar update
        this->UI->TaskC.vs_set_finish_ss(this->DB->DT_TaskFinish->TimeInSS());
        this->UI->TaskC.vs_set_progr_bar(
            1000.0 /
            this->DB->DT_TaskFinish->DiffDateTimeInSS(this->DB->DT_TaskProgrStart) *
            this->DB->DT_RTC->DiffDateTimeInSS(this->DB->DT_TaskProgrStart)
        );

        return false;
    });

    Task_LiquidChilling = new TaskModel(TaskType::LiquidChilling, [this]()
    {
	/* demo. hidden */
    });

    Task_LiquidBlowing = new TaskModel(TaskType::LiquidBlowing, [this]()
    {
	/* demo. hidden */
    });
}

void TaskService::set_task(TaskModel * Task)
{
    if (CurrentTask == nullptr ||
        static_cast<uint8_t>(CurrentTask->Type()) == static_cast<uint8_t>(TaskType::Await))
        CurrentTask = Task;
}

boolean TaskService::run_pasteurizing()
{
    return this->_run_pasteurizing(0);
}

boolean TaskService::run_heating()
{
    return this->_run_heating(0);
}

boolean TaskService::run_chilling()
{
    return this->_run_chilling();
}

boolean TaskService::run_blowing(uint8_t selected_blow_pattern, boolean blowgun_call)
{
    if (blowgun_call &&
        DB->ram_blowgun_trigger->Value == 1 &&
        DB->ram_blowgun_release->Value == 1)
        return false;

    if (task_type() != TaskType::Await)
        return false;

    if (DB->ram_380V_is_connected->Value == 1)
    {
        NIS->display_message(Message::V380IsOn, Icon::Info);
        return false;
    }

    this->DB->ram_blow_by_blowgun->Value = static_cast<uint8_t>(blowgun_call);    

    _prep_rt_counters(
        selected_blow_pattern < 3 ? 
        (power_lm = 60.0 / (36.0 + DB->ee_pump_calibr->Value)) * ((*DB->ee_blow_arr[selected_blow_pattern])->Value + 0.0005) * 1000 :
        DB->ee_blowgun_wash->Value * 1000
    );

    this->UI->blowing_state = selected_blow_pattern < 3 ? 
        BlowingState::Volume :
        BlowingState::Time;

    this->CurrentTask = Task_LiquidBlowing;
    return true;
}

void TaskService::stop_task()
{
    if (CurrentTask != nullptr &&
        static_cast<uint8_t>(CurrentTask->Type()) > static_cast<uint8_t>(TaskType::Await))
    {
        if (CurrentTask->Type() == TaskType::LiquidBlowing)
            CurrentTask = Task_TurnOffBlowTask;
        else
            CurrentTask = Task_TurnOffCurrTask;
    }
    else if (this->NS->page() == NaviPage::Await)
        CurrentTask = Task_TurnOffNextTask;
}

void TaskService::WorkTS()
{
    if (!startup_executed)
    {
        startup_executed = true;
        CurrentTask = Task_StartUp;
    }

    if (CurrentTask != nullptr &&
        CurrentTask->Iteration())
        stop_task();
    else if (CurrentTask == nullptr)
        CurrentTask = Task_Await;
}

TaskType TaskService::task_type()
{
    if (CurrentTask == nullptr)
        return TaskType::Await;
    else
        return CurrentTask->Type();
}