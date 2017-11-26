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

    ShowMenu();
    char inp;
    do
    {
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
          env.RemoveShipBorders(0);
          env.Display(0);
        break;
        case 'D':
        case 'd':
          ShowMenu();
          break;
      }
    }while((inp = getchar())!='q');
}
