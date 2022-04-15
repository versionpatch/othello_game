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

        uint64_t GetBestMove(Board b);

};

#endif