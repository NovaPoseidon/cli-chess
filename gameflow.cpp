#include "gameflow.h"
#include "display.h"
#include "pieceslogic.h"


extern Display display;
Pieces pieces;

Game::Game(){
    unordered_map <int,char> pieces_map = pieces.pieces_map;
}

void Game::init(
    vector<vector<int>> &board,
    vector<int> &p1_collec, 
    vector<int> &p2_collec 
    
){      
    
    display.init(board,p1_collec,p2_collec);
    
}

vector<vector<int>> Game::update(vector<vector<int>> &board){

}
vector<vector<int>> Game::move_decoder(string move){ //2d4d

    cout<<"====>> "<<move<<endl;

    string spot_start=string(1,move[0])+string(1,move[1]);//2d
    string spot_end=string(1,move[2])+string(1,move[3]);//4d

    unordered_map <char,int> x_positions_map={
        {'a',0},
        {'b',1},
        {'c',2},
        {'d',3},
        {'e',4},
        {'f',5},
        {'g',6},
        {'h',7}
    };

    char x_start_enc = spot_start[0];
    int x_start_dec = 8-(x_start_enc-'0');

    char y_start_enc = spot_start[1];
    int y_start_dec = x_positions_map[y_start_enc];

    char x_end_enc = spot_end[0];
    int x_end_dec = 8-(x_end_enc-'0');

    char y_end_enc = spot_end[1];
    int y_end_dec = x_positions_map[y_end_enc];


    vector<int> start_pos ={ x_start_dec, y_start_dec };
    vector<int> end_pos ={ x_end_dec, y_end_dec };

    vector<vector<int>> positions_arr = { start_pos, end_pos };

    return positions_arr;
}