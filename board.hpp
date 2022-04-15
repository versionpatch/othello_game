#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <cstring>
#include <functional>

using namespace std;




class Board
{
    private:
        uint64_t powIntervals[8];
        uint64_t colIntervals[8];
        uint64_t updiagIntervals[8];
        uint64_t downdiagIntervals[8];

        uint64_t color;
        uint64_t board;
        void flip(uint64_t pos);
        bool isWhite;

        uint64_t getFriendlyRight(uint64_t pos,uint64_t *ray = nullptr, bool white = true);
        uint64_t getFriendlyLeft(uint64_t pos,uint64_t *ray = nullptr, bool white = true);
        uint64_t getFriendlyUp(uint64_t pos,uint64_t *ray = nullptr, bool white = true);
        uint64_t getFriendlyDown(uint64_t pos,uint64_t *ray = nullptr, bool white = true);
        uint64_t getFriendlyUpDiagD1(uint64_t pos, uint64_t *ray = nullptr, bool white = true);
        uint64_t getFriendlyUpDiagD2(uint64_t pos, uint64_t *ray = nullptr, bool white = true);
        uint64_t getFriendlyDownDiagD1(uint64_t pos, uint64_t *ray = nullptr, bool white = true);
        uint64_t getFriendlyDownDiagD2(uint64_t pos, uint64_t *ray = nullptr, bool white = true);
        std::function<uint64_t(uint64_t,uint64_t*,bool)> getFriendlies[8];
        void setWhite(uint64_t pos);
        void setBlack(uint64_t pos);

    public:
        Board();
        static void Initialize();
        bool Play(uint64_t pos,bool flip = true);
        void Display();
        int GetNumBlack();
        int GetNumWhite();
        bool GameOver();
        bool IsWhite();
        uint64_t GetAllLegalMoves(bool debug = false);
        



};

#endif