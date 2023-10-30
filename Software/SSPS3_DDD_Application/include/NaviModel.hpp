#include "../../SSPS3_DDD_Domain/include/keyModel.hpp"
#include "../../SSPS3_DDD_Core/include/KBService.hpp"

#ifndef NaviModel_hpp
#define NaviModel_hpp

enum class NaviPage : uint8_t { Await, Task, Blowing, Settings };

class NaviModel
{
private:
    KBService* KB;
    NaviPage page;
    NaviPage* presenter;

    uint8_t selected = 0;
    vector<vector<KeyModel>*> kbTemplates;

public:
    NaviModel(KBService** KB, NaviPage page, NaviPage *presenter);
    void template_set(uint8_t selected = 0);
    NaviModel* template_add(vector<KeyModel> * kbTemplate);
    void template_next();
    void template_prev();
    uint8_t templates_cnt();
    NaviPage page_type();
};

#endif