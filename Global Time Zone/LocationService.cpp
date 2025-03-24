#include "LocationService.h"
#include <iostream>

LocationService::LocationService() {
    timeZones["NewYork"] = TimeZone("New York", -4, true);
    timeZones["London"] = TimeZone("London", 0, true);
    timeZones["Tokyo"] = TimeZone("Tokyo", 9, false);
    timeZones["Sydney"] = TimeZone("Sydney", 11, false);
    timeZones["LosAngeles"] = TimeZone("Los Angeles", -7, false);
    timeZones["Chicago"] = TimeZone("Chicago", -5, false);
    timeZones["Paris"] = TimeZone("Paris", 1, true);
    timeZones["Berlin"] = TimeZone("Berlin", 1, true);
    timeZones["Moscow"] = TimeZone("Moscow", 3, false);
    timeZones["Beijing"] = TimeZone("Beijing", 8, false);
    timeZones["Delhi"] = TimeZone("Delhi", 5.5, false);
    timeZones["Dubai"] = TimeZone("Dubai", 4, false);
    timeZones["Singapore"] = TimeZone("Singapore", 8, false);
    timeZones["HongKong"] = TimeZone("Hong Kong", 8, false);
    timeZones["Seoul"] = TimeZone("Seoul", 9, false);
    timeZones["Bangkok"] = TimeZone("Bangkok", 7, false);
    timeZones["Cairo"] = TimeZone("Cairo", 2, true);
    timeZones["Johannesburg"] = TimeZone("Johannesburg", 2, false);
    timeZones["Istanbul"] = TimeZone("Istanbul", 3, true);
    timeZones["MexicoCity"] = TimeZone("Mexico City", -6, true);
    timeZones["Toronto"] = TimeZone("Toronto", -4, true);
    timeZones["BuenosAires"] = TimeZone("Buenos Aires", -3, false);
    timeZones["RioDeJaneiro"] = TimeZone("Rio de Janeiro", -3, true);
    timeZones["Jakarta"] = TimeZone("Jakarta", 7, false);
    timeZones["Karachi"] = TimeZone("Karachi", 5, false);
    timeZones["Athens"] = TimeZone("Athens", 2, true);
    timeZones["Rome"] = TimeZone("Rome", 1, true);
    timeZones["Lisbon"] = TimeZone("Lisbon", 0, true);
    timeZones["Warsaw"] = TimeZone("Warsaw", 1, true);
    timeZones["KualaLumpur"] = TimeZone("Kuala Lumpur", 8, false);
    timeZones["Bangladesh"] = TimeZone("Dhaka", 6, false);
    timeZones["Nairobi"] = TimeZone("Nairobi", 3, false);
    timeZones["Tehran"] = TimeZone("Tehran", 3.5, true);
    timeZones["Helsinki"] = TimeZone("Helsinki", 2, true);
    timeZones["Stockholm"] = TimeZone("Stockholm", 1, true);
    timeZones["Manila"] = TimeZone("Manila", 8, false);
    timeZones["Auckland"] = TimeZone("Auckland", 13, true);
    timeZones["Honolulu"] = TimeZone("Honolulu", -10, false);
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
std::map<std::string, TimeZone> LocationService::getAllTimeZones() const {
    return timeZones;
}

