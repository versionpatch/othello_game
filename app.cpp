#include "board.hpp"
#include "minmax.hpp"
#include <string>


int main()
{

    Board b = Board();
    MinMaxPlayer p = MinMaxPlayer(5);
    std::string command;
    bool gameOn = true;
    while(true)
    {
        cin >> command;
        if (command == "display")
            b.Display();
        else if (command == "player")
            b.IsWhite() ? std::cout << "White is playing" << std::endl : std::cout << "Black is playing" << std::endl;
        else if (command == "legal")
            b.GetAllLegalMoves(true);
        else if (command == "random")
        {
            if (!gameOn)
            {
                std::cout << "Game is over, please reset" << std::endl;
            }
            uint64_t moves = b.GetAllLegalMoves(false);
            int numMoves = __builtin_popcountll(moves);
            int random = rand() % (numMoves);
            int ct = 0;
            
            while(ct < random)
            {
                uint64_t nextPos = (uint64_t)1 << __builtin_ctzll(moves);
                moves &= ~nextPos;
                ct++;
            }
            
            uint64_t nextPos = (uint64_t)1 << __builtin_ctzll(moves);
            b.Play(nextPos);
            
            if (b.GameOver())
            {
                std::cout << "Game over" << std::endl;
                gameOn = false;
            }
        }
        else if (command == "minmax")
        {
            if (!gameOn)
            {
                std::cout << "Game is over, please reset" << std::endl;
            }
            b.Play(p.GetBestMove(b));
            if (b.GameOver())
            {
                std::cout << "Game over" << std::endl;
                gameOn = false;
            }
        }
        else if (command == "reset")
        {
            b = Board();
            gameOn = true;
        }
        else if (command == "exit")
        {
            break;
        }
        else if (command == "play")
        {
            cin >> command;
            if (!gameOn)
            {
                std::cout << "Game is over. Please reset" << std::endl;
                continue;
            }
            if (command.length() != 2)
            {
                std::cout << "Error" << std::endl;
                continue;
            }
            try
            {
                int x = stoi(command);
                int lg = x / 10;
                int col = x % 10;
                if (lg >= 8 || col >= 8 )
                {
                    std::cout << "Error" << std::endl;
                    continue;
                }
                if (!b.Play((uint64_t)1 << (8*lg + col)))
                {
                    std::cout << "Invalid Move" << std::endl;
                    continue;
                }
                if (b.GameOver())
                {
                    std::cout << "Game over" << std::endl;
                    gameOn = false;
                }
                
            }
            catch(...)
            {
                std::cout << "Error" << std::endl;
                continue;
            }
        }
    }    
}   