#include <iostream>
#include <thread>
#include <mutex>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

// Mutex to protect shared data
std::mutex mtx; 
int counter = 0; 

// Function to convert byte array to hex string
std::string to_hex_string(const unsigned char* hash, size_t length) {
    std::stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// Function to compute SHA-256 hash of a string
std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    return to_hex_string(hash, SHA256_DIGEST_LENGTH);
}

// Function to increment the counter and hash it
void increment(int id) {
    for (int i = 0; i < 5; ++i) {
        // Lock the mutex before accessing the shared variable
        std::lock_guard<std::mutex> lock(mtx);

        ++counter;
        // Compute SHA-256 hash of the current counter value
        std::string counter_str = std::to_string(counter);
        std::string hash = sha256(counter_str);

        std::cout << "Thread " << id << " incremented counter to " << counter 
                  << " (SHA-256 hash: " << hash << ")" << std::endl;
        // Mutex is automatically released when lock goes out of scope
    }
}

int main() {
    // Create multiple threads
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);
    std::thread t3(increment, 3);

    // Wait for all threads to finish
    t1.join();
    t2.join();
    t3.join();

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
