#include <board.hpp>
#include <cstring>
#include <cassert>

Board::Board()
{
    color = 0;
    board = 0;
    isWhite = true; 
}
bool Board::flip(uint64_t pos)
{
    color ^= pos;
}
//-1 : no piece at (i,j)
//-2 : no friendlies found
int Board::getFriendlyRight(uint64_t pos)
{
    
}