#include <iostream>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <fstream>
#include "utils/utils.h"


// Dictionary attack using an imput txt file with a word in each line
std::string dictionaryAttack(const std::string& target_hash, const std::string& dictionary_file) {
    std::ifstream file(dictionary_file);
    std::string password;
    while (std::getline(file, password)) {
        if (sha256(password) == target_hash) {
            return password;
        }
    }
    return "";
}


int dict_Crack(const std::string& targetString){
    std::string target_password = targetString;
    std::string target_hash = sha256(target_password);
    std::string found_password = dictionaryAttack(target_hash, "dictionary.txt");
    
    if (!found_password.empty()) {
        std::cout << "Password found: " << found_password << std::endl;
    } else {
        std::cout << "Password not found in dictionary." << std::endl;
    }
    
    return 0;

}