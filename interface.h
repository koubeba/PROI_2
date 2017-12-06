#include "board.h"
#include "ship.h"

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <climits>
#include <string>

#ifndef INTERFACE_H
#define INTERFACE_H

namespace interface{
  class Environment
  {
      std::vector<Ships::Ship*> ships;
      std::vector<Boards::Board*> boards;
    public:
      Environment();
      //Getters
      const int GetShips();
      const int GetBoards();
      void AddShip();
      void AddBoard();
      void PlaceShips(int i);
      void RemoveShipBorders(int i);
      void Display(int i);
      void WriteToFile();
      void ReadFromFile(char* str);
      void AutonomicTest();
  };
  void ShowMenu();
  void Input(int* number, std::string note, int min, int max);
}


#endif
