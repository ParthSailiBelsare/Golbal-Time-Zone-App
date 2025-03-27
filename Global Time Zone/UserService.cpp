#include "UserService.h"
#include <iostream>
#include <fstream>
#include <sstream>

void UserService::loadUsers() {
    std::ifstream file("users.csv");
    if (!file.is_open()) return;

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string username, password, timeZone;
        getline(ss, username, ',');
        getline(ss, password, ',');
        User user(username, password);
        while (getline(ss, timeZone, ',')) {
            user.favoriteTimeZones.push_back(timeZone);
        }
        users[username] = user;
    }
    file.close();
}

void UserService::saveUsers() {
    std::ofstream file("users.csv");
    for (const auto& pair : users) {
        const User& user = pair.second;
        file << user.username << "," << user.password;
        for (const auto& tz : user.favoriteTimeZones) {
            file << "," << tz;
        }
        file << "\n";
    }
    file.close();
}

bool UserService::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        std::cout << "Username already exists.\n";
        return false;
    }
    users[username] = User(username, password);
    saveUsers();
    std::cout << "User registered successfully!\n";
    return true;
}

bool UserService::loginUser(const std::string& username, const std::string& password) {
    if (users.find(username) == users.end() || users[username].password != password) {
        std::cout << "Invalid username or password.\n";
        return false;
    }
    std::cout << "Login successful. Welcome, " << username << "!\n";
    return true;
}

void UserService::addFavoriteTimeZone(const std::string& username, const std::string& timezone) {
    if (users.find(username) == users.end()) {
        std::cout << "User not found.\n";
        return;
    }
    users[username].favoriteTimeZones.push_back(timezone);
    saveUsers();
    std::cout << "Time zone added to favorites.\n";
}

void UserService::viewFavoriteTimeZones(const std::string& username) {
    if (users.find(username) == users.end()) {
        std::cout << "User not found.\n";
        return;
    }
    std::cout << "Favorite Time Zones for " << username << ":\n";
    for (const auto& tz : users[username].favoriteTimeZones) {
        std::cout << "- " << tz << "\n";
    }
}
