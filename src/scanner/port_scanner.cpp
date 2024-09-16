#include <iostream>
#include <winsock2.h>    // For WinSock2 API
#include <ws2tcpip.h>    // For InetPton() function

#pragma comment(lib, "ws2_32.lib")  // Link with WinSock2 library

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600  // Windows Vista or later
#endif

bool isPortOpen(const char *ip, int port, int timeout) {
    // Initialize WinSock2
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed!" << std::endl;
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        WSACleanup();
        return false;
    }

    // Set socket timeout option
    DWORD timeoutMs = timeout * 1000;  // Convert seconds to milliseconds
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeoutMs, sizeof(timeoutMs));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeoutMs, sizeof(timeoutMs));

    sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    // Use inet_addr for compatibility instead of InetPtonA
    target.sin_addr.s_addr = inet_addr(ip);
    if (target.sin_addr.s_addr == INADDR_NONE) {
        std::cerr << "Invalid IP address!" << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    int connection = connect(sock, (struct sockaddr*)&target, sizeof(target));

    closesocket(sock);  // Close the socket
    WSACleanup();       // Cleanup WinSock2

    if (connection == 0) {
        return true;  // Port is open
    } else {
        return false; // Port is closed
    }
}

int Portmain() {
    const char *target_ip = "192.168.1.1";  // Replace with your target IP
    int start_port = 1, end_port = 1024;
    int timeout = 5; // Timeout of 5 seconds for each port check

    for (int port = start_port; port <= end_port; ++port) {
        if (isPortOpen(target_ip, port, timeout)) {
            std::cout << "Port " << port << " is open." << std::endl;
        } else {
            std::cout << "Port " << port << " is closed." << std::endl;
        }
    }

    return 0;
}
