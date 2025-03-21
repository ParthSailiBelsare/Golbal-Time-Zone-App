#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    std::string username;
    std::string password;
    std::vector<std::string> favoriteTimeZones;

    // Default constructor
    User() = default;

    // Parameterized constructor
    User(std::string uname, std::string pwd) : username(uname), password(pwd) {}
};

#endif
