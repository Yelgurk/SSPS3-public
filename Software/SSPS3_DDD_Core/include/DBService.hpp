#include <Arduino.h>
#include <functional>
#include "../../SSPS3_DDD_Infrastructure/include/eeprom.hpp"
#include "../../SSPS3_DDD_Domain/include/dateTimeModel.hpp"

#ifndef DBService_hpp
#define DBService_hpp

#define LIMIT_MAX_HEAT          50
#define LIMIT_MAX_CHILL         50
#define LIMIT_MAX_PROG_PASTEUR  85
#define LIMIT_MAX_PROG_CHILL    50
#define LIMIT_MAX_PROG_HEAT     50
#define LIMIT_MAX_PROG_DURAT    240
#define LIMIT_MAX_AUTOH_DURAT   240

#define LIMIT_MIN_HEAT          10
#define LIMIT_MIN_CHILL         10
#define LIMIT_MIN_PROG_PASTEUR  45
#define LIMIT_MIN_PROG_CHILL    10
#define LIMIT_MIN_PROG_HEAT     10
#define LIMIT_MIN_PROG_DURAT    10
#define LIMIT_MIN_AUTOH_DURAT   0

#define LIMIT_PUMP_LM_CALIBR    40.0
#define LIMIT_BLOW_L_MAX        10.0
#define LIMIT_BLOW_SS_MAX       600
#define LIMIT_BLOW_L_MIN        0.5
#define LIMIT_BLOW_SS_MIN       30

#define LIMIT_TEMPC_SAMPLE_CNT  8

#define EEPROM_LIMIT            2000
#define EEPROM_SIZE             4000
#define LIFE_RW_MIN_T_SIZE      1
#define LIFE_RW_HOUR_T_SIZE     1
#define LIFE_RW_DAY_T_SIZE      1
#define LIFE_RW_MONTH_T_SIZE    1
#define LIFE_RW_YEAR_T_SIZE     2
#define LIFE_RW_CNT_T_SIZE      4
#define LIFE_RW_CYCLE_CNTR_SIZE (LIFE_RW_MIN_T_SIZE + LIFE_RW_HOUR_T_SIZE + LIFE_RW_DAY_T_SIZE + LIFE_RW_MONTH_T_SIZE + LIFE_RW_YEAR_T_SIZE + LIFE_RW_CNT_T_SIZE)
#define LIFE_RW_CYCLE_LIMIT     150000

using namespace std;
using namespace std::placeholders;

template <typename T> 
void RegObjInEEFunc(ObjectUnitModel<T>* &object, EEPROM* ee);

static boolean init_failed = false;

class DBService
{
public: //must be private
    TwoWire *itcw;
    EEPROM* ee24;

public:
    DBService(uint8_t sda, uint8_t scl);
    DBService(TwoWire* itcw);

    boolean IsConnected();
    boolean InitVariables();
    boolean SetDefaultValues();
    uint32_t RWCounterInc();
    void RWCounterAlloc();
    void RWCounterClear();
    void DTImportExport(
        DateTime *DT_obj,
        ObjectUnitModel<uint8_t> *ee_dt_mm,
        ObjectUnitModel<uint8_t> *ee_dt_HH,
        ObjectUnitModel<uint8_t> *ee_dt_DD,
        ObjectUnitModel<uint8_t> *ee_dt_MM,
        ObjectUnitModel<uint16_t> *ee_dt_YYYY,
        boolean import
        );

    DateTime * DT_RTC;
    DateTime * DT_RTC_setter;
    DateTime * DT_Comparator;
    DateTime * DT_TaskCallTime;
    DateTime * DT_TaskProgrStart;
    DateTime * DT_TaskPaused;
    DateTime * DT_TaskFinish;
    DateTime * DT_Temp;

    ObjectUnitModel<uint8_t>    *ee_vars_inited;
    ObjectUnitModel<uint32_t>   *ee_blowgun_wash;
    ObjectUnitModel<double_t>   *ee_blowgun_vol1,
                                *ee_blowgun_vol2,
                                *ee_blowgun_vol3,
                                *ee_pump_calibr;
    ObjectUnitModel<uint8_t>    *ee_solo_heat_tempC,
                                *ee_solo_chill_tempC,
                                *ee_progr_pasteur_tempC,
                                *ee_progr_heat_tempC,
                                *ee_progr_chill_tempC,
                                *ee_progr_mode,
                                *ee_progr_duratMM,
                                *ee_templ_1_pasteur_tempC,
                                *ee_templ_2_pasteur_tempC,
                                *ee_templ_3_pasteur_tempC,
                                *ee_templ_1_heat_tempC,
                                *ee_templ_2_heat_tempC,
                                *ee_templ_3_heat_tempC,
                                *ee_templ_1_chill_tempC,
                                *ee_templ_2_chill_tempC,
                                *ee_templ_3_chill_tempC,
                                *ee_templ_1_mode,
                                *ee_templ_2_mode,
                                *ee_templ_3_mode,
                                *ee_templ_1_duratMM,
                                *ee_templ_2_duratMM,
                                *ee_templ_3_duratMM,
                                *ee_templ_1_startHH,
                                *ee_templ_1_startMM,
                                *ee_templ_2_startHH,
                                *ee_templ_2_startMM,
                                *ee_templ_3_startHH,
                                *ee_templ_3_startMM,
                                *ee_templ_1_runned,
                                *ee_templ_2_runned,
                                *ee_templ_3_runned,
                                *ee_autoH_1_heat_tempC,
                                *ee_autoH_2_heat_tempC,
                                *ee_autoH_3_heat_tempC,
                                *ee_autoH_1_mode,
                                *ee_autoH_2_mode,
                                *ee_autoH_3_mode,
                                *ee_autoH_1_duratMM,
                                *ee_autoH_2_duratMM,
                                *ee_autoH_3_duratMM,
                                *ee_autoH_1_startHH,
                                *ee_autoH_1_startMM,
                                *ee_autoH_2_startHH,
                                *ee_autoH_2_startMM,
                                *ee_autoH_3_startHH,
                                *ee_autoH_3_startMM,
                                *ee_autoH_1_runned,
                                *ee_autoH_2_runned,
                                *ee_autoH_3_runned,
                                *ee_progr_is_running,
                                *ee_progr_choise,
                                *ee_progr_waterJ_filled_yet,
                                *ee_progr_tempC_reached_yet,
                                *ee_progr_phase_1_finish,
                                *ee_progr_phase_2_finish,
                                *ee_autoH_is_running,
                                *ee_autoH_choise;
    ObjectUnitModel<int16_t>    *ee_master_4ma_tempC,
                                *ee_master_20ma_tempC;
    ObjectUnitModel<double_t>   *ee_master_pump_power_lm;
    ObjectUnitModel<uint8_t>    *ee_master_water_saving_toggle,
                                *ee_master_hysteresis_toggle,
                                *ee_master_hysteresis_value;

    ObjectUnitModel<uint8_t>    *ee_task_is_paused;

    ObjectUnitModel<uint8_t>    *ee_task_startHH,
                                *ee_task_startMin,
                                *ee_task_startDD,
                                *ee_task_startMonth;
    ObjectUnitModel<uint16_t>   *ee_task_startYYYY;

    ObjectUnitModel<uint8_t>    *ee_task_callHH,
                                *ee_task_callMin,
                                *ee_task_callDD,
                                *ee_task_callMonth;
    ObjectUnitModel<uint16_t>   *ee_task_callYYYY;

    ObjectUnitModel<uint8_t>    *ee_task_pauseHH,
                                *ee_task_pauseMin,
                                *ee_task_pauseDD,
                                *ee_task_pauseMonth;
    ObjectUnitModel<uint16_t>   *ee_task_pauseYYYY;

    ObjectUnitModel<uint8_t>    *ee_task_finishHH,
                                *ee_task_finishMin,
                                *ee_task_finishDD,
                                *ee_task_finishMonth;
    ObjectUnitModel<uint16_t>   *ee_task_finishYYYY;

    ObjectUnitModel<uint8_t>    *ee_task_pointHH,
                                *ee_task_pointMin,
                                *ee_task_pointDD,
                                *ee_task_pointMonth;
    ObjectUnitModel<uint16_t>   *ee_task_pointYYYY;

    ObjectUnitModel<uint8_t>    *ee_system_run_DD,
                                *ee_system_run_MM;
    ObjectUnitModel<uint16_t>   *ee_system_run_YYYY;
    ObjectUnitModel<uint8_t>    *ee_system_run_mm,
                                *ee_system_run_HH;
    ObjectUnitModel<uint32_t>   *ee_system_dt_cnt;

    vector<ObjectUnitModel<uint8_t>**>
    ee_templ_arr_pasteur_tempC {
        &ee_progr_pasteur_tempC,
        &ee_templ_1_pasteur_tempC,
        &ee_templ_2_pasteur_tempC,
        &ee_templ_3_pasteur_tempC
    },
    ee_templ_arr_heat_tempC {
        &ee_progr_heat_tempC,
        &ee_templ_1_heat_tempC,
        &ee_templ_2_heat_tempC,
        &ee_templ_3_heat_tempC
    },
    ee_templ_arr_chill_tempC {
        &ee_progr_chill_tempC,
        &ee_templ_1_chill_tempC,
        &ee_templ_2_chill_tempC,
        &ee_templ_3_chill_tempC
    },
    ee_templ_arr_mode {
        &ee_progr_mode,
        &ee_templ_1_mode,
        &ee_templ_2_mode,
        &ee_templ_3_mode
    },
    ee_templ_arr_duratMM {
        &ee_progr_duratMM,
        &ee_templ_1_duratMM,
        &ee_templ_2_duratMM,
        &ee_templ_3_duratMM
    },
    ee_templ_arr_startHH {
        &ee_templ_1_startHH,
        &ee_templ_2_startHH,
        &ee_templ_3_startHH
    },
    ee_templ_arr_startMM {
        &ee_templ_1_startMM,
        &ee_templ_2_startMM,
        &ee_templ_3_startMM
    },
    ee_templ_arr_runned {
        &ee_templ_1_runned,
        &ee_templ_2_runned,
        &ee_templ_3_runned
    },
    ee_autoH_arr_heat_tempC {
        &ee_solo_heat_tempC,
        &ee_autoH_1_heat_tempC,
        &ee_autoH_2_heat_tempC,
        &ee_autoH_3_heat_tempC
    },
    ee_autoH_arr_mode {
        &ee_autoH_1_mode,
        &ee_autoH_2_mode,
        &ee_autoH_3_mode
    },
    ee_autoH_arr_duratMM {
        &ee_autoH_1_duratMM,
        &ee_autoH_2_duratMM,
        &ee_autoH_3_duratMM
    },
    ee_autoH_arr_startHH {
        &ee_autoH_1_startHH,
        &ee_autoH_2_startHH,
        &ee_autoH_3_startHH
    },
    ee_autoH_arr_startMM {
        &ee_autoH_1_startMM,
        &ee_autoH_2_startMM,
        &ee_autoH_3_startMM
    },
    ee_autoH_arr_runned {
        &ee_autoH_1_runned,
        &ee_autoH_2_runned,
        &ee_autoH_3_runned
    };

    vector<ObjectUnitModel<double_t>**>
    ee_blow_arr {
        &ee_blowgun_vol1,
        &ee_blowgun_vol2,
        &ee_blowgun_vol3
    };

    // Local var's here (means without calling RegObjInEEFunc() method)
    ObjectUnitModel<uint8_t>    *ram_water_in_jacket,
                                *ram_stop_btn_pressed,
                                *ram_mixer_crash_trigger,
                                *ram_380V_is_connected,
                                *ram_blow_by_blowgun,
                                *ram_blowgun_KB_trigger,
                                *ram_blowgun_trigger,
                                *ram_blowgun_release,
                                *ram_sensor_tempC_error,
                                *ram_menu_tree,
                                *ram_menu_templ,
                                *ram_menu_visual,
                                *ram_menu_element,
                                *ram_blowing_index;
    ObjectUnitModel<int16_t>    *ram_battery_power,
                                *ram_liquid_tempC;

    uint16_t vec_as_que_index = 0;
    vector<double_t> ram_arr_liquid_tempC_sample;
};

#endif