#include "board.hpp"
#include <cstring>
#include <cassert>




Board::Board()
{
    color = 0;
    board = 0;
    isWhite = false; 
    powIntervals[0] = 1;
    colIntervals[0] = 1;
    downdiagIntervals[0] = (uint64_t)1 << (7*8);
    updiagIntervals[0] = 1;
    for (int i = 1;i < 8;i++)
    {
        powIntervals[i] = powIntervals[i-1] + (1 << i);
        colIntervals[i] = colIntervals[i-1] + ((uint64_t)1 << (8*i));
        downdiagIntervals[i] = downdiagIntervals[i-1] + ((uint64_t)1 << (8*7 - 7*i));
        updiagIntervals[i] = updiagIntervals[i-1] + ((uint64_t)1 << ((i)*8 + i));
    }
    getFriendlies[0] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyRight(pos,ro,iw);};
    getFriendlies[1] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyLeft(pos,ro,iw);};
    getFriendlies[2] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyUp(pos,ro,iw);};
    getFriendlies[3] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyDown(pos,ro,iw);};
    getFriendlies[4] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyDownDiagD1(pos,ro,iw);};
    getFriendlies[5] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyDownDiagD2(pos,ro,iw);};
    getFriendlies[6] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyUpDiagD1(pos,ro,iw);};
    getFriendlies[7] = [this](uint64_t pos,uint64_t *ro,bool iw) {return getFriendlyUpDiagD2(pos,ro,iw);};
    setWhite((uint64_t)1 << (3 + 3*8));
    setWhite((uint64_t)1 << (4 + 4*8));
    setBlack((uint64_t)1 << (3 + 4*8));
    setBlack((uint64_t)1 << (4 + 3*8));
}
void Board::flip(uint64_t pos)
{
    color ^= pos;
}

uint64_t Board::getFriendlyRight(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 7)
        return 0;
    uint64_t ray = (powIntervals[7] - powIntervals[col]) << (row * 8);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = __builtin_ctzll(Ray);
    uint64_t n = (uint64_t)1 << ind;
    int colneighbour = ind % 8;
    if (rayout)
        *rayout = (powIntervals[colneighbour - 1] - powIntervals[col]) << (row * 8);
    return n;
}
uint64_t Board::getFriendlyLeft(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 0)
        return 0;
    uint64_t ray = (powIntervals[col - 1]) << (row * 8);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = 63 - __builtin_clzll(Ray);
    uint64_t n = (uint64_t)1 << (ind);
    int colneighbour = ind % 8;
    if (rayout)
        *rayout = (powIntervals[col- 1 ] - powIntervals[colneighbour]) << (row * 8);
    return (n);
}
uint64_t Board::getFriendlyUp(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (row == 7)
        return 0;
    uint64_t ray = (colIntervals[7] - colIntervals[row]) << (col);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = __builtin_ctzll(Ray);
    uint64_t n = (uint64_t)1 << ind;
    int rowneighbour = ind / 8;
    if (rayout)
        *rayout = (colIntervals[rowneighbour - 1] - colIntervals[row]) << (col);
    return n;
}
void Board::Pass()
{
    isWhite = !isWhite;
}
uint64_t Board::getFriendlyDown(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (row == 0)
        return 0;
    uint64_t ray = (colIntervals[row - 1]) << (col);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = (63 - __builtin_clzll(Ray));
    uint64_t n = (uint64_t)1 << ind;
    int rowneighbour = ind / 8;
    if (rayout)
        *rayout = (colIntervals[row - 1] - colIntervals[rowneighbour]) << (col);
    return (n);
}
uint64_t Board::getFriendlyUpDiagD1(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 7)
        return 0;
    uint64_t ray = updiagIntervals[7] - updiagIntervals[col];
    if (row > col)
        ray = ray << ((row - col) * 8);
    else
        ray = ray >> ((col - row) * 8);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = __builtin_ctzll(Ray);
    uint64_t n = (uint64_t)1 << ind;
    int colneighbour = ind % 8;
    if (rayout)
    {
        *rayout = (updiagIntervals[colneighbour - 1] - updiagIntervals[col]);
        if (row > col)
            *rayout = *rayout << ((row - col) * 8);
        else
            *rayout = *rayout >> ((col - row) * 8);
    }
    return (n);
}
uint64_t Board::getFriendlyUpDiagD2(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 0)
        return 0;
    uint64_t ray = updiagIntervals[col - 1];
    if (row > col)
        ray = ray << ((row - col) * 8);
    else
        ray = ray >> ((col - row) * 8);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = (63 - __builtin_clzll(Ray));
    uint64_t n = (uint64_t)1 << ind;
    int colneighbour = ind % 8;
    if (rayout)
    {
        *rayout = (updiagIntervals[col - 1] - updiagIntervals[colneighbour]);
        if (row > col)
            *rayout = *rayout << ((row - col) * 8);
        else
            *rayout = *rayout >> ((col - row) * 8);
    }
    return n;
}
uint64_t Board::getFriendlyDownDiagD1(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 7)
        return 0;
    uint64_t ray = downdiagIntervals[7] - downdiagIntervals[col];
    if (7 - col - row >= 0)
        ray = ray >> ((7 - col - row) * 8);
    else
        ray = ray << ((row + col - 7) * 8);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = (63 - __builtin_clzll(Ray));
    uint64_t n = (uint64_t)1 << ind;
    int colneighbour = ind % 8;
    if (rayout)
    {
        *rayout = (downdiagIntervals[colneighbour - 1] - downdiagIntervals[col]);
        if (7 - col - row >= 0)
            *rayout = *rayout >> ((7 - col - row) * 8);
        else
            *rayout = *rayout << ((row + col - 7) * 8);
    }
    return (n);
    
}
uint64_t Board::getFriendlyDownDiagD2(uint64_t pos, uint64_t *rayout,bool white)
{
    int ind = __builtin_ctzll(pos);
    int row = ind / 8;
    int col = ind % 8;
    if (col == 0)
        return 0;
    uint64_t ray = downdiagIntervals[col - 1];
    if (7 - col - row >= 0)
        ray = ray >> ((7 - col - row) * 8);
    else
        ray = ray << ((row + col - 7) * 8);
    uint64_t colorTest = (white ? color : ~color);
    uint64_t Ray = ray & colorTest & board;
    if (Ray == 0)
        return 0;
    ind = __builtin_ctzll(Ray);
    uint64_t n = (uint64_t)1 << ind;
    int colneighbour = ind % 8;
    if (rayout)
    {
        *rayout = (downdiagIntervals[col - 1] - downdiagIntervals[colneighbour]);
        if (7 - col - row >= 0)
            *rayout = *rayout >> ((7 - col - row) * 8);
        else
            *rayout = *rayout << ((row + col - 7) * 8);
    }
    return (n);
}

bool Board::Play(uint64_t pos,bool flip)
{
    if (pos & board)
        return false;
    bool result = false;
    uint64_t ray = 0;
    uint64_t oppColorBoard = (isWhite ? ~color : color) & board;
    for (int i = 0;i < 8;i++)
    {
        uint64_t res = this->getFriendlies[i](pos,&ray,isWhite);
        if (ray != 0)
        {
            if ((oppColorBoard & ray) == ray)
            {
                result |= (res != 0);
                if (flip)
                    (isWhite) ? setWhite(ray) : setBlack(ray);
            }
        }
    }
    if (result && flip)
    {
        isWhite ? setWhite(pos) : setBlack(pos);
        isWhite = !isWhite;
    }
    return result;
}

void Board::setWhite(uint64_t p)
{
    color |= p;
    board |= p;
}
void Board::setBlack(uint64_t p)
{
    color &= ~p;
    board |= p;
}

void Board::Display()
{
    for (int j = 0;j < 8;j++)
    {
        for (int i = 0; i < 8;i++)
        {
            uint64_t pos = (uint64_t)1 << (i + 8*j);
            if (pos & board)
            {
                std::cout << ((color & pos) ? " 白 " : " 黒 ");
            }
            else
            {
                std :: cout << " ー ";
            }
        }
        std::cout << std::endl;
    }
}
int Board::GetEvaluation2(bool w)
{
    //Award more points for border, even more for corners
    uint64_t defactoColor = (w ? color : ~color) & board;
    uint64_t defactoEnemyColor = (w ? ~color : color) & board;
    //total :
    int supportNormal = __builtin_popcountll(defactoColor);
    int enemyNormal = __builtin_popcountll(defactoEnemyColor);
    int supportCorner = __builtin_popcountll(9295429630892703873 & defactoColor);
    int enemyCorner = __builtin_popcountll(9295429630892703873 & defactoEnemyColor);
    int supportBorder = __builtin_popcountll(18411139144890810879 & defactoColor);
    int enemyBorder = __builtin_popcountll(18411139144890810879 & defactoEnemyColor);
    return 1*(supportNormal) + 4*(supportCorner - enemyCorner) + 2*(supportBorder - enemyBorder);
}
int Board::GetEvaluation1(bool w,int w1 = 20,int w2 = 200)
{
    uint64_t defactoColor = w ? color : ~color;
    //award more points for stable disks
    uint64_t one = 1;
    uint64_t untakableWhite = (one << 0) || (one << 7) || (one << 56) || (one << 63);
    uint64_t untakableBlack = (one << 0) || (one << 7) || (one << 56) || (one << 63);
    untakableWhite &= (defactoColor & board);
    untakableBlack &= (~defactoColor & board);
    for (int it = 0;it < 7;it++)
    {
        for (int r = 0; r < 8;r++)
        {
            for (int c = 0;c < 8;c++)
            {
                uint64_t pos = (one << (c + r*8));
                bool untakableUp = (r == 0 || untakableWhite & (pos >> 8));
                bool untakableDown = (r == 7 || untakableWhite & (pos << 8));
                bool untakableLeft = (c == 0 || untakableWhite & (pos >> 1));
                bool untakableRight = (c == 7 || untakableWhite & (pos << 1));
                bool untakableUpLeft = (c == 0 || r == 0 || untakableWhite & (pos >> 9));
                bool untakableUpRight = (c == 7 || r == 0 || untakableWhite & (pos >> 7));
                bool untakableDownLeft = (c == 0 || r == 7 || untakableWhite & (pos << 7));
                bool untakableDownRight = (c == 7 || r == 7 || untakableWhite & (pos << 9));
                bool untakable = (untakableUp) && ((untakableUpLeft && untakableLeft) || (untakableUpRight && untakableRight));
                untakable |= (untakableDown) && ((untakableLeft && untakableDownLeft) || (untakableRight && untakableDownRight));
                if (untakable)
                    untakableWhite |= pos & defactoColor & board;
                
                untakableUp = (r == 0 || untakableBlack & (pos >> 8));
                untakableDown = (r == 7 || untakableBlack & (pos << 8));
                untakableLeft = (c == 0 || untakableBlack & (pos >> 1));
                untakableRight = (c == 7 || untakableBlack & (pos << 1));
                untakableUpLeft = (c == 0 || r == 0 || untakableBlack & (pos >> 9));
                untakableUpRight = (c == 7 || r == 0 || untakableBlack & (pos >> 7));
                untakableDownLeft = (c == 0 || r == 7 || untakableBlack & (pos << 7));
                untakableDownRight = (c == 7 || r == 7 || untakableBlack & (pos << 9));
                untakable = (untakableUp) && ((untakableUpLeft && untakableLeft) || (untakableUpRight && untakableRight));
                untakable |= (untakableDown) && ((untakableLeft && untakableDownLeft) || (untakableRight && untakableDownRight));
                if (untakable)
                    untakableBlack |= pos & ~defactoColor & board;
            }
        }
    }
    return w1 * __builtin_popcountll(untakableWhite) - w2 * __builtin_popcountll(untakableBlack)  + (w ? GetNumWhite() - GetNumBlack() : GetNumBlack() - GetNumWhite());
}
uint64_t Board::GetAllLegalMoves(bool debug)
{
    uint64_t enemyColor = (isWhite ? ~color : color) & board;
    uint64_t neighborHood = (enemyColor << 8) 
                        | (enemyColor >> 8) 
                        | ((enemyColor << 1) & 0xfefefefefefefefe) 
                        | ((enemyColor << 1) & 0xfefefefefefefefe) << 8
                        | ((enemyColor << 1) & 0xfefefefefefefefe) >> 8
                        | ((enemyColor >> 1) & 0x7f7f7f7f7f7f7f7f)
                        | ((enemyColor >> 1) & 0x7f7f7f7f7f7f7f7f) << 8
                        | ((enemyColor >> 1) & 0x7f7f7f7f7f7f7f7f) >> 8;
    neighborHood = neighborHood & ~enemyColor;
    uint64_t output = 0;
    for (int i = 0;i < 64;i++)
    {
        uint64_t pos = (uint64_t)1 << i;
        if (neighborHood & pos)
        {
            bool legal = Play(pos,false);
            if (legal)
            {
                output |= pos;
            }
        }
    }
    if (debug)
    {
        for (int j = 0;j < 8;j++)
        {
            for (int i = 0; i < 8;i++)
            {
                uint64_t pos = (uint64_t)1 << (i + 8*j);
                if (pos & board)
                {
                    std::cout << ((color & pos) ? " 白 " : " 黒 ");
                }
                else
                {
                    if (pos & output)
                        std :: cout << " 合 ";
                    else
                        std :: cout << " ー ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << (isWhite ? "白" : "黒") << std::endl;
    }
    return output;

}

int Board::GetNumBlack()
{
    return __builtin_popcountll ((~color) & board);
}

int Board::GetNumWhite()
{
    return __builtin_popcountll (color & board);
}

bool Board::GameOver(uint64_t* output, bool skip, bool* skippable)
{
    uint64_t t1 = GetAllLegalMoves();
    if (output)
        *output = t1;
    if (t1)
        return false;
    isWhite = !isWhite;
    bool t2 = GetAllLegalMoves();
    if (!skip)
        isWhite = !isWhite;
    if (skippable != nullptr)
        *skippable = true;
    return !t2;
}

bool Board::IsWhite()
{
    return isWhite;
}
