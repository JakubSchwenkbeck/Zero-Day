#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>


// Symmetirc encryption: 

// XOR 
std::string XOR(const std::string& msg,const std::string& key){

   // std::cout << msg.length() << "   " << key.length() << std::endl;
    if(msg.length() < key.length()){
        throw std::invalid_argument("msg length insufficent"); 
         //   std::cout << msg.length() << "   " << key.length() << std::endl;

    }


  //  std::string result; 
    std::string result(msg.length(), '\0');  // Initialize result string
    
    for(size_t i = 0;i < msg.length(); i++ ){
        result[i] = msg[i] ^ key[i % key.length()]; // bit wise XOR , handling padding of key
    }

   

}

// Symmetric encryption: Caesar Cipher (Shift Cipher)
std::string CaesarCipher(const std::string& msg, int shift) {
    std::string result = msg;
    shift = shift % 26;  // Ensure shift is within the alphabet range

    for (size_t i = 0; i < msg.length(); i++) {
        if (isalpha(msg[i])) {  // Apply only to alphabetic characters
            char base = islower(msg[i]) ? 'a' : 'A';
            result[i] = (msg[i] - base + shift) % 26 + base;
        }
    }

    return result;
}
// Symmetric encryption: Vigenère Cipher
std::string VigenereCipher(const std::string& msg, const std::string& key) {
    std::string result = msg;
    size_t keyLen = key.length();
    
    for (size_t i = 0; i < msg.length(); i++) {
        if (isalpha(msg[i])) {  // Apply only to alphabetic characters
            char base = islower(msg[i]) ? 'a' : 'A';
            char keyBase = islower(key[i % keyLen]) ? 'a' : 'A';
            result[i] = (msg[i] - base + (key[i % keyLen] - keyBase)) % 26 + base;
        }
    }

    return result;
}
// Symmetric encryption: Simple Substitution Cipher (AES-like basic substitution)
std::string SimpleSubstitutionCipher(const std::string& msg, const std::string& key) {
    if (key.length() != 26) {
        throw std::invalid_argument("Substitution key must be 26 characters long for English alphabet.");
    }

    std::string result = msg;

    for (size_t i = 0; i < msg.length(); i++) {
        if (isalpha(msg[i])) {
            char base = islower(msg[i]) ? 'a' : 'A';
            int index = msg[i] - base;
            result[i] = islower(msg[i]) ? tolower(key[index]) : toupper(key[index]);
        }
    }

    return result;
}
int main(){
try {
        // Test XOR Cipher
        std::cout << "XOR Cipher: " << XOR("HelloWorld", "monkey") << std::endl;

        // Test Caesar Cipher
        std::cout << "Caesar Cipher (shift 3): " << CaesarCipher("HelloWorld", 3) << std::endl;

        // Test Vigenère Cipher
        std::cout << "Vigenère Cipher: " << VigenereCipher("HelloWorld", "key") << std::endl;

        // Test Simple Substitution Cipher
        std::string substitutionKey = "QWERTYUIOPLKJHGFDSAZXCVBNM"; // 26 characters mapping alphabet
        std::cout << "Substitution Cipher: " << SimpleSubstitutionCipher("HelloWorld", substitutionKey) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
