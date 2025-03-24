#pragma once
#include <ctime>
#include "TimeZone.h"
#include "LocationService.h"

class TimeService {
public:
    std::tm getCurrentUTCTime();
    std::tm convertTimeZone(const std::tm& utcTime, const TimeZone& source, const TimeZone& target);
    void displayTime(const std::tm& time, const TimeZone& tz, bool isDST);
    void convertUserInputTimeZone(LocationService& locationService);
};
