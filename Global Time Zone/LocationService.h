#ifndef LOCATIONSERVICE_H
#define LOCATIONSERVICE_H
#include <map>
#include <string>
#include "TimeZone.h"

class LocationService {
private:
    std::map<std::string, TimeZone> timeZones;
public:
    LocationService();
    TimeZone* getTimeZone(const std::string& location);
    void displayAvailableTimeZones();
};

#endif
