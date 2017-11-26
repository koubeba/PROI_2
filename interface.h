#include "board.h"
#include "ship.h"

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <climits>

#ifndef INTERFACE_H
#define INTERFACE_H

namespace interface{
  class Environment
  {
      std::vector<Ships::Ship*> ships;
      std::vector<Boards::Board*> boards;
    public:
      Environment();
      void AddShip();
      void AddBoard();
      void PlaceShips(int i);
      void RemoveShipBorders(int i);
      void Display(int i);
  };
  void ShowMenu();
  void Input(int* number, std::string note, int min, int max);
  void Input(std::string* str, std::string strName);
}


#endif
