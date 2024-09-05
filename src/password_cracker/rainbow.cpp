#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <openssl/sha.h>
#include "utils/utils.h"

// Generate a simple rainbow table
std::unordered_map<std::string, std::string> generateRainbowTable(const std::vector<std::string>& passwords) {
    std::unordered_map<std::string, std::string> table;
    for (const auto& password : passwords) {
        table[sha256(password)] = password;
    }
    return table;
}

// Rainbow table attack
std::string rainbowAttack(const std::string& target_hash, const std::unordered_map<std::string, std::string>& table) {
    auto it = table.find(target_hash);
    if (it != table.end()) {
        return it->second;
    }
    return "";
}

int rain_Crack() {
    std::vector<std::string> passwords = {"password", "123456", "letmein"};
    std::string target_password = "123456";
    std::string target_hash = sha256(target_password);
    auto table = generateRainbowTable(passwords);
    std::string found_password = rainbowAttack(target_hash, table);
    
    if (!found_password.empty()) {
        std::cout << "Password found: " << found_password << std::endl;
    } else {
        std::cout << "Password not found in rainbow table." << std::endl;
    }
    
    return 0;
}