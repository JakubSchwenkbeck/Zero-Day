#include "password_cracker/brute_force.h"
#include <string>
#include <iostream>

int main(){


    // Choice of Tool:
    int choice;
    std::cout << "Choose a tool:\n";
    std::cout << "1. Brute Force\n";
    std::cin >> choice;


    // if cases for choice:
 if (choice == 1) {  // Brute force password cracking


        std::cout << "Enter Hash to crack: \n" ; //Get hash to crack param
        std::string toCrack;
        std::cin >> toCrack;


        std::cout << "Entered: "<< toCrack << " \n \n Please enter max length: \n"; // get Max Pass Length to crack
        int Max;
        std::cin >> Max;


        std::cout << "Bruteforce started!" << std::endl; // start cracking hash
        Crack(toCrack,Max);

    } else {
        std::cout << "Invalid choice!" << std::endl; // default else
    }

   
    return 0;

}