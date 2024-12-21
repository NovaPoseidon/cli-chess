#include "menu.h"
#include "display.h"
#include "gameflow.h"
#include<iostream>
using namespace std;

extern Game game;
extern Player player;
extern Display display;

Menu::Menu(){
    int game_mode;
}

int Menu::selector(){
    cout<<"Select your mode of playing: "<<endl;
    cout<<"     1 for Pass n Play (Offline 1 on 1)\n     2 for LAN multiplayer\n     3 for AI opponent(Offline)\n\n---> ";
    cin>>game_mode;
    return game_mode;
}

void Menu::passnplay(
    vector<vector<int>> board,
    vector<int> p1_collec,
    vector<int> p2_collec,
    bool start,
    int turns,
    string move
){
    while(start){
        
        bool p1sturn = turns%2==0;
        cout<<"Total moves: "<<turns<<endl;
        if (p1sturn) {
            cout << "Player 1's turn: ";
            cin >> move;
        } else {
            cout << "Player 2's turn: ";
            
            cin>>move;
        }

        vector<vector<int>> positions = game.move_decoder(move);

        system("cls");

        int move_made = player.make_move(board,positions,p1_collec,p2_collec,p1sturn);
        if(move_made==0){
            turns--;
        }
        
        display.update(board,p1_collec,p2_collec);

        turns++;
        
    }
}
void Menu::lanmultiplayer(
    vector<vector<int>> board,
    vector<int> p1_collec,
    vector<int> p2_collec,
    bool start,
    int turns,
    string move
){
    while(start){
        
        bool p1sturn = turns%2==0;
        cout<<"Total moves: "<<turns<<endl;
        if (p1sturn) {
            cout << "Player 1's turn: ";
            cin >> move;
        } else {
            cout << "Player 2's turn: ";
            
            cin>>move;
        }

        vector<vector<int>> positions = game.move_decoder(move);

        system("cls");

        int move_made = player.make_move(board,positions,p1_collec,p2_collec,p1sturn);
        if(move_made==0){
            turns--;
        }
        
        display.update(board,p1_collec,p2_collec);

        turns++;
        
    }
}
void Menu::aiopponent(
    vector<vector<int>> board,
    vector<int> p1_collec,
    vector<int> p2_collec,
    bool start,
    int turns,
    string move
){
    while(start){
        
        bool p1sturn = turns%2==0;
        cout<<"Total moves: "<<turns<<endl;
        if (p1sturn) {
            cout << "Player 1's turn: ";
            cin >> move;
        } else {
            cout << "Player 2's turn: ";
            
            cin>>move;
        }

        vector<vector<int>> positions = game.move_decoder(move);

        system("cls");

        int move_made = player.make_move(board,positions,p1_collec,p2_collec,p1sturn);
        if(move_made==0){
            turns--;
        }
        
        display.update(board,p1_collec,p2_collec);

        turns++;
        
    }
}