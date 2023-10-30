#include "./NaviModel.hpp"

#ifndef NaviService_hpp
#define NaviService_hpp

class NaviService
{
private:
    NaviPage current_page = NaviPage::Await;

public:
    NaviService(KBService** KB);
    NaviModel   *navi_scr_task,
                *navi_scr_blow,
                *navi_scr_await,
                *navi_scr_settings,
                *navi_settings_elements;

    NaviModel   *navi_debug;

    NaviPage page();
};

#endif