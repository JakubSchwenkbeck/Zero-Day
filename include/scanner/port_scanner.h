#ifndef PORT_SCANNER_H
#define PORT_SCANNER_H

#include <winsock2.h>  // For WinSock2 API
#include <ws2tcpip.h>  // For inet_addr() function
#include <iostream>

// Ensure compatibility with Windows Vista or later
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

// Function to initialize Winsock
bool initializeWinsock();

// Function to check if a specific port on a given IP address is open
bool isPortOpen(const char* ip, int port, int timeout);

// Function to clean up Winsock
void cleanupWinsock();

int Portmain(); 

#endif // PORT_SCANNER_H
