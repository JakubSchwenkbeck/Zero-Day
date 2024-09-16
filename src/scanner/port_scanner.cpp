#include <iostream>
#include <winsock2.h>    // For WinSock2 API
#include <ws2tcpip.h>    // For InetPton() function
#include <chrono>        // For timeouts

#pragma comment(lib, "ws2_32.lib")  // Link with WinSock2 library

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600  // Windows Vista or later required for InetPton
#endif

// Function to check if a port is open
bool isPortOpen(const char* ip, int port, int timeout_ms = 2000) {
    // Initialize WinSock2
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed!" << std::endl;
        return false;
    }

    // Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        WSACleanup();
        return false;
    }

    // Set socket timeout
    timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;  // microseconds
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));

    // Set up target address
    sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    // Convert IP address from string to binary form
    if (InetPtonA(AF_INET, ip, &target.sin_addr) <= 0) {
        std::cerr << "Invalid IP address: " << ip << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    // Attempt to connect to the port
    int connection = connect(sock, (struct sockaddr*)&target, sizeof(target));

    // Close socket and cleanup WinSock
    closesocket(sock);
    WSACleanup();

    return (connection == 0);  // Returns true if connection successful (port open)
}

int main() {
    const char* target_ip = "192.168.1.1";  // Replace with your target IP
    int start_port = 1, end_port = 1024;

    for (int port = start_port; port <= end_port; ++port) {
        if (isPortOpen(target_ip, port)) {
            std::cout << "Port " << port << " is open." << std::endl;
        } else {
            std::cout << "Port " << port << " is closed." << std::endl;
        }
    }

    return 0;
}
