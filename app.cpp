#include "board.hpp"
#include "minmax.hpp"
#include <string>


int main()
{
    char letters[8] = {'a','b','c','d','e','f','g','h'};
    Board b = Board();
    MinMaxPlayer p = MinMaxPlayer(10);
    std::string command;
    bool gameOn = true;
    while(true)
    {
        cin >> command;
        if (command == "genmove")
        {
            cin >> command;
            if (b.IsWhite() && command != "white" || !b.IsWhite() && command != "black")
            {
                std::cout << "? Wrong player" << std::endl;
                continue;
            }
            uint64_t move = p.GetBestMove(b);
            if (move == 0)
                std::cout << "= pass" << std::endl << std::endl;
            else
            {
                int ind = __builtin_ctzll(move);
                int row = ind / 8;
                int col = ind % 8;
                std::cout << "= " << letters[col] << row + 1 << std::endl << std::endl;
            }
        }
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
            if (b.IsWhite() && command != "white" || !b.IsWhite() && command != "black")
            {
                std::cout << "? Wrong player" << std::endl;
                continue;
            }
            cin >> command;
            if (!gameOn)
            {
                std::cout << "? Game is over. Please reset" << std::endl;
                continue;
            }
            if (command == "pass")
            {
                bool sk = false;
                b.GameOver(nullptr,false,&sk);
                if (sk)
                {
                    b.Pass();
                    std::cout << "= " << std::endl << std::endl;
                    continue;
                }
            }
            if (command.length() != 2)
            {
                std::cout << "?Error" << std::endl;
                continue;
            }
            try
            {
                int lg = stoi(command.substr(1,1)) - 1;
                int col = command[0] - 'a';
                if (lg >= 8 || col >= 8 || col < 0)
                {
                    std::cout << "? Error" << std::endl;
                    continue;
                }
                if (!b.Play((uint64_t)1 << (8*lg + col)))
                {
                    std::cout << "? Invalid Move" << std::endl;
                    continue;
                }
                std::cout << "= " << std::endl;
                if (b.GameOver(nullptr,false,nullptr))
                {
                    gameOn = false;
                }
                
                
            }
            catch(...)
            {
                std::cout << "?Error" << std::endl;
                continue;
            }
        }
    }    
}   