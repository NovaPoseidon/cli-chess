#ifndef PLAYER
#define PLAYER
#include<unordered_map>
#include<vector>
using namespace std;

class Player{
    unordered_map<int,int> pieces_value;
    Player();
public:
    void swap(int &a, int &b);
    void kill_piece(
        int &start_piece, 
        int &end_piece, 
        vector<vector<int>> &board, 
        vector<int> &p1_collec, 
        vector<int> &p2_collec
    );
    int make_move(
        vector<vector<int>> &board, 
        vector<vector<int>> &positions,
        vector<int> &p1_collec, 
        vector<int> &p2_collec,
        bool p1sturn
    );
    int score(vector<int> &collec);
    void print_collec(vector<int> &collec,unordered_map<int,char> map);

};

#endif