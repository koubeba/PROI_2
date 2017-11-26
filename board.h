#ifndef BOARD_H
#define BOARD_H

namespace Boards
{
    class Board
    {
        int x, y;
        int **layout;
    public:
        Board(int _y, int _x);
        void DisplayBoard();

        //Getters
        const int GetX();
        const int GetY();

        //Checks if the requested space is free.
        bool checkAvailability(int xStart, int xEnd, int _y, bool vertical);

        bool occupySpace(int xStart, int xEnd, int y, bool vertical, int ID);

        bool borderSpace(int xStart, int xEnd, int _y, bool vertical, int ID);

        bool freeSpace(int xStart, int xEnd, int _y, bool vertical, int ID);

        bool removeBorder(int xStart, int xEnd, int _y, bool vertical, int ID);
    };
}

#endif
