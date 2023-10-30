#include <Arduino.h>

#ifndef dateTimeBase_hpp
#define dateTimeBase_hpp

typedef std::function<void(int32_t)> ExtraDayOffsetFunction;

class Time
{
private:
    tm  left_ttm,
        right_ttm;
    time_t  left_tt,
            right_tt; 

    uint32_t Hours = 0;
    uint32_t Minutes = 0;
    uint32_t Seconds = 0;
    uint32_t Millis = 0;
    int64_t ExtraDays = 0;

    ExtraDayOffsetFunction IncDayOffsetFunction;
    ExtraDayOffsetFunction* IncDayOffsetFunctionPtr;
    ExtraDayOffsetFunction DecDayOffsetFunction;
    ExtraDayOffsetFunction* DecDayOffsetFunctionPtr;

    void _setTimeT(Time* Left, Time* Right);
    static uint32_t _millisDiff(Time* Left, Time* Right);

public:
    Time();
    Time(uint8_t Hours, uint8_t Minutes, uint8_t Seconds);
    Time(uint8_t Hours, uint8_t Minutes, uint8_t Seconds, uint16_t Millis);
    Time* SetIncDayOffset(ExtraDayOffsetFunction OffsetFunction);
    Time* SetDecDayOffset(ExtraDayOffsetFunction OffsetFunction);
    Time* SetTime(uint8_t Hours, uint8_t Minutes, uint8_t Seconds);
    Time* SetTime(uint8_t Hours, uint8_t Minutes, uint8_t Seconds, uint16_t Millis);
    Time* SetTime(Time* Parent);
    Time* IncHours(uint32_t Hours);
    Time* IncMinutes(uint32_t Minutes);
    Time* IncSeconds(uint32_t Seconds);
    Time* IncMillis(uint32_t Millis);
    Time* DecHours(uint32_t Hours);
    Time* DecMinutes(uint32_t Minutes);
    Time* DecSeconds(uint32_t Seconds);
    Time* DecMillis(uint32_t Millis);
    boolean IsBigger(Time* than);
    boolean IsSmaller(Time* than);
    boolean IsEquals(Time* that);
    boolean IsEqualsMS(Time* that);
    int32_t DiffInSeconds(Time* Ref, boolean isABS = true);
    int64_t DiffInMillis(Time* Ref, boolean isABS = true);
    uint8_t HH();
    uint8_t MM();
    uint8_t SS();
    uint16_t MS();

    boolean operator < (Time second)        { return this->IsSmaller(&second); }
    boolean operator > (Time second)        { return this->IsBigger(&second); }
    boolean operator |= (Time second)       { return this->IsEquals(&second); }
    boolean operator == (Time second)       { return this->IsEqualsMS(&second); }
    Time* operator = (Time second)          { return this->SetTime(&second); }
    Time* operator + (uint32_t seconds)     { return this->IncSeconds(seconds); }
    Time* operator << (uint32_t millis)     { return this->IncMillis(millis); }
    Time* operator - (uint32_t seconds)     { return this->DecSeconds(seconds); }
    Time* operator >> (uint32_t millis)     { return this->DecMillis(millis); }
    uint64_t operator - (Time * rt)         { return this->DiffInSeconds(rt); }
};

class Date
{
private:
    static const uint32_t yearRef = 1900;
    tm  left_dtm,
        right_dtm;
    time_t  left_dt,
            right_dt; 

    uint32_t Day = 0;
    uint32_t Month = 0;
    uint32_t Year = 0;

    static uint8_t _totalDaysInMonth(int32_t Year, int32_t Month);
    static uint8_t _dayOfTheWeek(int32_t Year, int32_t Month, int32_t Day);
    void _setDateT(Date* Left, Date* Right);

public:
    Date();
    Date(uint8_t Day, uint8_t Month, uint16_t Year);
    Date* SetDate(uint8_t Day, uint8_t Month, uint16_t Year);
    Date* SetDate(Date* Parent);
    Date* IncDay(uint32_t Day);
    Date* IncMonth(uint32_t Month);
    Date* IncYear(uint32_t Year);
    Date* DecDay(uint32_t Day);
    Date* DecMonth(uint32_t Month);
    Date* DecYear(uint32_t Year);
    boolean IsBigger(Date* than);
    boolean IsSmaller(Date* than);
    boolean IsEquals(Date* that);
    int64_t DiffInDays(Date* Ref, boolean isABS = true);
    uint8_t DD();
    uint8_t MM();
    uint16_t YYYY();

    boolean operator < (Date second)        { return this->IsSmaller(&second); }
    boolean operator > (Date second)        { return this->IsBigger(&second); }
    boolean operator == (Date second)       { return this->IsEquals(&second); }
    Date* operator = (Date second)          { return this->SetDate(&second); }
    Date* operator + (uint32_t days)        { return this->IncDay(days); }
    Date* operator - (uint32_t days)        { return this->DecDay(days); }
    uint64_t operator - (Date * rd)         { return (uint64_t)this->DiffInDays(rd); }
};

#endif