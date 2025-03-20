#ifndef DSTSERVICE_H
#define DSTSERVICE_H
#include <ctime>
#include "TimeZone.h"

class DSTService {
public:
    bool isDST(const std::tm& time, const TimeZone& tz);
};

#endif