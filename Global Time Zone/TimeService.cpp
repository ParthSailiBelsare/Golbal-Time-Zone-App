#include "TimeService.h"
#include "LocationService.h"
#include "DSTService.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

std::tm TimeService::getCurrentUTCTime() {
    std::time_t now = std::time(nullptr);
    std::tm utcTime;

#ifdef _WIN32
    gmtime_s(&utcTime, &now);
#else
    gmtime_r(&now, &utcTime);
#endif

    return utcTime;
}


//std::tm TimeService::convertTimeZone(const std::tm& sourceTime, const TimeZone& source, const TimeZone& target) {
//    std::tm localTime = sourceTime;
//
//    std::cout << "Source Time in " << source.name << ": "
//        << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
//
//    // Convert source time to UTC
//    double sourceOffset = source.utc_offset;
//    int sourceHours = static_cast<int>(sourceOffset);
//    int sourceMinutes = static_cast<int>((sourceOffset - sourceHours) * 60);
//
//    localTime.tm_hour -= sourceHours;
//    localTime.tm_min -= sourceMinutes;
//    std::mktime(&localTime); // Normalize the time
//
//    std::cout << "Converted to UTC Time: "
//        << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
//
//    // Convert UTC to target time
//    double targetOffset = target.utc_offset;
//    int targetHours = static_cast<int>(targetOffset);
//    int targetMinutes = static_cast<int>((targetOffset - targetHours) * 60);
//
//    localTime.tm_hour += targetHours;
//    localTime.tm_min += targetMinutes;
//    std::mktime(&localTime); // Normalize the time
//
//    // Apply DST if applicable
//    DSTService dstService;
//    if (target.observes_dst && dstService.isDST(localTime, target)) {
//        localTime.tm_hour += 1;
//        std::mktime(&localTime);
//        std::cout << "After DST Adjustment: "
//            << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
//    }
//
//    std::cout << "Final Time in " << target.name << ": "
//        << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
//
//    return localTime;
//}
std::tm TimeService::convertTimeZone(const std::tm& sourceTime, const TimeZone& source, const TimeZone& target) {
    std::tm localTime = sourceTime;

    // First check if DST applies to source timezone and adjust if needed
    DSTService dstService;
    bool sourceDST = source.observes_dst && dstService.isDST(localTime, source);
    std::tm adjustedSourceTime = localTime;
    if (sourceDST) {
        adjustedSourceTime.tm_hour += 1;
        std::mktime(&adjustedSourceTime);
    }

    // Display the source time (including DST adjustment if applicable)
    std::cout << "Source Time in " << source.name << ": "
        << std::put_time(&adjustedSourceTime, "%Y-%m-%d %H:%M:%S")
        << (sourceDST ? " (with DST)" : "") << std::endl;

    // Convert source time to UTC
    double sourceOffset = source.utc_offset;
    int sourceHours = static_cast<int>(sourceOffset);
    int sourceMinutes = static_cast<int>((sourceOffset - sourceHours) * 60);

    localTime.tm_hour -= sourceHours;
    localTime.tm_min -= sourceMinutes;

    // If source has DST, subtract that hour too when converting to UTC
    if (sourceDST) {
        localTime.tm_hour -= 1;
    }

    std::mktime(&localTime); // Normalize the time

    std::cout << "Converted to UTC Time: "
        << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;

    // Convert UTC to target time
    double targetOffset = target.utc_offset;
    int targetHours = static_cast<int>(targetOffset);
    int targetMinutes = static_cast<int>((targetOffset - targetHours) * 60);

    localTime.tm_hour += targetHours;
    localTime.tm_min += targetMinutes;
    std::mktime(&localTime); // Normalize the time

    // Apply DST if applicable to target
    bool targetDST = target.observes_dst && dstService.isDST(localTime, target);
    if (targetDST) {
        localTime.tm_hour += 1;
        std::mktime(&localTime);
        std::cout << "After DST Adjustment: "
            << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    }

    std::cout << "Final Time in " << target.name << ": "
        << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << std::endl;

    return localTime;
}

void TimeService::displayTime(const std::tm& time, const TimeZone& tz, bool isDST) {
    std::cout << "Time in " << tz.name << ": "
        << std::put_time(&time, "%Y-%m-%d %H:%M:%S")
        << " (UTC" << (tz.utc_offset >= 0 ? "+" : "") << tz.utc_offset << ")"
        << (isDST ? " DST" : "") << std::endl;
}

//void TimeService::convertUserInputTimeZone(LocationService& locationService) {
//    std::string sourceCity, targetCity, dateTimeStr;
//
//    // Take user input
//    std::cout << "Enter source city: ";
//    std::cin >> sourceCity;
//    std::cout << "Enter target city: ";
//    std::cin >> targetCity;
//    std::cin.ignore();
//    std::cout << "Enter date and time (YYYY-MM-DD HH:MM): ";
//    std::getline(std::cin, dateTimeStr);
//
//    // Validate cities
//    TimeZone* sourceZone = locationService.getTimeZone(sourceCity);
//    TimeZone* targetZone = locationService.getTimeZone(targetCity);
//
//    if (!sourceZone || !targetZone) {
//        std::cerr << "Invalid source or target city!" << std::endl;
//        return;
//    }
//
//    // Parse input datetime
//    std::tm userTime = {};
//    std::istringstream ss(dateTimeStr);
//    ss >> std::get_time(&userTime, "%Y-%m-%d %H:%M");
//    if (ss.fail()) {
//        std::cerr << "Invalid date-time format! Use YYYY-MM-DD HH:MM" << std::endl;
//        return;
//    }
//
//    // Convert to UTC using source city offset
//    double sourceOffset = sourceZone->utc_offset;
//    DSTService dstService;
//
//    if (sourceZone->observes_dst && dstService.isDST(userTime, *sourceZone)) {
//        sourceOffset += 1.0;
//    }
//
//    std::time_t userTimeT = std::mktime(&userTime) - static_cast<std::time_t>(sourceOffset * 3600);
//    std::tm utcTime;
//
//#ifdef _WIN32
//    gmtime_s(&utcTime, &userTimeT);
//#else
//    gmtime_r(&userTimeT, &utcTime);
//#endif
//
//    // Convert time using existing function
//    std::tm resultTime = convertTimeZone(utcTime, *sourceZone, *targetZone);
//
//    // Display result
//    displayTime(resultTime, *targetZone, dstService.isDST(resultTime, *targetZone));
//}
void TimeService::convertUserInputTimeZone(LocationService& locationService) {
    std::string sourceCity, targetCity, dateTimeStr;

    // Take user input
    std::cout << "Enter source city: ";
    std::cin >> sourceCity;
    std::cout << "Enter target city: ";
    std::cin >> targetCity;
    std::cin.ignore();
    std::cout << "Enter date and time (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, dateTimeStr);

    // Validate cities
    TimeZone* sourceZone = locationService.getTimeZone(sourceCity);
    TimeZone* targetZone = locationService.getTimeZone(targetCity);

    if (!sourceZone || !targetZone) {
        std::cerr << "Invalid source or target city!" << std::endl;
        return;
    }

    // Parse input datetime
    std::tm userTime = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&userTime, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        std::cerr << "Invalid date-time format! Use YYYY-MM-DD HH:MM" << std::endl;
        return;
    }

    // Simply pass the user-provided time directly to convertTimeZone
    // Let convertTimeZone handle the conversion logic
    std::tm resultTime = convertTimeZone(userTime, *sourceZone, *targetZone);

    // Display result
    DSTService dstService;
    displayTime(resultTime, *targetZone, dstService.isDST(resultTime, *targetZone));
}