#ifndef BRUTE_FORCE__H
#define BRUTE_FORCE__H

#include <string>

// Recursive function to brute-force the password
bool bruteForce(const std::string& current_guess, const std::string& target_hash, const std::string& characters, int max_length);

// Main function to initiate brute-force cracking
int brute_Crack(const std::string& targetString, int maxLength);

#endif // BRUTE_FORCE__H
