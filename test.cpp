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

int main(int argc, char** argv)
{
    Environment env = Environment();
    Environment testEnv = Environment();
    
    int i;

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
        if (env.GetShips() == 0 || env.GetBoards() == 0)
        {
          std::cout << "Error! No boards or ships." << std::endl;
          break;
        }
          Input(&i, "Board index: ", 0, env.GetBoards()-1);
          env.PlaceShips(i);
          env.RemoveShipBorders(i);
          env.Display(i);
        break;
        case 'D':
        case 'd':
          ShowMenu();
          break;
        case 'E':
        case 'e':
          testEnv.AutonomicTest();
          break;
        case 'F':
        case 'f':
          env.WriteToFile();
        break;
        case 'h':
        case 'H':
        if (env.GetBoards() == 0) 
        {
			std::cout << "No boards to show!"<<std::endl;
			break;
		}
        Input(&i, "Board index: ", 0, env.GetBoards()-1);
        env.Display(i);
        break;
        case 'G':
        case 'g':
          if (argc < 2)
          {
            std::cout << "Error! No file name" << std::endl;
            break;
          }
          env.ReadFromFile(argv[1]);
        break;
      }
    }while((inp = getchar())!='q');
}
