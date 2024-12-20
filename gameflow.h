#ifndef GAMEFLOW
#define GAMEFLOW

#include<unordered_map>
#include<vector>
using namespace std;

class Game{
    Game();
    unordered_map <int,char> pieces_map;
    void init(
        vector<vector<int>> &board,
        vector<int> &p1_collec, 
        vector<int> &p2_collec 
        
    );
    vector<vector<int>> update(vector<vector<int>> &board);
    vector<vector<int>> move_decoder(string move);
};

#endif