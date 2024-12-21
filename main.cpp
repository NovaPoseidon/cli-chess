#include<iostream>
#include "gameflow.h"
#include "display.h"
#include "player.h"
#include "pieceslogic.h"
#include "menu.h"
#include "m2m.h"
using namespace std;

Game game;
Player player;
Display display;
Lan lan;
Menu menu;

int main(){
    bool start = true;
    string move, piece;
    int turns=0;

    vector<vector<int>> board = {
        {-1,-2,-3,-4,-5,-3,-2,-1},
        {-6,-6,-6,-6,-6,-6,-6,-6},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {6,6,6,6,6,6,6,6},
        {1,2,3,4,5,3,2,1},
    };
    
    vector<int> p1_collec={}; 
    vector<int> p2_collec={};
    

    system("cls");
    menu.selector();
    system("cls");
    

    if(menu.game_mode==1){
        cout<<"Plying Pass n Play mode"<<endl;
        game.init(board,p1_collec,p2_collec);
        //pass n play
        menu.passnplay(
            board,
            p1_collec,
            p2_collec,
            start,
            turns,
            move
        );
    }else if(menu.game_mode==2){
        //lan multiplayer
        cout<<"Plying LAN Multiplayer mode"<<endl;
        game.init(board,p1_collec,p2_collec);
        menu.lanmultiplayer(
            board,
            p1_collec,
            p2_collec,
            start,
            turns,
            move
        );
    }else if(menu.game_mode==3){
        //ai opponent
        cout<<"Plying aginst AI Opponent"<<endl;
        game.init(board,p1_collec,p2_collec);
        menu.aiopponent(
            board,
            p1_collec,
            p2_collec,
            start,
            turns,
            move
        );
    }
    system("pause");
    return 0;
}