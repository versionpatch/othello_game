#include "board.hpp"




int main()
{
    Board b = Board();
    b.GetAllLegalMoves(true);
    /*
    while(true)
    {
        int col,row;
        cin >> col >> row;
        uint64_t pos = (uint64_t)1 << (col + 8*row);
        b.Play(pos);
        b.Display();
    }
    */
}