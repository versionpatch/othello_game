#ifndef BOARD_HPP


#define BOARD_HPP

#include <iostream>
#include <cstring>
using namespace std;


class Board
{
    private:
        uint64_t powIntervals[8];
        uint64_t color;
        uint64_t board;
        bool flip(uint64_t pos);
        bool isWhite; 
    public:
        Board();
        bool Play();
        void setWhite(uint64_t pos);
        uint64_t getFriendlyRight(uint64_t pos);
        

};

#endif