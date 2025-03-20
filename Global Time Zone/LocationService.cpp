#include "LocationService.h"
#include <iostream>

LocationService::LocationService() {
    timeZones["NewYork"] = TimeZone("New York", -4, false);
    timeZones["London"] = TimeZone("London", 0, true);
    timeZones["Tokyo"] = TimeZone("Tokyo", 9, false);
    timeZones["Sydney"] = TimeZone("Sydney", 11, false);
}

TimeZone* LocationService::getTimeZone(const std::string& location) {
    if (timeZones.find(location) != timeZones.end()) {
        return &timeZones[location];
    }
    return nullptr;
}

void LocationService::displayAvailableTimeZones() {
    for (const auto& pair : timeZones) {
        std::cout << pair.first << " (UTC " << pair.second.utc_offset
            << (pair.second.observes_dst ? " with DST)" : ")") << std::endl;
    }
}
