#include "board.hpp"
#include <cstring>
#include <cassert>





Board::Board()
{
    color = 0;
    board = 0;
    isWhite = true; 
    powIntervals[0] = 1;
    colIntervals[0] = 1;
    for (int i = 1;i < 8;i++)
    {
        powIntervals[i] = powIntervals[i-1] + (1 << i);
        colIntervals[i] = colIntervals[i-1] + ((uint64_t)1 << (8*i));

    }
}
void Board::flip(uint64_t pos)
{
    color ^= pos;
}

uint64_t Board::getFriendlyRight(uint64_t pos)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 7)
        return 0;
    uint64_t ray = (powIntervals[7] - powIntervals[col]) << (row * 8);
    uint64_t colorTest = (color & pos ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    uint64_t r = 1;
    return (r << __builtin_ctzll(Ray));
}
uint64_t Board::getFriendlyLeft(uint64_t pos)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 0)
        return 0;
    uint64_t ray = (powIntervals[col - 1]) << (row * 8);
    uint64_t colorTest = (color & pos ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    uint64_t r = 1;
    return (r << (63 - __builtin_clzll(Ray)));
}
uint64_t Board::getFriendlyUp(uint64_t pos)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (row == 7)
        return 0;
    uint64_t ray = (colIntervals[7] - colIntervals[row]) << (col);
    uint64_t colorTest = (color & pos ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    uint64_t r = 1;
    return (r << __builtin_ctzll(Ray));
}
uint64_t Board::getFriendlyDown(uint64_t pos)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (row == 0)
        return 0;
    uint64_t ray = (colIntervals[row - 1]) << (col);
    uint64_t colorTest = (color & pos ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    uint64_t r = 1;
    return (r << (63 - __builtin_clzll(Ray)));
}
void Board::setWhite(uint64_t p)
{
    color |= p;
    board |= p;
}
