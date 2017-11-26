#include <iostream>
#include <stdlib.h>
#include "ship.h"
namespace Ships
{
    int SHIP_MAX_ID; //Max ID of a ship (also number of ships)

    Ship::Ship(bool _vertical)
    {
        std::cout << "Created a new ship." << std::endl;
        id = ++SHIP_MAX_ID; //Return the value, then increment it
        vertical = _vertical;

    }

    bool Ship::CheckBoardSize(Boards::Board& b)
    {
        if (vertical && b.GetY() < size)  return false;
        if (b.GetX() < size) return false;
        return true;
    }

    void Ship::PlaceShipOnBoard(Boards::Board& b, int _x, int _y)
    {
        if (CheckBoardSize(b));
        if (!vertical)
        {
            if (b.occupySpace(_x, _x + size-1, _y, vertical, id))
            {
              x = _y;
              y = _x;
              b.borderSpace(_x, _x + size-1, _y, vertical, id);
            }

        }
        else
        {
            if (b.occupySpace(_y, _y + size-1, _x, vertical, id))
            {
                x = _y;
                y = _x;
              b.borderSpace(_y, _y + size-1, _x, vertical, id);
            }
        }
    }

    void Ship::TakeShipOffBoard(Boards::Board& b)
    {
        if (!vertical)
        {
            if (b.freeSpace(y, y + size-1, x, vertical, id))
            {
              b.removeBorder(y, y + size-1, x, vertical, id);
              x = -1;
              y = -1;

            }

        }
        else
        {
            if (b.freeSpace(x, x + size-1, y, vertical, id))
            {
              b.removeBorder(x, x + size-1, y, vertical, id);
                x = -1;
                y = -1;

            }
        }
    }



    One_Masted::One_Masted(bool _vertical): Ship(_vertical)
    {
        size = 1;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
    Two_Masted::Two_Masted(bool _vertical): Ship(_vertical)
    {
        size = 2;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
    Three_Masted::Three_Masted(bool _vertical): Ship(_vertical)
    {
        size = 3;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
    Four_Masted::Four_Masted(bool _vertical): Ship(_vertical)
    {
        size = 4;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
}
