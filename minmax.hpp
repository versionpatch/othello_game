#ifndef MINMAX_HPP
#define MINMAX_HPP

#include <board.hpp>

class MinMaxPlayer
{
    private:
        Board* gameInstance;
    public:
        MinMaxPlayer(Board* b)
        {
            gameInstance = b;
        }
};

#endif