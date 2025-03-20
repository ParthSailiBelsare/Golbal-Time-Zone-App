#include "TimeService.h"
#include <iomanip>

std::tm TimeService::getCurrentUTCTime() {
    std::time_t now = std::time(nullptr);
    std::tm utcTime;

#ifdef _WIN32
    gmtime_s(&utcTime, &now);
#endif

    return utcTime;
}

std::tm TimeService::convertTimeZone(const std::tm& utcTime, const TimeZone& source, const TimeZone& target) {
    std::tm localTime = utcTime;
    std::cout << "UTC Time: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    localTime.tm_hour += (target.utc_offset - source.utc_offset);
    std::cout << "After Time Zone Adjustment: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;

    DSTService dstService;
    if (target.observes_dst && dstService.isDST(localTime, target)) {
        localTime.tm_hour += 1;
        std::cout << "After DST Adjustment: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    }

    std::mktime(&localTime); // Normalize time
    std::cout << "After Normalization: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    return localTime;
}

void TimeService::displayTime(const std::tm& time, const TimeZone& tz, bool isDST) {
    std::cout << "Time in " << tz.name << ": "
        << std::put_time(&time, "%Y-%m-%d %H:%M:%S")
        << " (UTC" << (tz.utc_offset >= 0 ? "+" : "") << tz.utc_offset << ")"
        << (isDST ? " DST" : "") << std::endl;
}
