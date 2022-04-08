#include "board.hpp"

int main()
{
    Board b = Board();
    b.setWhite(2);
    b.setWhite(8);
    b.setWhite(16);
    std::cout << b.getFriendlyRight(8) << std::endl;
    return 0;
}