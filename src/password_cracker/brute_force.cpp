#include <iostream>
#include <openssl/sha.h>
#include <string>
#include <vector>

using namespace std;

// Helper function to compute SHA256 hash of the input string
string sha256(const string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    string output;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        output += buffer;
    }
    return output;
}

// Recursively tries every combination of characters to brute-force the password
bool bruteForce(const string& current_guess, const string& target_hash, const string& characters, int max_length) {
    // Calculate the SHA256 hash of the current guess
    string current_hash = sha256(current_guess);

    // Print the current guess (optional, can be removed if too slow)
    cout << "Trying: " << current_guess << " -> Hash: " << current_hash << endl;

    // Check if the guessed hash matches the target hash
    if (current_hash == target_hash) {
        cout << "Password found! It is: " << current_guess << endl;
        return true;
    }

    // Stop if the maximum password length is reached
    if (current_guess.length() >= max_length) {
        return false;
    }

    // Recursively try every character in the character set
    for (char c : characters) {
        if (bruteForce(current_guess + c, target_hash, characters, max_length)) {
            return true;
        }
    }

    return false;
}

int Crack(const string& targetString,int maxLength ) {
    // The hash of the password we're trying to guess (replace this with your target hash)
    string target_password = targetString;
    string target_hash = sha256(target_password);

    // Character set to brute-force from (e.g., lowercase letters and digits)
    string characters = "abcdefghijklmnopqrstuvwxyz0123456789";

    // Maximum password length to try (to limit the brute-force search)

    int max_length;
    if (maxLength > 0){
     max_length = maxLength; 
    }else {
         max_length = 10; // default
    }

    // Start the brute-force attack
    cout << "Starting brute-force attack for hash: " << target_hash << endl;

    if (!bruteForce("", target_hash, characters, max_length)) {
        cout << "Password not found within the given character set and length limit." << endl;
    } 

    return 0;
}
/*
int main(){
    Crack("aaa",4);
    return 0;
}*/