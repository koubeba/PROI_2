#include <iostream>
#include <stdlib.h>
#include "ship.h"
namespace Ship
{
    int SHIP_MAX_ID; //Max ID of a ship (also number of ships)

    Ship::Ship()
    {
        std::cout << "Created a new ship." << std::endl;
        id = ++SHIP_MAX_ID; //Return the value, then increment it

    }
    One_Masted::One_Masted(): Ship()
    {
        size = 1;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
    Two_Masted::Two_Masted(): Ship()
    {
        size = 2;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
    Three_Masted::Three_Masted(): Ship()
    {
        size = 3;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
    Four_Masted::Four_Masted(): Ship()
    {
        size = 4;
        std::cout << "Created a new ship. ID: " << id << ", size: " << size << std::endl;

    }
}
