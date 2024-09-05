#ifndef RAINBOW_H
#define RAINBOW_H

#include <string>
#include <unordered_map>

// simple Rainbow attack
std::string rainbowAttack(const std::string& target_hash, const std::unordered_map<std::string, std::string>& table) ;

// Main function to initiate rainbow table  cracking
int rain_Crack();

#endif // RAINBOW_H
