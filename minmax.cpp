#include "minmax.hpp"

uint64_t MinMaxPlayer::GetBestMove(Board b)
{
    bool player = b.IsWhite();
    uint64_t moves = b.GetAllLegalMoves();
    uint64_t currentBest = 0;
    int currentScore = -5981;
    while (moves)
    {
        uint64_t nextPos = (uint64_t)1 << __builtin_ctzll(moves);
        moves &= ~nextPos;
        Board newB(b);
        newB.Play(nextPos);
        int sc = newB.GetNumWhite() - newB.GetNumBlack();
        if (!player)
            sc = -sc;
        if (sc >= currentScore)
        {
            currentScore = sc;
            currentBest = nextPos;
        }
    }
    return currentBest;
}