#include <iostream>
#include <stdlib.h>
#include "ship.h"
namespace Ships
{
    int SHIP_MAX_ID; //Max ID of a ship (also number of ships)

    Ship::Ship()
    {
        std::cout << "Created a new ship." << std::endl;
        id = ++SHIP_MAX_ID; //Return the value, then increment it
        x = -1;
        y = -1;
        vertical = false;
    }

    bool Ship::CheckBoardSize(Boards::Board& b)
    {
        if (vertical && b.GetRows() < size)  return false;
        if (b.GetColumns() < size) return false;
        return true;
    }

    void Ship::PlaceShipOnBoard(Boards::Board& b, int _rows, int _columns)
    {
        if (CheckBoardSize(b));
        if (vertical)
        {
            if (b.occupySpace(_rows, _rows + size-1, _columns, vertical, id))
            {
              x = _rows;
              y = _columns;
              b.borderSpace(_rows, _rows + size-1, _columns, vertical, id);
            }
        }
        else
        {
            if (b.occupySpace(_columns, _columns + size-1, _rows, vertical, id))
            {
                x = _rows;
                y = _columns;
              b.borderSpace(_columns, _columns + size-1, _rows, vertical, id);
            }
        }
    }

    void Ship::TakeShipOffBoard(Boards::Board& b)
    {
        if (vertical)
        {
            if (b.freeSpace(x, x + size-1, y, vertical, id))
            {
              b.removeBorder(x, x + size-1, y, vertical, id);
              x = -1;
              y = -1;
            }
        }
        else
        {
            if (b.freeSpace(y, y + size-1, x, vertical, id))
            {
              b.removeBorder(y, y + size-1, x, vertical, id);
                x = -1;
                y = -1;
            }
        }
    }

    void Ship::RemoveShipBorders(Boards::Board& b)
    {
      if (!vertical)
      {
        b.removeBorder(y, y + size-1, x, vertical, id);
      }
      else
      {
        b.removeBorder(x, x + size-1, y, vertical, id);
      }
    }

    bool operator <(Ship& s1, Ship& s2)
    {
      return (s1.GetSize() < s2.GetSize());
    }

    void Ship::MakeVertical(bool _verticality)
    {
      vertical = _verticality;
    }

    //Getters
    int Ship::GetID() {return id;}
    int Ship::GetSize() {return size;}

    int One_Masted::GetSize() {return 1;}
    int Two_Masted::GetSize() {return 2;}
    int Three_Masted::GetSize() {return 3;}
    int Four_Masted::GetSize() {return 4;}

    One_Masted::One_Masted(): Ship()
    {
        size = 1;
        std::cout << "Created a new one-masted ship. ID: " << id << ", size: " << size << std::endl;

    }
    Two_Masted::Two_Masted(): Ship()
    {
        size = 2;
        std::cout << "Created a new two-masted ship. ID: " << id << ", size: " << size << std::endl;

    }
    Three_Masted::Three_Masted(): Ship()
    {
        size = 3;
        std::cout << "Created a new three-masted ship. ID: " << id << ", size: " << size << std::endl;

    }
    Four_Masted::Four_Masted(): Ship()
    {
        size = 4;
        std::cout << "Created a new four-masted ship. ID: " << id << ", size: " << size << std::endl;

    }

    bool ShipCompare (Ship* s1, Ship* s2) { return (*s1<*s2); }
}
