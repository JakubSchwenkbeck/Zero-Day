#include <iostream>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
//#include "utils/utils.h"


// Global variables for synchronization
std::mutex mtx;
std::condition_variable cv;
bool found = false;


// Function to compute SHA256 hash
std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);
    char buf[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(buf + i * 2, "%02x", hash[i]);
    }
    return std::string(buf);
}


// Recursively tries every combination of characters to brute-force the password
void bruteForce(const std::string& current_guess, const std::string& target_hash, const std::string& characters, int max_length) {
    if (found) return;  // Stop if the password has already been found

    std::string current_hash = sha256(current_guess);

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Trying: " << current_guess << " -> Hash: " << current_hash << std::endl;
    }

    if (current_hash == target_hash) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            found = true;
            std::cout << "Password found! It is: " << current_guess << std::endl;
            cv.notify_all();  // Notify all threads that the password is found
        }
        return;
    }

    if (current_guess.length() >= max_length) {
        return;
    }

    std::vector<std::thread> threads;

    for (char c : characters) {
        threads.emplace_back([=]() {
            bruteForce(current_guess + c, target_hash, characters, max_length);
        });
    }

    for (auto& t : threads) {
        t.join();  // Wait for all threads to finish
    }
}

int brute_Crack(const std::string& targetString, int maxLength) {
    std::string target_password = targetString;
    std::string target_hash = sha256(target_password);

    std::string characters = "abcdefghijklmnopqrstuvwxyz0123456789";

    int max_length = (maxLength > 0) ? maxLength : 10; // Default to 10 if maxLength is not provided

    std::cout << "Starting brute-force attack for hash: " << target_hash << std::endl;
   // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    bruteForce("", target_hash, characters, max_length);
 // Stop timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

    if (!found) {
        std::cout << "Password not found within the given character set and length limit." << std::endl;
    }

    return 0;
}


