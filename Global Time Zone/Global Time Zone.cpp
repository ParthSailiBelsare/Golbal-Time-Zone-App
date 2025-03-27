#include <iostream>
#include "TimeService.h"
#include "DSTService.h"
#include "LocationService.h"
#include "UserService.h"
#include<iomanip>

void showMenu() {
    std::cout << "\nGlobal Time Zone Application\n";
    std::cout << "1. View Current Time\n";
    std::cout << "2. Convert Time Between Time Zones\n";
    std::cout << "3. View Available Time Zones\n";
    std::cout << "4. Register\n";
    std::cout << "5. Login\n";
    std::cout << "6. Add Favorite Time Zone\n";
    std::cout << "7. View Favorite Time Zones\n";
    std::cout << "8. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    TimeService timeService;
    LocationService locationService;
    DSTService dstService;
    UserService userService;

    int choice;
    std::string username, password, timezone;
    bool loggedIn = false;

    do {
        showMenu();
        std::cin >> choice;
        std::string city1, city2;
        std::tm utcTime, resultTime;
        TimeZone* srcTZ = nullptr;
        TimeZone* tgtTZ = nullptr;

        switch (choice) {
        case 1:
            std::cout << "Enter city name: ";
            std::cin.ignore();
            std::getline(std::cin,city1);
            if (auto* tz = locationService.getTimeZone(city1)) {
                utcTime = timeService.getCurrentUTCTime();

                // Calculate local time using the offset from UTC
                std::time_t utcTimeT = std::mktime(&utcTime);
                utcTimeT += tz->utc_offset * 3600; // Convert hours to seconds

                std::tm localTime;
                if (localtime_s(&localTime, &utcTimeT) != 0) {
                    std::cerr << "Failed to convert time.\n";
                    break;
                }

                timeService.displayTime(localTime, *tz, dstService.isDST(localTime, *tz));
            }
            else {
                std::cout << "City not found.\n";
            }
            break;


        case 2: 
            std::cout << "Do you want to convert specific time and date(y/n): ";
            char ch;
            std::cin >> ch;
            switch (ch) {
            case 'y':timeService.convertUserInputTimeZone(locationService);
                break;

            case 'n':
                std::cout << "Enter source city: ";
                std::cin.ignore();
                std::getline(std::cin, city1);

                std::cout << "Enter target city: ";
                std::getline(std::cin,city2);

                // Clear invalid input
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter valid city names.\n";
                    break;
                }

                // Fetch Time Zones
                srcTZ = locationService.getTimeZone(city1);
                tgtTZ = locationService.getTimeZone(city2);

                if (!srcTZ) {
                    std::cout << "Source city not found.\n";
                }
                else if (!tgtTZ) {
                    std::cout << "Target city not found.\n";
                }
                else {
                    // Get current UTC time
                    utcTime = timeService.getCurrentUTCTime();

                    // Calculate source local time from UTC
                    std::tm srcLocalTime = utcTime;
                    double srcOffset = srcTZ->utc_offset;
                    int srcHours = static_cast<int>(srcOffset);
                    int srcMinutes = static_cast<int>((srcOffset - srcHours) * 60);
                    srcLocalTime.tm_hour += srcHours;
                    srcLocalTime.tm_min += srcMinutes;
                    std::mktime(&srcLocalTime);

                    // Now convert from source to target
                    resultTime = timeService.convertTimeZone(srcLocalTime, *srcTZ, *tgtTZ);

                    // Check for DST and display the result
                    DSTService dstService;
                    /*bool isDst = dstService.isDST(resultTime, *tgtTZ);*/
                    /*timeService.displayTime(resultTime, *tgtTZ, isDst);*/
                }
                break;
            }
            break;
            

        case 3:
            std::cout << std::left << std::setw(20) << "City"
                << std::setw(15) << "UTC Offset"
                << std::setw(25) << "Local Time"
                << std::setw(10) << "DST"
                << std::endl;
            std::cout << std::string(70, '-') << std::endl;

            for (const auto& pair : locationService.getAllTimeZones()) {
                TimeZone tz = pair.second;
                std::tm utcTime = timeService.getCurrentUTCTime();

                // Extract hours and minutes from offset
                int hours = tz.utc_offset;
                int minutes = static_cast<int>((tz.utc_offset - hours) * 60);

                // Calculate local time using UTC offset
                std::tm localTime = utcTime;
                localTime.tm_hour += hours;
                localTime.tm_min += minutes;

                // Normalize the time
                mktime(&localTime);

                std::ostringstream localTimeStr;
                localTimeStr << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

                std::ostringstream offsetStr;
                offsetStr << "UTC" << (tz.utc_offset >= 0 ? "+" : "")
                    << hours << (minutes != 0 ? ":" + std::to_string(abs(minutes)) : "");

                std::cout << std::left << std::setw(20) << pair.first
                    << std::setw(15) << offsetStr.str()
                    << std::setw(25) << localTimeStr.str()
                    << std::setw(10) << (tz.observes_dst ? "Yes" : "No")
                    << std::endl;
            }
            break;


        case 4:
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;
            userService.registerUser(username, password);
            break;

        case 5:
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;
            loggedIn = userService.loginUser(username, password);
            break;

        case 6:
            if (loggedIn) {
                std::cout << "Enter Time Zone to Add (e.g., Sydney, Tokyo): ";
                std::cin >> timezone;
                userService.addFavoriteTimeZone(username, timezone);
            }
            else {
                std::cout << "Please log in first.\n";
            }
            break;

        case 7:
            if (loggedIn) {
                userService.viewFavoriteTimeZones(username);
            }
            else {
                std::cout << "Please log in first.\n";
            }
            break;

        case 8:
            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
