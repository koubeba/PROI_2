#ifndef DATE_H
#define DATE_H

namespace Ship {


    class Ship {
    protected:
        int id;
        int x, y; //Coordinates on a board, where each coordinate is the smaller one (so a horizontal ship 2x1 would occupy space from x to x+1)
        bool vertical; //True for vertically placed ship, False for horizontally placed one
        int size; //from 1 to 4

    public:
        Ship();
    };

    class One_Masted : protected Ship {
    public:
        One_Masted();
    };

    class Two_Masted : protected Ship {
    public:
        Two_Masted();
    };

    class Three_Masted : protected Ship {
    public:
        Three_Masted();
    };

    class Four_Masted : protected Ship {
    public:
        Four_Masted();
    };
}

#endif