#include <Arduino.h>
#include "./dateTimeBase.hpp"

#ifndef dateTimeModel_hpp
#define dateTimeModel_hpp

class DateTime
{
private:
    static const uint32_t yearRef = 1900;
    void _setReferences();
    void _setDateT(DateTime* Left, DateTime* Right);

    tm  left_fdtm,
        right_fdtm;
    time_t  left_fdt,
            right_fdt; 

public:
    Time* time;
    Date* date;

    DateTime();
    DateTime(uint32_t Hours, uint32_t Minutes, uint32_t Seconds);
    DateTime(uint32_t Hours, uint32_t Minutes, uint32_t Seconds, uint32_t Millis);
    DateTime(
        uint32_t Hours, uint32_t Minutes, uint32_t Seconds,
        uint32_t Day, uint32_t Month, uint32_t Year
    );
    DateTime(
        uint32_t Hours, uint32_t Minutes, uint32_t Seconds, uint32_t Millis,
        uint32_t Day, uint32_t Month, uint32_t Year
    );

    uint32_t TimeInSS();
    int64_t DiffDateTimeInSS(DateTime* rdt, boolean isABS = true);

    DateTime* operator = (DateTime second)  { this->time->SetTime(second.time); this->date->SetDate(second.date); return this; }
    boolean operator < (DateTime second)    { return DiffDateTimeInSS(&second, false) < 0 ? true : false; }
    boolean operator > (DateTime second)    { return DiffDateTimeInSS(&second, false) > 0 ? true : false; }
    boolean operator == (DateTime second)   { return DiffDateTimeInSS(&second, false) == 0 ? true : false; }
    DateTime* operator + (uint32_t seconds) { time->IncSeconds(seconds); return this; }
    DateTime* operator - (uint32_t seconds) { time->DecSeconds(seconds); return this; }
};

#endif