#include <iostream>
#include "TimeService.h"
#include "DSTService.h"
#include "LocationService.h"

void showMenu() {
    std::cout << "\nGlobal Time Zone Application\n";
    std::cout << "1. View Current Time\n";
    std::cout << "2. Convert Time Between Time Zones\n";
    std::cout << "3. View Available Time Zones\n";
    std::cout << "4. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    TimeService timeService;
    LocationService locationService;
    DSTService dstService;

    int choice;
    do {
        showMenu();
        std::cin >> choice;
        std::string city1, city2;
        std::tm utcTime, resultTime;

        switch (choice) {
        case 1:
            std::cout << "Enter city name: ";
            std::cin >> city1;
            if (auto* tz = locationService.getTimeZone(city1)) {
                utcTime = timeService.getCurrentUTCTime();
                resultTime = timeService.convertTimeZone(utcTime, TimeZone("UTC", 0, false), *tz);
                timeService.displayTime(resultTime, *tz, dstService.isDST(resultTime, *tz));
            }
            else {
                std::cout << "City not found.\n";
            }
            break;

        case 2:
            std::cout << "Enter source city: ";
            std::cin >> city1;
            std::cout << "Enter target city: ";
            std::cin >> city2;
            if (auto* srcTZ = locationService.getTimeZone(city1)) {
                /*std::cout << srcTZ;
                std::cout << "\n";*/

                if (auto* tgtTZ = locationService.getTimeZone(city2)) {
                    /*std::cout << tgtTZ;
                    std::cout << "\n";*/
                    utcTime = timeService.getCurrentUTCTime();

                    resultTime = timeService.convertTimeZone(utcTime, *srcTZ, *tgtTZ);
                    timeService.displayTime(resultTime, *tgtTZ, dstService.isDST(resultTime, *tgtTZ));
                }
                else {
                    std::cout << "Target city not found.\n";
                }
            }
            else {
                std::cout << "Source city not found.\n";
            }
            break;

        case 3:
            locationService.displayAvailableTimeZones();
            break;

        case 4:
            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
