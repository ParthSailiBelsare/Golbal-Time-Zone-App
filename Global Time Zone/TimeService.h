#ifndef TIMESERVICE_H
#define TIMESERVICE_H
#include <iostream>
#include <ctime>
#include "TimeZone.h"
#include "DSTService.h"

class TimeService {
public:
    std::tm getCurrentUTCTime();
    std::tm convertTimeZone(const std::tm& utcTime, const TimeZone& source, const TimeZone& target);
    void displayTime(const std::tm& time, const TimeZone& tz, bool isDST);
};

#endif
