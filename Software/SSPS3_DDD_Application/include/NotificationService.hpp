#include "el_notification.hpp"
#include <vector>
#include <functional>

#ifndef NIService_hpp
#define NIService_hpp

typedef function<bool(Message message, Icon icon, uint8_t total_messages)> DisplayMessageFunction;
typedef function<bool()> GetStateFunction;

struct ServiceMessage
{
    Message message;
    Icon icon;

    ServiceMessage(Message message, Icon icon)
    {
        this->message = message;
        this->icon = icon;
    }
};

class NIService
{
private:
    DisplayMessageFunction _display_message_f;
    GetStateFunction       _get_state_f;
    vector<ServiceMessage> _messageQueue;
    uint8_t _pop_up_messages_cnt = 0;
    bool _is_message_active = false;

public:
    NIService(DisplayMessageFunction DMfunction, GetStateFunction GSFunction);
    bool display_message(Message message, Icon icon);
    void UserActivity();
    void WorkNIS();
};

#endif