#include "display.h"
#include "pieceslogic.h"
#include "player.h"

extern Player player;
extern Pieces pieces;

Display::Display() {
    pieces_map = Pieces::pieces_map;
    pieces_value = Pieces::pieces_value;
}

void Display::init(
    vector<vector<int>> &board,
    vector<int> &p1_collec, 
    vector<int> &p2_collec 
){
    cout << endl;
    
    cout << "==> Black(p2)'s collection: ";
    player.print_collec(p2_collec, pieces_map);
    cout << "==> Black(p2)'s score: ";
    cout << player.score(p2_collec) << endl;
    
    cout << endl;
    for (int i = 0; i < board.size(); i++) {
        cout << 8 - i << "   ";
        for (int j = 0; j < board[i].size(); j++) {
            cout << pieces_map[board[i][j]] << " ";
        }
        cout << endl;
    }
    cout << endl << "    ";
    for (int i = 97; i < 105; i++) {
        cout << char(i) << " ";
    }
    cout << endl;
    cout << endl;

    cout << "==> White(p1)'s collection: ";
    player.print_collec(p1_collec, pieces_map);
    cout << "==> White(p1)'s score: ";
    cout << player.score(p1_collec) << endl;
    cout << endl;
    cout << endl;
}

void Display::update(
    vector<vector<int>> &board,
    vector<int> &p1_collec, 
    vector<int> &p2_collec 
){
    init(board, p1_collec, p2_collec);
}