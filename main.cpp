#include <iostream>
#include <string>

// Function prototypes for each tool
void CLI_password_cracker();
void CLI_sql_injection_tester();
void CLI_file_explorer();
void CLI_log_monitor();

void printHome();

int main() {
    // Choice of Branch:
    printHome();

    int choice;
    std::cin >> choice;

    // if cases for choice:
    if (choice == 1) {  // Password Cracking
        CLI_password_cracker();
    } else if (choice == 2) {  // SQL Injection Tester
        CLI_sql_injection_tester();
    } else if (choice == 3) {  // File Explorer
        CLI_file_explorer();
    } else if (choice == 4) {  // Log Monitoring
        CLI_log_monitor();
    } else if (choice == 0) {
        return 0;
    } else {
        std::cout << "Invalid choice!" << std::endl; // default else
    }

    std::string exit;
    std::cout << "Type exit to exit Tool" << std::endl;
    std::cin >> exit;
    if (exit == "exit" || exit == "Exit") {
        return 0;
    }

    return 0;
}

void CLI_password_cracker() {
    // Choice of Tool:
    int choice;
    std::cout << "Choose a password cracking tool:\n";
    std::cout << "1. Brute Force\n";
    std::cout << "2. Dictionary Attack\n";
    std::cout << "3. Rainbow Table Attack\n";
    std::cin >> choice;

    std::string toCrack;
    std::cout << "Enter Password to crack: \n"; // Get hash to crack param
    std::cin >> toCrack;
    std::cout << "Entered: " << toCrack << std::endl;

    if (choice == 1) {
        std::cout << "Please enter max length (0 for default): \n";
        int Max;
        std::cin >> Max;
        std::cout << "Bruteforce started!" << std::endl;
        // Call the brute force function here
        // brute_Crack(toCrack, Max);
    } else if (choice == 2) {
        std::cout << "Dictionary Attack started!" << std::endl;
        // Call the dictionary attack function here
        // dict_Crack(toCrack);
    } else if (choice == 3) {
        std::cout << "Rainbow Table Attack started!" << std::endl;
        // Call the rainbow table attack function here
        // rain_Crack(toCrack);
    } else {
        std::cout << "Invalid choice!" << std::endl; // default else
    }
}

void CLI_sql_injection_tester() {
    std::string url;
    std::cout << "Enter the URL to test for SQL injection (e.g., http://example.com/vuln): ";
    std::cin >> url;
    // Call the SQL injection tester function here
    // testSQLInjection(url);
}

void CLI_file_explorer() {
    std::string path;
    std::cout << "Enter the directory path to explore: ";
    std::cin >> path;
    // Call the file explorer function here
    // exploreDirectory(path);
}

void CLI_log_monitor() {
    std::string logFile;
    std::cout << "Enter the log file path to monitor: ";
    std::cin >> logFile;
    // Call the log monitoring function here
    // monitorLogs(logFile);
}

void printHome() {
    std::cout << "\033[38;2;179;0;0m";  // Dark Red Color
    std::cout << R"(
                    //////////ZERODAY\\\\\\\\\\
                                          
                    What would you like to do?

                    1. Crack Password
                    2. Test SQL Injection
                    3. Explore Files
                    4. Monitor Logs
                    0. Exit
                )";
}
