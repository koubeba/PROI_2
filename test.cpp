#include <iostream>
#include <stdlib.h>
#include "ship.h"
#include "board.h"

using namespace std;
using namespace Ships;
using namespace Boards;

int main()
{
    //n. of columns, then n. of rows
    Board b= Board(10, 4);
    b.DisplayBoard();
    One_Masted on1 = One_Masted(false);
    Two_Masted on2 = Two_Masted(true);
}
