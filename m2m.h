#ifndef LAN
#define LAN

#include <iostream>
#include <winsock2.h>
#include <limits>
#include <vector>  
#include <string>
#define PORT 9999
#define MAX_BUFFER_SIZE 1024
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class Lan{
public:
    Lan();
    void startServer(
        SOCKET &serverSocket, 
        sockaddr_in &serverAddr, 
        sockaddr_in &clientAddr,
        vector<vector<int>> &board, 
        int &turns, 
        string &move,
        vector<int> &p1_collec,
        vector<int> &p2_collec
    );
    void startClient(
        SOCKET &clientSocket, 
        sockaddr_in &serverAddr,
        vector<vector<int>> &board, 
        int &turns, 
        string &move,
        vector<int> &p1_collec,
        vector<int> &p2_collec
    );
    int initiate(
        vector<vector<int>> &board, 
        int &turns, 
        string &move,
        vector<int> &p1_collec,
        vector<int> &p2_collec
    );

};

#endif