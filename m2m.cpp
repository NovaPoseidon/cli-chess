//LAN Multiplayer Mode

#include "m2m.h"
#include "player.h"
#include "display.h"
#include "gameflow.h"
#include <iostream>
#include <winsock2.h>
#include <limits>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

#define PORT 9999
#define MAX_BUFFER_SIZE 1024

using namespace std;

extern Game game;
extern Player player;
extern Display display;

Lan::Lan(){
    
}

string serializeBoard(const vector<vector<int>>& board) {
    string serialized;
    for (const auto& row : board) {
        for (int piece : row) {
            serialized += to_string(piece) + ",";
        }
    }
    return serialized;
}

vector<vector<int>> deserializeBoard(const string& data) {
    vector<vector<int>> board(8, vector<int>(8));
    size_t pos = 0, start = 0;
    int row = 0, col = 0;
    while ((pos = data.find(',', start)) != string::npos) {
        board[row][col] = stoi(data.substr(start, pos - start));
        start = pos + 1;
        if (++col == 8) {
            col = 0;
            ++row;
        }
    }
    return board;
}

void Lan::startServer(SOCKET &serverSocket, sockaddr_in &serverAddr, sockaddr_in &clientAddr,vector<vector<int>> &board, int &turns, string &move,vector<int> &p1_collec,vector<int> &p2_collec) {
    listen(serverSocket, 1);
    std::cout << "waiting for opponent to join..." << std::endl;
    
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);

    if (clientSocket != INVALID_SOCKET) {
        std::cout << "opponent has joined the game!" << std::endl;

        char buffer[MAX_BUFFER_SIZE];
        string server_message;
        int bytesReceived;
        
        while (true) {
            memset(buffer, 0, MAX_BUFFER_SIZE);
            
            // Receive message from client
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::cout << "opponent's move: " << buffer << std::endl;
                board=deserializeBoard(buffer);
                display.update(board,p1_collec,p2_collec);
                
                // Get server's response
                std::cout << "Your Move: ";
                getline(std::cin, server_message);
                move = server_message;
                vector<vector<int>> positions = game.move_decoder(move);
                int move_made = player.make_move(board,positions,p1_collec,p2_collec,true);
                display.update(board,p1_collec,p2_collec);
                // Send response to client
                server_message = serializeBoard(board);
                send(clientSocket, server_message.c_str(), server_message.length(), 0);
            } else {
                std::cout << "opponent disconnected." << std::endl;
                break;
            }
        }
        closesocket(clientSocket);
    }
}

void Lan::startClient(SOCKET &clientSocket, sockaddr_in &serverAddr, vector<vector<int>> &board, int &turns, string &move,vector<int> &p1_collec,vector<int> &p2_collec) {
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed!" << std::endl;
        return;
    }

    std::cout << "Connected to opponent!" << std::endl;

    char buffer[MAX_BUFFER_SIZE];
    string message;
    
    // Clear the input buffer once at the start
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        // Clear buffers
        memset(buffer, 0, MAX_BUFFER_SIZE);
        // memset(message, 0, MAX_BUFFER_SIZE);
        
        // Get message from user
        std::cout << "Your move: ";
        getline(std::cin, message);
        move = message;
        vector<vector<int>> positions = game.move_decoder(move);
        int move_made = player.make_move(board,positions,p1_collec,p2_collec,false);
        display.update(board,p1_collec,p2_collec);
        
        if (message.length() == 0) {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        // Send message to server
        message = serializeBoard(board);
        send(clientSocket, message.c_str(), message.length(), 0);
        
        // Receive server's response
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "opponent's move: " << buffer << std::endl;
            board=deserializeBoard(buffer);
            display.update(board,p1_collec,p2_collec);
        } else {
            std::cout << "opponent disconnected." << std::endl;
            break;
        }
    }
}

int Lan::initiate(vector<vector<int>> &board, int &turns, string &move,vector<int> &p1_collec,vector<int> &p2_collec) {
    WSADATA wsaData;
    SOCKET socketHandle;
    sockaddr_in addr;
    char buffer[MAX_BUFFER_SIZE];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed!" << std::endl;
        return -1;
    }
    socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketHandle == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    std::cout << "Choose your role: 1 for Hosting a Game, 2 for Joining a Game: ";
    int role;
    std::cin >> role;
    std::cin.ignore();

    if (role == 1) {
        // Server Role
        if (bind(socketHandle, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed!" << std::endl;
            return -1;
        }
        std::cout << "Creating a Game Space for you two..." << std::endl;
        startServer(socketHandle, addr, addr,board, turns, move,p1_collec,p2_collec);
    } else if (role == 2) {
        // Client Role
        std::cout << "Enter server IP address: ";
        std::string serverIp;
        std::cin >> serverIp;
        addr.sin_addr.s_addr = inet_addr(serverIp.c_str()); 

        startClient(socketHandle, addr, board, turns, move,p1_collec,p2_collec);
    } else {
        std::cerr << "Invalid choice!" << std::endl;
    }

    closesocket(socketHandle);
    WSACleanup();
    return 0;
}