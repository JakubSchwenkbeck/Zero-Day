#include <iostream>
#include <fstream>
#include <string>

void monitorLogs(const std::string& logFile) {
    std::ifstream file(logFile);
    if (!file.is_open()) {
        std::cerr << "Could not open log file: " << logFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("ERROR") != std::string::npos || line.find("WARNING") != std::string::npos) {
            std::cout << "Suspicious entry: " << line << std::endl;
        }
    }
    file.close();
}

int main() {
    std::string logFile;
    std::cout << "Enter the log file path to monitor: ";
    std::cin >> logFile;

    monitorLogs(logFile);
    return 0;
}
