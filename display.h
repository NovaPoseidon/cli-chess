#ifndef DISPLAY
#define DISPLAY

#include<unordered_map>
#include<vector>
using namespace std;

class Display{
    
    unordered_map<int,char> pieces_map;
    unordered_map<int,int> pieces_value;

    Display();
public:

    void init(
        vector<vector<int>> &board,
        vector<int> &p1_collec, 
        vector<int> &p2_collec 
    );

    void update(
        vector<vector<int>> &board,
        vector<int> &p1_collec, 
        vector<int> &p2_collec 
    );
};

#endif