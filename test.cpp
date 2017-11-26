#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "ship.h"
#include "board.h"
#include "interface.h"

using namespace std;
using namespace Ships;
using namespace Boards;
using namespace interface;

int main()
{
    Environment env = Environment();

    char inp;
    do
    {
      ShowMenu();
      switch(inp)
      {
        case 'A':
        case 'a':
          env.AddShip();
        break;
        case 'B':
        case 'b':
          env.AddBoard();
        break;
        case 'C':
        case 'c':
          env.PlaceShips(0);
        break;
      }
    }while((inp = getchar())!='q');
}
