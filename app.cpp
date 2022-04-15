#include "board.hpp"
#include "minmax.hpp"



int main()
{
    Board b = Board();
    MinMaxPlayer p = MinMaxPlayer(5);
    b.GetAllLegalMoves(true);

    while(!b.GameOver())
    {
        b.Play(p.GetBestMove(b));
    }
    b.Display();
}