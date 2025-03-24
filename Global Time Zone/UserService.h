#pragma once
#include "User.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

class UserService {
private:
    std::unordered_map<std::string, User> users;

public:
    UserService() { loadUsers(); }
    void loadUsers();
    void saveUsers();
    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    void addFavoriteTimeZone(const std::string& username, const std::string& timezone);
    void viewFavoriteTimeZones(const std::string& username);
};
