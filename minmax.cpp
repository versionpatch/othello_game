#include "minmax.hpp"

uint64_t MinMaxPlayer::GetBestMoveGreedy(Board b)
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

int MinMaxPlayer::EvaluteState(Board b, int maxDepth,bool maxt,bool player,uint64_t* outputMove)
{
    uint64_t legalMoves = 0;
    if (b.GameOver(&legalMoves) || maxDepth == 0)
    {
        int sc = (b.GetNumWhite() - b.GetNumBlack()) * (player ? 1 : -1);
        return sc;
    }
    else
    {
        int val = maxt ? -9999 : 9999;
        if (!legalMoves)
        {
            return EvaluteState(b,maxDepth - 1,!maxt,player);
        }
        while (legalMoves)
        {
            uint64_t nextPos = (uint64_t)1 << __builtin_ctzll(legalMoves);
            legalMoves &= ~nextPos;
            Board bp = Board(b);
            bp.Play(nextPos);
            int v = EvaluteState(bp,maxDepth - 1,!maxt,player);
            if (maxt)
            {
                if (v > val)
                {
                    val = v;
                    if (outputMove)
                        *outputMove = nextPos;
                }
            }
            else
            {
                if (v < val)
                {
                    val = v;
                    if (outputMove)
                        *outputMove = nextPos;
                }
            }
        }
        return val;
    }
}

uint64_t MinMaxPlayer::GetBestMove(Board b)
{
    uint64_t output = 0;
    EvaluteState(b,depth,true,b.IsWhite(),&output);
    return output;
}