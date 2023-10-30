#include "../include/main.hpp"

TwoWire * itcw;
RtcDS3231<TwoWire> * DS3231;

IOService * IO;
KBService * KB;
DBService * DB;
UIService * UI;
RTCService * RTC;
NaviService * NS;
TaskService * TS;
NIService * NIS;

/* HW INT */
void Interrupt_KBService() { KB->KeyPadInterrupt = true; }
void Interrupt_IOService() { IO->DInInterrupt = true; }

void io_ui_refresh();
void ns_btn_init();
void _goto_main_page();
void _menu_next(boolean to_top);

void setup()
{
    Serial.begin(115200);
    Serial.println("init");
    
    itcw = new TwoWire(0);
    itcw->setPins(SDA, SCL);
    itcw->begin(SDA, SCL, 100000);

    DS3231 = new RtcDS3231<TwoWire>(*itcw);
    DS3231->Begin();
    Serial.println("ds init");

    IO = new IOService(itcw);
    IO->InitPeriphery();
    if (IO->IsConnected())
    {
        pinMode(ESP_DIN_INT_PIN, INPUT_PULLUP);
        attachInterrupt(ESP_DIN_INT_PIN, Interrupt_IOService, FALLING);
    }
    Serial.println("io init");

    KB = new KBService(itcw);
    KB->InitPeriphery();
    if (KB->IsConnected())
    {
        pinMode(ESP_KEY_INT_PIN, INPUT_PULLUP);
        attachInterrupt(ESP_KEY_INT_PIN, Interrupt_KBService, FALLING);
    }
    Serial.println("kb init");

    DB = new DBService(itcw);
    DB->InitVariables();
    //DB->SetDefaultValues();
    Serial.println("db init");

    DB->ram_liquid_tempC->Value     = 0;
    DB->ram_menu_tree->Value        = 0;
    DB->ram_menu_templ->Value       = 0;
    DB->ram_menu_visual->Value      = 0;
    DB->ram_menu_element->Value     = 0;
    DB->ram_blowing_index->Value    = 0;

    RTC = new RTCService(&DS3231, &DB->DT_RTC);
    RTC->RefreshDT(true);
    Serial.println("rtc init");

    //DB->RWCounterClear();
    DB->RWCounterAlloc();
    Serial.println("rtc to db init");

    UI = new UIService(&DB);
    UI->init_screen();
    UI->init_controls();
    UI->data_refresh_await();
    UI->data_refresh_task();
    UI->data_refresh_blow();
    UI->data_refresh_settings();
    UI->show_scr_await();
    Serial.println("ui init");

    NS = new NaviService(&KB);
    ns_btn_init();
    NS->navi_scr_await->template_set();
    Serial.println("ns init");

    NIS = new NIService(
        [](Message message, Icon icon, uint8_t total_messages) { return UI->NotificationC.display_message(message, icon, total_messages); },
        []() { return UI->NotificationC.get_state(); }
        );
    NIS->display_message(Message::Hello, Icon::Salutem);

    TS = new TaskService(&DB, &IO, &UI, &NS, &NIS);
    Serial.println("ts init");
}

void loop()
{
    if (KB->ReadKB() == KeyboardCallback::KBPress)
        NIS->UserActivity();

    if (RTC->RefreshDT())
    {
        UI->DateTimeC.set_time(DB->DT_RTC->time->HH(), DB->DT_RTC->time->MM(), DB->DT_RTC->time->SS());
        UI->DateTimeC.set_date(DB->DT_RTC->date->DD(), DB->DT_RTC->date->MM(), DB->DT_RTC->date->YYYY());
    }

    if (IO->ReadIN())
    {
        // stop
        DB->ram_stop_btn_pressed->Value     = IO->OptIn_StopBTN->Value();
        if (DB->ram_stop_btn_pressed->Value == 1) //prod
        //if (DB->ram_stop_btn_pressed->Value == 0) //debug
        {
            TS->stop_task();
            NIS->display_message(Message::StopPressed, Icon::Info);
        }

        // blowgun
        DB->ram_blowgun_trigger->Value      = IO->OptIn_Blowgun->Value();
        if (DB->ram_blowgun_trigger->Value == 1)
        {
            if (NS->page() == NaviPage::Blowing)
                TS->run_blowing(DB->ram_blowing_index->Value, true);
            DB->ram_blowgun_release->Value = 1;
        }
        else
            DB->ram_blowgun_release->Value = 0;

        // temperature (celsius)
        int16_t tempC_sample = IO->vAnIn_LiqTempC->Value();
        if (tempC_sample > 5)
        {
            DB->ram_arr_liquid_tempC_sample[DB->vec_as_que_index] = SENS_TEMPC_STATE(tempC_sample);
            DB->vec_as_que_index = ++DB->vec_as_que_index >= LIMIT_TEMPC_SAMPLE_CNT ? 0 : DB->vec_as_que_index;
        }
        
        if (DB->vec_as_que_index == 0)
            DB->ram_liquid_tempC->Value = static_cast<int16_t>(
                accumulate(DB->ram_arr_liquid_tempC_sample.begin(), DB->ram_arr_liquid_tempC_sample.end(), 0) /
                DB->ram_arr_liquid_tempC_sample.size()
            );

        // battery power(charge) by voltage
        DB->ram_battery_power->Value        = SENS_BATT_STATE(IO->vAnIn_Battery->Value());

        // other sensors
        DB->ram_water_in_jacket->Value      = IO->OptIn_WaterJ->Value();
        DB->ram_mixer_crash_trigger->Value  = IO->OptIn_MixerCrash->Value();
        DB->ram_380V_is_connected->Value    = IO->OptIn_380V->Value();

        io_ui_refresh();
    }
    IO->SafeIO();

    if (TS->startup_executed)
        TS->update_datetime();
    TS->WorkTS();

    NIS->WorkNIS();
    lv_timer_handler();
}

void io_ui_refresh()
{
    UI->BlowProgC.set_tempC(DB->ram_liquid_tempC->Value);
    UI->StateInfoC.set_tempC(DB->ram_liquid_tempC->Value);
    UI->StateInfoC.set_wj_state(
        DB->ram_water_in_jacket->Value == 0 ? false : true,
        IO->Relay_WaterJ->get_value()
        );
    UI->Battery.set_val(static_cast<uint8_t>(DB->ram_battery_power->Value));
    UI->Battery.set_isChargering(DB->ram_380V_is_connected->Value == 0 ? false : true);

    uint8_t wd_on_counter = 0;
    for(uint8_t index = 0; index < 3; index++)
    {
        (*DB->ee_templ_arr_mode[index + 1])->Value > 0 ? ++wd_on_counter : 0;
        (*DB->ee_autoH_arr_mode[index])->Value > 0 ? ++wd_on_counter : 0;
    }
    UI->StateInfoC.set_wd_state(wd_on_counter, 6);
}

static vector<KeyModel> kb_scr_await
{
    KeyModel(KeyType::L_STACK_4, []() { if (TS->run_pasteurizing()) { NS->navi_scr_task->template_set(); UI->show_scr_task(); } }),
    KeyModel(KeyType::L_STACK_3, []() { if (TS->run_chilling()) { NS->navi_scr_task->template_set(); UI->show_scr_task(); } }),
    KeyModel(KeyType::L_STACK_2, []() { if (TS->run_heating()) { NS->navi_scr_task->template_set(); UI->show_scr_task(); } }),
    KeyModel(KeyType::L_STACK_1, []() { TS->stop_task(); NIS->display_message(Message::StopPressed, Icon::Info); }),
    KeyModel(KeyType::RIGHT_TOP, []() { NS->navi_scr_settings->template_set(0); UI->show_scr_settings(); }),
    KeyModel(KeyType::R_STACK_4, []() { UI->show_scr_blowing(); UI->BlowSelectC.select_val(DB->ram_blowing_index->Value = 0); NS->navi_scr_blow->template_set(); }),
    KeyModel(KeyType::R_STACK_3, []() { UI->show_scr_blowing(); UI->BlowSelectC.select_val(DB->ram_blowing_index->Value = 1); NS->navi_scr_blow->template_set(); }),
    KeyModel(KeyType::R_STACK_2, []() { UI->show_scr_blowing(); UI->BlowSelectC.select_val(DB->ram_blowing_index->Value = 2); NS->navi_scr_blow->template_set(); }),
    KeyModel(KeyType::R_STACK_1, []() { UI->show_scr_blowing(); UI->BlowSelectC.select_val(DB->ram_blowing_index->Value = 3); NS->navi_scr_blow->template_set(); })
};