#include <iostream>
#include <winsock2.h>    // For WinSock2 API
#include <ws2tcpip.h>    // For inet_pton() function

#pragma comment(lib, "ws2_32.lib")  // Link with WinSock2 library

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
    inet_pton(AF_INET, ip, &target.sin_addr);

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
