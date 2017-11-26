#include <iostream>
#include "board.h"

namespace Boards
{
    Board::Board(int _y, int _x)
    {
        x = _x;
        y = _y;
        layout = new int*[x];

        for (int i = 0; i < x; i++)
        {
            layout[i] = new int[y];
            for (int j = 0; j < y; j++)
                layout[i][j] = 0;
            //Fill the array with zeroes
        }
        std::cout << "Created a board " << x << "x" << y << std::endl;

        //Ship on board representation:
        //0- unoccupied space
        //i- id of occupying ship
        //-i- border of ship, that can't be occupied by another ship
    }

    void Board::DisplayBoard()
    {
        for (int i = 0; i<x; i++)
        {
            for (int j=0; j<y; j++)
                std::cout << layout[i][j] << "\t";
            std::cout << std::endl;
        }
    }

    const int Board::GetX()
    {
        return x;
    }
    const int Board::GetY()
    {
        return y;
    }

    bool Board::checkAvailability(int xStart, int xEnd, int _y, bool vertical)
    {
        //First: are the requested coordinates in the board
        if (!vertical)
        {
            if (_y<0 || _y >= x) return false;
            if (xStart < 0 || xStart >= y) return false;
            if (xEnd < 0 || xEnd >= y) return false;
        }
        else
        {
            if (_y<0 || _y >= y) return false;
            if (xStart < 0 || xStart >= x) return false;
            if (xEnd < 0 || xEnd >= x) return false;
        }
        //Are the requested coords valid
        if (xEnd < xStart) return false;

        int i = xStart;
        if (vertical)
        {
            while (i <= xEnd)
            {
                if (layout[i][_y] != 0)
                    return false;
                i++;
            }
            return true;
        }
        else
        {
            while (i <= xEnd)
            {
                if (layout[_y][i] != 0)
                    return false;
                i++;
            }
            return true;
        }
    }

    bool Board::occupySpace(int xStart, int xEnd, int y, bool vertical, int ID)
    {
        if (checkAvailability(xStart, xEnd, y, vertical))
        {
            int i = xStart;
            if (vertical)
            {
                while (i <= xEnd)
                {
                    layout[i][y] = ID;
                    i++;
                }
                return true;
            }
            else
            {
                while (i <= xEnd)
                {
                    layout[y][i] = ID;
                    i++;
                }
                return true;
            }
        }
        return false;
    }

    bool Board::borderSpace(int xStart, int xEnd, int _y, bool vertical, int ID)
    {
            //border top
            occupySpace(xStart-1,xStart-1, _y, vertical, -ID);
            //borders left and right
            for (int i=xStart-1; i <= xEnd+1; i++)
            {
              occupySpace(i, i, _y-1, vertical, -ID);
              occupySpace(i, i, _y+1, vertical, -ID);
            }
            //border bottom
            occupySpace(xEnd+1, xEnd+1, _y, vertical, -ID);

            return true;
    }

    bool Board::freeSpace(int xStart, int xEnd, int _y, bool vertical, int ID)
    {
      //First: are the requested coordinates in the board
      if (!vertical)
      {
          if (_y<0 || _y >= x) return false;
          if (xStart < 0 || xStart >= y) return false;
          if (xEnd < 0 || xEnd >= y) return false;
      }
      else
      {
          if (_y<0 || _y >= y) return false;
          if (xStart < 0 || xStart >= x) return false;
          if (xEnd < 0 || xEnd >= x) return false;
      }
      //Are the requested coords valid
      if (xEnd < xStart) return false;
      int i = xStart;
      if (vertical)
      {
          while (i <= xEnd)
          {
              if (layout[i][_y] == ID) layout[i][_y] = 0;
              i++;
          }
          return true;
      }
      else
      {
          while (i <= xEnd)
          {
              if (layout[_y][i] == ID)
              layout[_y][i] = 0;
              i++;
          }
          return true;
      }

    };

    bool Board::removeBorder(int xStart, int xEnd, int _y, bool vertical, int ID)
    {
      //border top
      freeSpace(xStart-1,xStart-1, _y, vertical, -ID);
      //borders left and right
      for (int i=xStart-1; i <= xEnd+1; i++)
      {
        freeSpace(i, i, _y-1, vertical, -ID);
        freeSpace(i, i, _y+1, vertical, -ID);
      }
      //border bottom
      freeSpace(xEnd+1, xEnd+1, _y, vertical, -ID);

      return true;
    }

}
