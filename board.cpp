#include "board.hpp"
#include <cstring>
#include <cassert>





Board::Board()
{
    color = 0;
    board = 0;
    isWhite = true; 
    powIntervals[0] = 1;
    for (int i = 1;i < 8;i++)
    {
        powIntervals[i] = powIntervals[i-1] + (1 << i);
    }
}
bool Board::flip(uint64_t pos)
{
    color ^= pos;
}

uint64_t Board::getFriendlyRight(uint64_t pos)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    uint64_t ray = (powIntervals[7] - powIntervals[col]) << (row * 8);
    uint64_t whitesRay = ray & color & board;
    uint64_t r = 1;
    return (r << __builtin_ctzll(whitesRay));
}
void Board::setWhite(uint64_t p)
{
    color |= p;
    board |= p;
}
