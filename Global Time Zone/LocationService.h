#pragma once
#include <map>
#include <string>
#include "TimeZone.h"

class LocationService {
public:
    std::map<std::string, TimeZone> getAllTimeZones() const;

private:
    std::map<std::string, TimeZone> timeZones;
public:
    LocationService();
    TimeZone* getTimeZone(const std::string& location);
    void displayAvailableTimeZones();
};
