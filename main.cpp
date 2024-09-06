#include "password_cracker/brute_force.h"
#include "password_cracker/dictionary.h"

#include <string>
#include <iostream>
void CLI_password_cracker();
void printHome();
int main(){

// Choice of Branch:
    printHome();

    int choice;
      std::cin >> choice;
   // if cases for choice:
 if     (choice == 1) {  // Password Cracking

    CLI_password_cracker();

 }else if(choice == 2){


 }else if (choice == 3){

 }else if (choice == 0){
return 0;

 }else{
            std::cout << "Invalid choice!" << std::endl; // default else


 }
        std::string exit;
    std::cout << "Type exit to exit Tool" << std::endl;


    std::cin >> exit;
    if(exit == "exit" ||exit == "Exit" || exit == "exit()"){
        return 0;
        std::cout << "\033[0m";  // Red text color

    }


    
        std::cout << "\033[0m";  // Red text color

}
 void CLI_password_cracker(){
// Choice of Tool:


    int choice;
    std::cout << "Choose a tool:\n";
    std::cout << "1. Brute Force\n";
    std::cout << "2. Dictonary\n";
    std::cout << "3. Rainbow Table\n \n";

    std::cin >> choice;


    // if cases for choice:
 if (choice == 1) {  // Brute force password cracking


        std::cout << "Enter Password to crack: \n" ; //Get hash to crack param
        std::string toCrack;
        std::cin >> toCrack;


        std::cout << "Entered: "<< toCrack << " \n \n Please enter max length: \n   Enter 0 if you want to use default \n "; // get Max Pass Length to crack
        int Max;
        std::cin >> Max;


        std::cout << "Bruteforce started!" << std::endl; // start cracking hash
        brute_Crack(toCrack,Max);

    } else if (choice == 2) {
        

        std::cout << "Enter Password to crack: \n" ; //Get hash to crack param
        std::string toCrack;
        std::cin >> toCrack;


        std::cout << "Entered: "<< toCrack << std::endl;

        std::cout << "\n Dictonary Attack started!" << std::endl;
        //dict_Crack(toCrack);

    } else if (choice == 3 ) {

        
        std::cout << "Enter Password to crack: \n" ; //Get hash to crack param
        std::string toCrack;
        std::cin >> toCrack;


        std::cout << "Entered: "<< toCrack << std::endl;

        std::cout << "\n Rainbow Attack started!" << std::endl;
         // rain_Crack(toCrack);
    }
    
    else{

        
        std::cout << "Invalid choice!" << std::endl; // default else
    }

   

}

void printHome(){
         //   std::cout << "\033[31m";  // Red text color


    std::cout << "\033[38;2;179;0;0m";  // Dark Red Color
            std::cout << R"(
                        //////////ZERODAY\\\\\\\\\\
                                          
                        What would you like to do?

                        1. crack password
                        2. encrypt / decrypt
                        3. scan for vulnerabilities
                        0. exit

                

                )";

}