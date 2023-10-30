#include <lgfx_user/LGFX_ESP32_sample.hpp>
#include <lvgl.h>
#include "../../SSPS3_DDD_Core/include/DBService.hpp"
#include "../../SSPS3_DDD_Domain/include/objectUnitModel.hpp"

#include "el_battery.hpp"
#include "el_dateTime_c.hpp"
#include "el_task_c.hpp"
#include "el_stateInfo.hpp"
#include "el_blowHelp.hpp"
#include "el_blowSelect.hpp"
#include "el_blowProg.hpp"
#include "el_awaitInfo.hpp"
#include "el_settings.hpp"
#include "el_notification.hpp"

#ifndef UIService_hpp
#define UIService_hpp

enum class MenuPage { RTC, Solo, Calibr, Pasteur, Templ_Arr, AutoH_Arr, _last };
enum class BlowingState { Available, Volume, Time };

#define LGFX_USE_V1
#define SCREEN_WIDTH    480U
#define SCREEN_HEIGHT   320U
#define SCREEN_BUFFER   1024U * 40U

static LGFX lcd;
static lv_color_t buf1 [SCREEN_BUFFER];
static lv_color_t buf2 [SCREEN_BUFFER];
static lv_disp_draw_buf_t draw_buf;

static lv_obj_t * ui_Screen1;

static void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
    lcd.endWrite();

    lv_disp_flush_ready(disp);
}

class UIService
{
private:
    void _hide_all_controls();
    DBService *DB;

public:
    UIService(DBService** DB);
    void init_screen();
    void init_controls();

    BlowingState blowing_state = BlowingState::Available;

    el_battery Battery;
    el_dateTime_c DateTimeC;
    el_task_c TaskC;
    el_stateInfo StateInfoC;
    el_blowHelp BlowHelpC;
    el_blowSelect BlowSelectC;
    el_blowProg BlowProgC;
    el_awaitInfo AwaitInfoC;
    el_settings SettingsC;
    el_notification NotificationC;

    void show_scr_task();
    void show_scr_await();
    void show_scr_blowing();
    void show_scr_settings();
    void show_scr(uint8_t page);
    void progr_blowing(uint32_t full, uint32_t left, double_t power_lm);
    void data_refresh_task();
    void data_refresh_await();
    void data_refresh_blow();
    void data_refresh_settings();
    void data_refresh_settings(uint8_t menu_index);
};

#endif