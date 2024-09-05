#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>

// simple dictonary attack
std::string dictionaryAttack(const std::string& target_hash, const std::string& dictionary_file);

// Main function to initiate dict cracking
int dict_Crack(const std::string& targetString);

#endif // DICTIONARY_H
