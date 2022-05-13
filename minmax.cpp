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

int MinMaxPlayer::EvaluteState(Board b, int maxDepth,bool maxt,bool player,int alpha,int beta,uint64_t* outputMove)
{
    uint64_t legalMoves = 0;
    bool gOver = b.GameOver(&legalMoves);
    if (gOver || maxDepth == 0)
    {
        int totalNum = b.GetNumWhite() + b.GetNumBlack();
        if (totalNum < 24)
            return b.GetEvaluation2(player);
        else
            return b.GetEvaluation1(player,2,2);
    }
    else
    {
        int val = maxt ? -9999 : 9999;
        if (!legalMoves)
        {
            return EvaluteState(b,maxDepth - 1,!maxt,player,alpha,beta);
        }
        while (legalMoves)
        {
            uint64_t nextPos = (uint64_t)1 << __builtin_ctzll(legalMoves);
            legalMoves &= ~nextPos;
            Board bp = Board(b);
            bp.Play(nextPos);
            int v = EvaluteState(bp,maxDepth - 1,!maxt,alpha,beta,player);
            if (maxt)
            {
                if (v > val)
                {
                    val = v;
                    if (outputMove)
                        *outputMove = nextPos;
                }
                if (val >= beta)
                    return val;
                alpha = max(alpha,val);
            }
            else
            {
                if (v < val)
                {
                    val = v;
                    if (outputMove)
                        *outputMove = nextPos;
                }
                if (val <= alpha)
                    return v;
                beta = min(beta,val);
            }
        }
        return val;
    }
}

uint64_t MinMaxPlayer::GetBestMove(Board b)
{
    uint64_t output = 0;
    bool sk = false;
    bool gOver = b.GameOver(nullptr,false,&sk);
    if (sk)
        return 0;
    Board bp(b);
    EvaluteState(bp,depth,true,bp.IsWhite(),-9999,9999,&output);
    return output;
}