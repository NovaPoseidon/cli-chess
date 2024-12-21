#ifndef MENU
#define MENU
#include "display.h"
#include "player.h"

class Menu{
public:
    Menu();

    int game_mode;

    int selector();
    void passnplay(
        vector<vector<int>> board,
        vector<int> p1_collec,
        vector<int> p2_collec,
        bool start,
        int turns,
        string move
    );
    void lanmultiplayer(
        vector<vector<int>> board,
        vector<int> p1_collec,
        vector<int> p2_collec,
        bool start,
        int turns,
        string move
    );
    void aiopponent(
        vector<vector<int>> board,
        vector<int> p1_collec,
        vector<int> p2_collec,
        bool start,
        int turns,
        string move
    );
};

#endif