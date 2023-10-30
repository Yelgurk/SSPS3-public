#include <lvgl.h>
#include <string.h>
#include <string>
#include "lv_resources.hpp"
#include "lv_helper.hpp"

#ifndef el_task_c_hpp
#define el_task_c_hpp

using namespace std;

enum class ProgrMode : uint8_t {
    PasteurOnly,
    PasteurChilling,
    PasteurFull,
    Chilling,
    Heating
};

class el_task_c
{
private:
    lv_obj_t * ui_TaskContainer;
    lv_obj_t * ui_TaskProgress;
    lv_obj_t * ui_TaskPercentage;
    lv_obj_t * ui_TaskDuration;
    lv_obj_t * ui_TaskInfo;
    lv_obj_t * ui_statePanel;
    lv_obj_t * ui_startTime;
    lv_obj_t * ui_Finishtime;
    lv_obj_t * ui_taskName;
    lv_obj_t * ui_LapLine;
    lv_obj_t * ui_tempCAim;
    lv_obj_t * ui_pasteurTempCAimLabel;
    lv_obj_t * ui_chillingTempCAimLabel;
    lv_obj_t * ui_heatingTempCAimLabel;
    lv_obj_t * ui_pasteurTempC;
    lv_obj_t * ui_pasteurDurationMM;
    lv_obj_t * ui_chillingTempC;
    lv_obj_t * ui_heatingTempC;
    lv_obj_t * ui_pasteurTempCCheck;
    lv_obj_t * ui_chillingTempCCheck;
    lv_obj_t * ui_heatingTempCCheck;
    lv_obj_t * ui_finishInfoContainer;
    lv_obj_t * ui_finishInfo;
    lv_obj_t * ui_finishInfoBackLabel;
    lv_obj_t * ui_finishInfoBackImg;

    char str_t_start[5];
    char str_t_finish[5];
    char str_t_durat[8];

    void _set_icon(uint8_t workPauseFinish);
    void _set_bar_color(uint8_t workPause);

public:
    void display(lv_obj_t *screen);
    void hide();
    void show();
    void vs_set_name(string progr_name);
    void vs_set_mode(ProgrMode progr_mode);
    void vs_set_start_ss(uint32_t start_t_ss);
    void vs_set_finish_ss(uint32_t finish_t_ss);
    void vs_set_gone_ss(uint32_t gone_t_ss);
    void vs_set_progr_bar(uint16_t progress_var);
    void vs_set_pasteur_tempC(uint8_t tempC);
    void vs_set_pasteur_duratMM(uint8_t duratMM);
    void vs_set_chilling_tempC(uint8_t tempC);
    void vs_set_heating_tempC(uint8_t tempC);
    void vs_set_pasteur_flag(bool flag);
    void vs_set_chilling_flag(bool flag);
    void vs_set_heating_flag(bool flag);
    void vs_set_theme(uint8_t theme_index);
    void vs_set_theme_start();
    void vs_set_theme_pause();
    void vs_set_theme_resume();
    void vs_set_theme_finish();
};

#endif