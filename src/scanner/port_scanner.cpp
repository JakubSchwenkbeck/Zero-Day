#include <iostream>
#include <winsock2.h>    // For WinSock2 API
#include <ws2tcpip.h>    // For InetPton() function

#pragma comment(lib, "ws2_32.lib")  // Link with WinSock2 library

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600  // Windows Vista or later required for InetPton
#endif

bool isPortOpen(const char *ip, int port) {
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

    sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
     // Convert char* to wide string (wchar_t)
    wchar_t w_ip[100];
    MultiByteToWideChar(CP_ACP, 0, ip, -1, w_ip, 100);

    // Use InetPton with wide string
    if (InetPtonW(AF_INET, w_ip, &target.sin_addr) <= 0) {
        std::cerr << "Invalid IP address!" << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    int connection = connect(sock, (struct sockaddr *)&target, sizeof(target));

    closesocket(sock);  // Close the socket
    WSACleanup();       // Cleanup WinSock2

    if (connection == 0) {
        return true;  // Port is open
    } else {
        return false; // Port is closed
    }
}

int main() {
    const char *target_ip = "192.168.1.1";  // Replace with your target IP
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
