#ifndef MINMAX_HPP
#define MINMAX_HPP

#include "board.hpp"

class MinMaxPlayer
{
    private:
        int depth = 5;
    public:
        MinMaxPlayer(int depth)
        {
           this->depth = depth;
        }

        uint64_t GetBestMoveGreedy(Board b);
        int EvaluteState(Board b, int maxDepth,bool max,bool player,int alpha,int beta,uint64_t* outputMove = nullptr );
        uint64_t GetBestMove(Board b);
};

#endif