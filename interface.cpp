#include "board.h"
#include "ship.h"

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#include "interface.h"

namespace interface
{
  Environment::Environment()
  {
    ships = std::vector<Ships::Ship*>();
    boards = std::vector<Boards::Board*>();
  }

  void Environment::AddShip()
  {
    int sailCount;
    interface::Input(&sailCount, "How many sails (1- one-masted ship etc.)", 1, 4);
    switch(sailCount)
    {
      case 1:
        ships.push_back(new Ships::One_Masted());
      break;
      case 2:
        ships.push_back(new Ships::Two_Masted());
      break;
      case 3:
        ships.push_back(new Ships::Three_Masted());
      break;
      case 4:
        ships.push_back(new Ships::Four_Masted());
      break;
    }
  }
  void Environment::AddBoard()
  {
    int columns, rows;
    interface::Input(&columns, "How many columns?", 1, 100);
    interface::Input(&rows, "How many rows?", 1, 100);
    boards.push_back(new Boards::Board(columns, rows));
  }
  void Environment::PlaceShips(int i)
  {
    if (boards.size()==0) return;
    //TODO: Make a copy of board without border rows?

    //Copy the vector of ships.
    //Sort it by ships size.
    std::sort(ships.begin(), ships.end(), Ships::ShipCompare);
    //An array of x coords for ships, and one for y coords for ship. Init it with -1.

    int* xCoords;
    int* yCoords;
    xCoords = new int[ships.size()];
    yCoords = new int[ships.size()];

    for (int i=0; i < ships.size(); i++)
    {
      xCoords[i] = -1;
      yCoords[i] = -1;
    }

    //Place the ships on board starting from the largest. Iterate until there are ships to place.

      int x, y; //Current x and y
      x = 0;
      y = 0;

      int maxX, maxY;
      int* lastX;

      maxX = boards[0]->GetX();
      maxY = boards[0]->GetY() % 2 == 1 ? boards[0]->GetY()/2 + 1 : boards[0]->GetY()/2;

      lastX = new int[maxY];
      for (int i = 0; i<maxY; i++) lastX[i] = 0;

      int index = ships.size()-1;

      for (int k = ships.size()-1; k >= 0; k--)
      {

        std::cout << "Figuring out for a ship " << ships[k]->GetID() << " of size " << ships[k]->GetSize() << std::endl;

        //If there is enough place in a row, add a ship to the row.
        ARGH: if (x+ships[k]->GetSize() < maxX)
        {
          xCoords[k] = x;
          yCoords[k] = y;

          x+= ships[k]->GetSize();
          if (x!=maxX-1) x+=1;

          lastX[y] = x;

          continue;
        }
        else if (y+2 < maxY)
        {
          y+=2;
          x = lastX[y];
          goto ARGH;
        }
        else
        {
          y = 0;
          x = lastX[0];
          goto ARGH;
        }
      }

      //test:
      for(int i=0; i<ships.size(); i++)
      {
        std::cout << "A ship size: " << ships[i]->GetSize() << " ,x: " << xCoords[i] << " ,y " << yCoords[i] << std::endl;
      }

      //Place ships:
      for (int k=0; k<ships.size(); k++)
      {
        ships[k]->PlaceShipOnBoard(*boards[0], xCoords[k], yCoords[k]);
      }

  }

  void Environment::RemoveShipBorders(int b)
  {
    std::cout << "hello" << std::endl;
    if (boards.size()<=b) return;
    for (int i = 0; i < ships.size(); i++)
      ships[i]->RemoveShipBorders(*boards[b]);
  }
  {
      if (boards.size()<=i) return;
      boards[i]->DisplayBoard();
  }


  void ShowMenu()
  {
    std::cout << "\ta)Add a new ship to the list" << std::endl;
    std::cout << "\tb)Add a new board" << std::endl;
    std::cout << "\tc)Place ships from a list to a board" << std::endl;
    std::cout << "\td)Show menu" << std::endl;
    std::cout << "\te)Automatic test" << std::endl;
    std::cout << "\tq)Exit" << std::endl;
  }


  void Input(int* number, std::string note = "Enter a number", int min = INT_MIN, int max = INT_MAX)
  {
    //Checking: is the given pointer not null
    if (number)
    {
        //Checking: is the entered data the right type (int)
        while ((std::cout << note + ": ") && !(std::cin >> *number))
        {
            //Clearing the input after receiving wrong data.
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "ERROR: Wrong input type. Please enter a number." << std::endl;
        }
        //Checking: is the entered number in right range.
        if (min != INT_MIN)
        {
            if (*number < min)
            {
                std::cout << "ERROR: Number too small. Please enter a number bigger than " << (min-1) << " and smaller than " << (max+1) << std::endl;
                Input(number, note, min, max);
            }
        }
        if (max != INT_MAX)
        {
            if (*number > max)
            {
                std::cout << "ERROR: Number too big. Please enter a number bigger than " << (min-1) << " and smaller than " << (max+1) << std::endl;
                Input(number, note, min, max);
            }
        }
    }
}


void Input(std::string* str, std::string strName = "name")
{
    //Checking: is the given pointer not null
    if (str)
    {
        //Checking: is the entered data the right type (std::string)
        while ((std::cout << "Enter a " + strName + ": ") && !(std::cin >> *str))
        {
            //Clearing the input after receiving wrong data.
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "Wrong input.";
        }
    }
}

}
