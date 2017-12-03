#include <iostream>
#include "board.h"

namespace Boards
{
    Board::Board(int _rows, int _columns)
    {
        rows = _rows;
        columns = _columns;
        layout = new int*[rows];

        for (int i = 0; i < rows; i++)
        {
            layout[i] = new int[columns];
            for (int j = 0; j < columns; j++)
                layout[i][j] = 0;
            //Fill the array with zeroes
        }
        std::cout << "Created a board " << rows << " rows and " << columns << " columns."<<std::endl;

        //Ship on board representation:
        //0- unoccupied space
        //i- id of occupying ship
        //-i- border of ship, that can't be occupied by another ship
    }

    void Board::DisplayBoard()
    {
        for (int i = 0; i<rows; i++)
        {
            for (int j=0; j<columns; j++)
                std::cout << layout[i][j] << "\t";
            std::cout << std::endl;
        }
    }

    const int Board::GetRows()
    {
        return rows;
    }
    const int Board::GetColumns()
    {
        return columns;
    }

    bool Board::checkAvailability(int xStart, int xEnd, int _y, bool vertical)
    {
        //First: are the requested coordinates in the board

        //If the ship is placed horizontal, the row index is constant and the column index changes.
        if (!vertical)
        {
            //is the row index smaller than zero or bigger than last row index?
            if (_y<0 || _y >= rows) return false;
            //is the starting column index smaller than zero or bigger than last column index?
            if (xStart < 0 || xStart >= columns) return false;
            //is the end column index smaller than zero or bigger than last column index?
            if (xEnd < 0 || xEnd >= columns) return false;
        }
        //If the ship is vertical, the column index is constant and the row index changes.
        else
        {
            //is the column index smaller than zero or bigger than last column index?
            if (_y<0 || _y >= columns) return false;
            //is the starting row index smaller than zero or bigger than last row index?
            if (xStart < 0 || xStart >= rows) return false;
            //is the end row index smaller than zero or bigger than last row index?
            if (xEnd < 0 || xEnd >= rows) return false;
        }
        //Are the requested coords valid: is the end index bigger or equal than start index
        if (xEnd < xStart) return false;

        //Start iteration from start index.
        int i = xStart;

        //If the ship is vertical, the row index changes while the column index is constant.
        if (vertical)
        {
            //Iterate until the end index
            while (i <= xEnd)
            {
              //For vertical ships, iterate the rows
                if (layout[i][_y] != 0)
                    return false;
                i++;
            }
            return true;
        }
        //If the ship is horizontal, the row index is constant while the column index changes.
        else
        {
          //Iterate until the end index
            while (i <= xEnd)
            {
              //For vertical ships, iterate the columns
                if (layout[_y][i] != 0)
                    return false;
                i++;
            }
            return true;
        }
    }

    bool Board::occupySpace(int xStart, int xEnd, int y, bool vertical, int ID)
    {
      //First, check the availability of the space
        if (checkAvailability(xStart, xEnd, y, vertical))
        {
          //If the space is available, start the iteration from starting index
            int i = xStart;
            if (vertical)
            {
              //Iterate until end index
                while (i <= xEnd)
                {
                  //For vertical ships, iterate the rows
                  //Replace zero with ID number
                    layout[i][y] = ID;
                    i++;
                }
                return true;
            }
            else
            {
              //Iterate until end index
                while (i <= xEnd)
                {
                  //For horizontal ships, iterate the columns
                  //Replace zero with ID number
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
          if (_y<0 || _y >= rows) return false;
          if (xStart < 0 || xStart >= columns) return false;
          if (xEnd < 0 || xEnd >= columns) return false;
      }
      else
      {
          if (_y<0 || _y >= columns) return false;
          if (xStart < 0 || xStart >= rows) return false;
          if (xEnd < 0 || xEnd >= rows) return false;
      }
      //Are the requested coords valid
      if (xEnd < xStart) return false;

      //Start the iteration from starting index
      int i = xStart;
      if (vertical)
      {
        //Iterate until the end index
          while (i <= xEnd)
          {
            //For vertical ships iterate the rows
            //Check if the space is occupied by the ship
              if (layout[i][_y] == ID)
              layout[i][_y] = 0;
              i++;
          }
          return true;
      }
      else
      {
        //Iterate until the end index
          while (i <= xEnd)
          {
            //For horizontal ships iterate the columns
            //Check if the space is occupied by the ship
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
