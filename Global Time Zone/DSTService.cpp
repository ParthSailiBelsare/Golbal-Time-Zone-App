#include "DSTService.h"
#include <iostream>
#include <iomanip>

bool DSTService::isDST(const std::tm& time, const TimeZone& tz) {
    /*std::cout << "Here"<<"\n";
    std::cout<<std::put_time(&time, "%Y-%m-%d %H:%M:%S")<<"\n";
    std::cout << "\n";*/
    int toggle;
    std::cout << "Toggle DST on/off. Press 1 for on and 0 for off " << tz.name <<":";
    std::cin >> toggle;
    int month = time.tm_mon + 1;

    switch (toggle) {
    case 1: 
        if (!tz.observes_dst) return false;

        
        /*std::cout << month;*/
        //int day = time.tm_mday;
        //int weekday = time.tm_wday; // 0-6, 0 is Sunday
        //int year = time.tm_year + 1900;

        if (month == 1 || month == 2 || month == 12) return false;

        // Specific check for US DST (similar approach can be adapted for other regions)
        if (month > 3 && month < 11) return true;

        //// More precise DST start and end for US (second Sunday in March, first Sunday in November)
        //if (month == 3) {
        //    // Find the second Sunday in March
        //    int firstDayOfMonth = (time.tm_mday - (time.tm_wday + 7 - time.tm_mday % 7) % 7);
        //    return firstDayOfMonth >= 8 && firstDayOfMonth <= 14 && weekday == 0;
        //}

        //if (month == 11) {
        //    // Find the first Sunday in November
        //    int firstDayOfMonth = (time.tm_mday - (time.tm_wday + 7 - time.tm_mday % 7) % 7);
        //    return firstDayOfMonth <= 7 && weekday == 0;
        //}

        return false;
        break;

    case 0:
        return false;
        break;
        
    }
    
}
