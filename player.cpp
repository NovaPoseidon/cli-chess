#include "player.h"
#include "pieceslogic.h"

extern Pieces pieces;

Player::Player(){
    unordered_map<int,int> pieces_value = pieces.pieces_value;
}

void Player::swap(int &a, int &b){
    int temp = a;
    a=b;
    b=temp;
};

void Player::kill_piece(
        int &start_piece, 
        int &end_piece, 
        vector<vector<int>> &board, 
        vector<int> &p1_collec, 
        vector<int> &p2_collec
    ){
    
    if(start_piece>0 && end_piece<0){
        
        //white p1 kills
        p1_collec.push_back(end_piece);
        end_piece=start_piece;
        start_piece=0;

    }else if(start_piece<0 && end_piece>0){

        //black p2 kills
        p2_collec.push_back(end_piece);
        end_piece=start_piece;
        start_piece=0;

    }else{
        cout<<"*****************"<<endl;
    }
}

int Player::make_move(
        vector<vector<int>> &board, 
        vector<vector<int>> &positions,
        vector<int> &p1_collec, 
        vector<int> &p2_collec,
        bool p1sturn
    ){
    int x1=positions[0][0], x2=positions[1][0];
    int y1=positions[0][1], y2=positions[1][1];

    int start_piece = board[x1][y1];
    int end_piece = board[x2][y2];

    bool allowed = pieces.validate_move(start_piece, end_piece, board, positions,p1sturn);

    if(allowed){

        if(end_piece==0){
            swap(board[x1][y1],board[x2][y2]);
            return 1;
        }

        kill_piece(board[x1][y1],board[x2][y2],board,p1_collec,p2_collec);
        return 1;
    }else return 0;

    cout<<"~~~~~~~~~~~~~~~~~~~~~"<<endl;
}

int Player::score(vector<int> &collec){
    int sum=0;
    for(int piece:collec){
        sum+=pieces_value[piece];
    }
    return sum;
}

void Player::print_collec(vector<int> &collec,unordered_map<int,char> map){
    for(int piece:collec){
        cout<<map[piece]<<" ";
    }
    cout<<endl;
}