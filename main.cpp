#include "password_cracker/brute_force.h"
#include <string>
#include <iostream>

int main(){

    int choice;
    std::cout << "Choose a tool:\n";
    std::cout << "1. Brute Force\n";
    std::cin >> choice;


 if (choice == 1) {
        std::cout << "Enter Hash to crack: \n" ;
        std::string toCrack;
        std::cin >> toCrack;
        std::cout << "Entered: "<< toCrack << " \n \n Please enter max length: \n";
        int Max;
        std::cin >> Max;
        std::cout << "Bruteforce started!" << std::endl;
        Crack(toCrack,Max);

    } else {
        std::cout << "Invalid choice!" << std::endl;
    }

   
    return 0;

}