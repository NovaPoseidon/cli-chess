#ifndef PIECESLOGIC
#define PIECESLOGIC
#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

class Pieces{
public:


    unordered_map <int,char> pieces_map;
    unordered_map <int,int> pieces_value;
    Pieces();

    bool validate_move(
        int &start_piece, 
        int &end_piece,
        vector<vector<int>> &board, 
        vector<vector<int>> &positions,
        bool p1sturn
    );
};


#endif