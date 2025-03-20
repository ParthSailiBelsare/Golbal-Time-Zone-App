#include "DSTService.h"

bool DSTService::isDST(const std::tm& time, const TimeZone& tz) {
    if (!tz.observes_dst) return false;

    int month = time.tm_mon + 1;
    int day = time.tm_mday;

    // DST typically starts in March and ends in November
    if ((month > 3 && month < 11) ||
        (month == 3 && day >= 10) ||
        (month == 11 && day <= 5)) {
        return true;
    }
    return false;
}
