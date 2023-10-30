#include "../include/el_task_c.hpp"

void el_task_c::display(lv_obj_t *screen)
{
    ui_TaskContainer = lv_obj_create(screen);
    lv_obj_set_width(ui_TaskContainer, 300);
    lv_obj_set_height(ui_TaskContainer, 240);
    lv_obj_set_x(ui_TaskContainer, 80);
    lv_obj_set_y(ui_TaskContainer, 30);
    lv_obj_set_align(ui_TaskContainer, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TaskContainer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_TaskContainer, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TaskContainer, lv_color_hex(0xAAAAAA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TaskContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TaskContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_TaskContainer, lv_color_hex(0x9B9B9B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_TaskContainer, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_TaskContainer, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_TaskContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_TaskContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_TaskContainer, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TaskContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TaskContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TaskContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TaskContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TaskProgress = lv_arc_create(ui_TaskContainer);
    lv_obj_set_width(ui_TaskProgress, 300);
    lv_obj_set_height(ui_TaskProgress, 300);
    lv_obj_set_align(ui_TaskProgress, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_TaskProgress, 0, 1000);
    lv_arc_set_value(ui_TaskProgress, 85);
    lv_arc_set_bg_angles(ui_TaskProgress, 91, 89);
    lv_obj_set_style_arc_color(ui_TaskProgress, lv_color_hex(0x4040FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_TaskProgress, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_TaskProgress, -125, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TaskProgress, -125, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TaskProgress, -125, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TaskProgress, -125, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_TaskProgress, 200, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_TaskProgress, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_img_src(ui_TaskProgress, &ui_img_pbmaskinproc4_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_img_src(ui_TaskProgress, &ui_img_pbmaskawait4_png, LV_PART_INDICATOR | LV_STATE_USER_1);

    lv_obj_set_style_bg_color(ui_TaskProgress, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TaskProgress, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_TaskPercentage = lv_label_create(ui_TaskContainer);
    lv_obj_set_width(ui_TaskPercentage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TaskPercentage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TaskPercentage, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_TaskPercentage, "85%");
    lv_obj_set_style_text_font(ui_TaskPercentage, &MontserratInt24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TaskPercentage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TaskPercentage, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TaskPercentage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TaskPercentage, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TaskDuration = lv_label_create(ui_TaskContainer);
    lv_obj_set_width(ui_TaskDuration, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TaskDuration, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TaskDuration, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_TaskDuration, "01:35:15");
    lv_obj_set_style_text_font(ui_TaskDuration, &MontserratInt24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TaskDuration, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TaskDuration, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TaskDuration, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TaskDuration, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TaskInfo = lv_obj_create(ui_TaskContainer);
    lv_obj_set_width(ui_TaskInfo, 260);
    lv_obj_set_height(ui_TaskInfo, 190);
    lv_obj_set_x(ui_TaskInfo, 0);
    lv_obj_set_y(ui_TaskInfo, -5);
    lv_obj_set_align(ui_TaskInfo, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TaskInfo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_TaskInfo, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TaskInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_TaskInfo, lv_color_hex(0x9B9B9B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_TaskInfo, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_TaskInfo, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_TaskInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_TaskInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_TaskInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_statePanel = lv_obj_create(ui_TaskInfo);
    lv_obj_set_width(ui_statePanel, 100);
    lv_obj_set_height(ui_statePanel, 50);
    lv_obj_set_x(ui_statePanel, 0);
    lv_obj_set_y(ui_statePanel, 70);
    lv_obj_set_align(ui_statePanel, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_statePanel, LV_STATE_USER_1);       /// States
    lv_obj_clear_flag(ui_statePanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_width(ui_statePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_statePanel, &ui_img_play_png, LV_PART_MAIN | LV_STATE_USER_1);
    lv_obj_set_style_bg_img_src(ui_statePanel, &ui_img_pause_png, LV_PART_MAIN | LV_STATE_USER_2);
    lv_obj_set_style_bg_img_src(ui_statePanel, &ui_img_flag_start_png, LV_PART_MAIN | LV_STATE_USER_3);

    ui_startTime = lv_label_create(ui_TaskInfo);
    lv_obj_set_width(ui_startTime, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_startTime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_startTime, -75);
    lv_obj_set_y(ui_startTime, 70);
    lv_obj_set_align(ui_startTime, LV_ALIGN_CENTER);
    lv_label_set_text(ui_startTime, "16:35");
    lv_obj_set_style_text_font(ui_startTime, &MontserratInt24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Finishtime = lv_label_create(ui_TaskInfo);
    lv_obj_set_width(ui_Finishtime, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Finishtime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Finishtime, 75);
    lv_obj_set_y(ui_Finishtime, 70);
    lv_obj_set_align(ui_Finishtime, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Finishtime, "18:23");
    lv_obj_set_style_text_font(ui_Finishtime, &MontserratInt24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_taskName = lv_label_create(ui_TaskInfo);
    lv_obj_set_width(ui_taskName, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_taskName, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_taskName, 0);
    lv_obj_set_y(ui_taskName, -70);
    lv_obj_set_align(ui_taskName, LV_ALIGN_CENTER);
    lv_label_set_text(ui_taskName, "Будильник #1");
    lv_obj_set_style_text_font(ui_taskName, &MontserratInt28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LapLine = lv_obj_create(ui_TaskContainer);
    lv_obj_set_width(ui_LapLine, 4);
    lv_obj_set_height(ui_LapLine, 30);
    lv_obj_set_x(ui_LapLine, 0);
    lv_obj_set_y(ui_LapLine, 105);
    lv_obj_set_align(ui_LapLine, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_LapLine, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_LapLine, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LapLine, lv_color_hex(0x323232), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LapLine, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_LapLine, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tempCAim = lv_obj_create(ui_TaskContainer);
    lv_obj_set_width(ui_tempCAim, 260);
    lv_obj_set_height(ui_tempCAim, 95);
    lv_obj_set_x(ui_tempCAim, 0);
    lv_obj_set_y(ui_tempCAim, -5);
    lv_obj_set_align(ui_tempCAim, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_tempCAim, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_tempCAim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_tempCAim, lv_color_hex(0xDCDCDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tempCAim, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_tempCAim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_tempCAim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_tempCAim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_tempCAim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_tempCAim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pasteurTempCAimLabel = lv_label_create(ui_tempCAim);
    lv_obj_set_width(ui_pasteurTempCAimLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_pasteurTempCAimLabel, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_pasteurTempCAimLabel, "Нагрев");
    lv_obj_set_style_text_font(ui_pasteurTempCAimLabel, &MontserratInt22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pasteurTempCAimLabel, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pasteurTempCAimLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pasteurTempCAimLabel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pasteurTempCAimLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chillingTempCAimLabel = lv_label_create(ui_tempCAim);
    lv_obj_set_width(ui_chillingTempCAimLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_chillingTempCAimLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_chillingTempCAimLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_chillingTempCAimLabel, "Охлажд.");
    lv_obj_set_style_text_font(ui_chillingTempCAimLabel, &MontserratInt22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_chillingTempCAimLabel, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_chillingTempCAimLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_chillingTempCAimLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_chillingTempCAimLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_heatingTempCAimLabel = lv_label_create(ui_tempCAim);
    lv_obj_set_width(ui_heatingTempCAimLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_heatingTempCAimLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_heatingTempCAimLabel, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_heatingTempCAimLabel, "Поддерж.");
    lv_obj_set_style_text_font(ui_heatingTempCAimLabel, &MontserratInt22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_heatingTempCAimLabel, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_heatingTempCAimLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_heatingTempCAimLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_heatingTempCAimLabel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pasteurTempC = lv_label_create(ui_tempCAim);
    lv_obj_set_width(ui_pasteurTempC, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_pasteurTempC, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_pasteurTempC, "65°C");
    lv_obj_set_style_text_font(ui_pasteurTempC, &MontserratInt22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pasteurTempC, 135, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pasteurTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pasteurTempC, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pasteurTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pasteurDurationMM = lv_label_create(ui_tempCAim);
    lv_obj_set_width(ui_pasteurDurationMM, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_pasteurDurationMM, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_pasteurDurationMM, "60м.");
    lv_obj_set_style_text_font(ui_pasteurDurationMM, &MontserratInt22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pasteurDurationMM, 198, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pasteurDurationMM, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pasteurDurationMM, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pasteurDurationMM, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chillingTempC = lv_label_create(ui_tempCAim);
    lv_obj_set_width(ui_chillingTempC, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_chillingTempC, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_chillingTempC, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_chillingTempC, "40 °C");
    lv_obj_set_style_text_font(ui_chillingTempC, &MontserratInt24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_chillingTempC, 170, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_chillingTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_chillingTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_chillingTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_heatingTempC = lv_label_create(ui_tempCAim);
    lv_obj_set_width(ui_heatingTempC, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_heatingTempC, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_heatingTempC, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_heatingTempC, "45 °C");
    lv_obj_set_style_text_font(ui_heatingTempC, &MontserratInt24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_heatingTempC, 170, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_heatingTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_heatingTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_heatingTempC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pasteurTempCCheck = lv_checkbox_create(ui_tempCAim);
    lv_checkbox_set_text(ui_pasteurTempCCheck, "");
    lv_obj_set_width(ui_pasteurTempCCheck, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_pasteurTempCCheck, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_pasteurTempCCheck, 10);
    lv_obj_set_y(ui_pasteurTempCCheck, 4);
    lv_obj_add_flag(ui_pasteurTempCCheck, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_letter_space(ui_pasteurTempCCheck, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_line_space(ui_pasteurTempCCheck, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    lv_obj_set_style_border_color(ui_pasteurTempCCheck, lv_color_hex(0x323232), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_pasteurTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_pasteurTempCCheck, lv_color_hex(0x8CCB5E), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_pasteurTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(ui_pasteurTempCCheck, lv_color_hex(0x8CCB5E), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(ui_pasteurTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_chillingTempCCheck = lv_checkbox_create(ui_tempCAim);
    lv_checkbox_set_text(ui_chillingTempCCheck, "");
    lv_obj_set_width(ui_chillingTempCCheck, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_chillingTempCCheck, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_chillingTempCCheck, 10);
    lv_obj_set_y(ui_chillingTempCCheck, 0);
    lv_obj_set_align(ui_chillingTempCCheck, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_chillingTempCCheck, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    lv_obj_set_style_border_color(ui_chillingTempCCheck, lv_color_hex(0x323232), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_chillingTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_chillingTempCCheck, lv_color_hex(0x8CCB5E), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_chillingTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(ui_chillingTempCCheck, lv_color_hex(0x8CCB5E), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(ui_chillingTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_heatingTempCCheck = lv_checkbox_create(ui_tempCAim);
    lv_checkbox_set_text(ui_heatingTempCCheck, "");
    lv_obj_set_width(ui_heatingTempCCheck, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_heatingTempCCheck, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_heatingTempCCheck, 10);
    lv_obj_set_y(ui_heatingTempCCheck, -4);
    lv_obj_set_align(ui_heatingTempCCheck, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_heatingTempCCheck, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    lv_obj_set_style_border_color(ui_heatingTempCCheck, lv_color_hex(0x323232), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_heatingTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_heatingTempCCheck, lv_color_hex(0x8CCB5E), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_heatingTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(ui_heatingTempCCheck, lv_color_hex(0x8CCB5E), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(ui_heatingTempCCheck, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_finishInfoContainer = lv_obj_create(ui_TaskContainer);
    lv_obj_set_width(ui_finishInfoContainer, 260);
    lv_obj_set_height(ui_finishInfoContainer, 95);
    lv_obj_set_x(ui_finishInfoContainer, 0);
    lv_obj_set_y(ui_finishInfoContainer, -5);
    lv_obj_set_align(ui_finishInfoContainer, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_finishInfoContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_finishInfoContainer, lv_color_hex(0xDCDCDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_finishInfoContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_finishInfoContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_finishInfoContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_finishInfoContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_finishInfoContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_finishInfoContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_finishInfo = lv_label_create(ui_finishInfoContainer);
    lv_obj_set_align(ui_finishInfo, LV_ALIGN_CENTER);
    lv_obj_set_y(ui_finishInfo, -15);
    lv_obj_set_style_text_font(ui_finishInfo, &MontserratInt28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_finishInfo, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_finishInfo, "Завершено");

    ui_finishInfoBackLabel = lv_label_create(ui_finishInfoContainer);
    lv_obj_set_align(ui_finishInfoBackLabel, LV_ALIGN_CENTER);
    lv_obj_set_y(ui_finishInfoBackLabel, 15);
    lv_obj_set_x(ui_finishInfoBackLabel, -11);
    lv_obj_set_style_text_font(ui_finishInfoBackLabel, &MontserratInt24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_finishInfoBackLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_finishInfoBackLabel, "нажмите \"назад\"");

    ui_finishInfoBackImg = lv_img_create(ui_finishInfoContainer);
    lv_obj_set_align(ui_finishInfoBackImg, LV_ALIGN_CENTER);
    lv_img_set_src(ui_finishInfoBackImg, &ui_img_back_png);
    lv_obj_set_y(ui_finishInfoBackImg, 16);
    lv_obj_set_x(ui_finishInfoBackImg, 110);
}

void el_task_c::_set_icon(uint8_t workPauseFinish)
{
    lv_obj_clear_state(ui_statePanel, LV_STATE_USER_1);
    lv_obj_clear_state(ui_statePanel, LV_STATE_USER_2);
    lv_obj_clear_state(ui_statePanel, LV_STATE_USER_3);

    switch (workPauseFinish)
    {
    case 0: lv_obj_add_state(ui_statePanel, LV_STATE_USER_1); break;
    case 1: lv_obj_add_state(ui_statePanel, LV_STATE_USER_2); break;
    case 2: lv_obj_add_state(ui_statePanel, LV_STATE_USER_3); break;
    default: break;
    }
}

void el_task_c::_set_bar_color(uint8_t workPause)
{
    if (workPause == 0) 
        lv_obj_clear_state(ui_statePanel, LV_STATE_USER_2);
    else
        lv_obj_add_state(ui_statePanel, LV_STATE_USER_2);
}

void el_task_c::hide()
{
    lv_obj_add_flag(ui_TaskContainer, LV_OBJ_FLAG_HIDDEN);
}

void el_task_c::show()
{
    lv_obj_clear_flag(ui_TaskContainer, LV_OBJ_FLAG_HIDDEN);
}

void el_task_c::vs_set_name(string progr_name)
{
    lv_label_set_text(ui_taskName, progr_name.c_str());
}

void el_task_c::vs_set_mode(ProgrMode progr_mode)
{
    lv_obj_clear_flag(ui_pasteurTempCCheck, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_pasteurTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_pasteurTempC, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_pasteurDurationMM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(ui_chillingTempCCheck, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_chillingTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_chillingTempC, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(ui_heatingTempCCheck, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_heatingTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_heatingTempC, LV_OBJ_FLAG_HIDDEN);

    switch (progr_mode)
    {
    case ProgrMode::PasteurChilling : {
        lv_obj_add_flag(ui_heatingTempCCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_heatingTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_heatingTempC, LV_OBJ_FLAG_HIDDEN);
    } break;

    case ProgrMode::PasteurOnly : {
        lv_obj_add_flag(ui_chillingTempCCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_chillingTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_chillingTempC, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(ui_heatingTempCCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_heatingTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_heatingTempC, LV_OBJ_FLAG_HIDDEN);
    } break;

    case ProgrMode::Chilling : {
        lv_obj_add_flag(ui_pasteurTempCCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_pasteurTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_pasteurTempC, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_pasteurDurationMM, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(ui_heatingTempCCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_heatingTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_heatingTempC, LV_OBJ_FLAG_HIDDEN);
    } break;

    case ProgrMode::Heating : {
        lv_obj_add_flag(ui_pasteurTempCCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_pasteurTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_pasteurTempC, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_pasteurDurationMM, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(ui_chillingTempCCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_chillingTempCAimLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_chillingTempC, LV_OBJ_FLAG_HIDDEN);
    } break;
    
    default:
        break;
    }
}

void el_task_c::vs_set_start_ss(uint32_t start_t_ss)
{
    sprintf(str_t_start, "%02d:%02d", start_t_ss / 3600, (start_t_ss % 3600) / 60);
    lv_label_set_text(ui_startTime, str_t_start);
}

void el_task_c::vs_set_finish_ss(uint32_t finish_t_ss)
{
    sprintf(str_t_finish, "%02d:%02d", finish_t_ss / 3600, (finish_t_ss % 3600) / 60);
    lv_label_set_text(ui_Finishtime, str_t_finish);
}

void el_task_c::vs_set_gone_ss(uint32_t gone_t_ss)
{
    sprintf(str_t_durat, "%02d:%02d:%02d", gone_t_ss / 3600, (gone_t_ss % 3600) / 60, gone_t_ss % 60);
    lv_label_set_text(ui_TaskDuration, str_t_durat);
}

void el_task_c::vs_set_progr_bar(uint16_t progress_var)
{
    progress_var = progress_var > 1000 ? 1000 : progress_var;
    lv_label_set_text(ui_TaskPercentage, (to_string(progress_var / 10) + "%").c_str());
    lv_arc_set_value(ui_TaskProgress, progress_var);
}

void el_task_c::vs_set_pasteur_tempC(uint8_t tempC)
{
    lv_label_set_text(ui_pasteurTempC, (to_string(tempC) + "°C").c_str());
}

void el_task_c::vs_set_pasteur_duratMM(uint8_t duratMM)
{
    lv_label_set_text(ui_pasteurDurationMM, (to_string(duratMM) + "м.").c_str());
}

void el_task_c::vs_set_chilling_tempC(uint8_t tempC)
{
    lv_label_set_text(ui_chillingTempC, (to_string(tempC) + " °C").c_str());
}

void el_task_c::vs_set_heating_tempC(uint8_t tempC)
{
    lv_label_set_text(ui_heatingTempC, (to_string(tempC) + " °C").c_str());
}

void el_task_c::vs_set_pasteur_flag(bool flag)
{
    if (flag)
        lv_obj_add_state(ui_pasteurTempCCheck, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_pasteurTempCCheck, LV_STATE_CHECKED);
}

void el_task_c::vs_set_chilling_flag(bool flag)
{
    if (flag)
        lv_obj_add_state(ui_chillingTempCCheck, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_chillingTempCCheck, LV_STATE_CHECKED);
}

void el_task_c::vs_set_heating_flag(bool flag)
{
    if (flag)
        lv_obj_add_state(ui_heatingTempCCheck, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_heatingTempCCheck, LV_STATE_CHECKED);
}

void el_task_c::vs_set_theme(uint8_t theme_index)
{
    switch (theme_index)
    {
    case 0: vs_set_theme_start(); break;
    case 1: vs_set_theme_pause();  break;
    case 2: vs_set_theme_resume();  break;
    default: vs_set_theme_finish(); break;
    }
}

void el_task_c::vs_set_theme_start()
{
    lv_label_set_text(ui_TaskPercentage, "0%");
    vs_set_theme_resume();
    vs_set_progr_bar(0);
    vs_set_gone_ss(0);
    vs_set_pasteur_flag(false);
    vs_set_chilling_flag(false);
    vs_set_heating_flag(false);
}

void el_task_c::vs_set_theme_pause()
{
    lv_obj_add_flag(ui_finishInfoContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_state(ui_TaskProgress, LV_STATE_USER_1);
    _set_icon(1);
    _set_bar_color(1);
}

void el_task_c::vs_set_theme_resume()
{
    lv_obj_add_flag(ui_finishInfoContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_state(ui_TaskProgress, LV_STATE_USER_1);
    _set_icon(0);
    _set_bar_color(0);
}

void el_task_c::vs_set_theme_finish()
{
    lv_obj_clear_state(ui_TaskProgress, LV_STATE_USER_1);
    lv_obj_clear_flag(ui_finishInfoContainer, LV_OBJ_FLAG_HIDDEN);
    vs_set_progr_bar(1000);
    _set_icon(2);
    _set_bar_color(0);
}