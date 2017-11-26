#include "board.h"

#ifndef DATE_H
#define DATE_H

namespace Ships {


    class Ship {
    protected:
        int id;
        int x, y; //Coordinates on a board, where each coordinate is the smaller one (so a horizontal ship 2x1 would occupy space from x to x+1)
        bool vertical; //True for vertically placed ship, False for horizontally placed one
        int size; //from 1 to 4

        //Checks if the board is the right size.
        bool CheckBoardSize(Boards::Board& b);

    public:
        Ship(bool _vertical);
        void PlaceShipOnBoard(Boards::Board& b, int _x, int _y);
        void TakeShipOffBoard(Boards::Board& b);
    };

    class One_Masted : public Ship {
    public:
        One_Masted(bool _vertical);
    };

    class Two_Masted : public Ship {
    public:
        Two_Masted(bool _vertical);
    };

    class Three_Masted : public Ship {
    public:
        Three_Masted(bool _vertical);
    };

    class Four_Masted : public Ship {
    public:
        Four_Masted(bool _vertical);
    };
}

#endif
