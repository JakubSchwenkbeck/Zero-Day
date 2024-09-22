#include <iostream>
#include <filesystem>

void exploreDirectory(const std::string& path) {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::cout << "File: " << entry.path() << " | Size: " << entry.file_size() << " bytes" << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
}

int main() {
    std::string path;
    std::cout << "Enter the directory path to explore: ";
    std::cin >> path;

    exploreDirectory(path);
    return 0;
}
