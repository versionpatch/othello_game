#include "board.hpp"

int main()
{
    Board b = Board();
    std::cout << b.getFriendlyDown((uint64_t)1 << 16) << std::endl;
    return 0;
}