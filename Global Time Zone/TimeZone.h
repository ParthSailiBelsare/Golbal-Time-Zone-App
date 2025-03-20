#ifndef TIMEZONE_H
#define TIMEZONE_H
#include <string>

class TimeZone {
public:
    std::string name;
    int utc_offset;
    bool observes_dst;

    // Default constructor
    TimeZone() : name("Unknown"), utc_offset(0), observes_dst(false) {}

    // Parameterized constructor
    TimeZone(std::string n, int offset, bool dst)
        : name(n), utc_offset(offset), observes_dst(dst) {
    }
};

#endif
