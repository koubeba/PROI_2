#include "board.h"
#include "ship.h"

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <fstream>
#include <string>

#include "interface.h"

namespace interface
{
  Environment::Environment()
  {
    ships = std::vector<Ships::Ship*>();
    boards = std::vector<Boards::Board*>();
  }

  const int Environment::GetShips()
  {
    return ships.size();
  }
  const int Environment::GetBoards()
  {
    return boards.size();
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
    interface::Input(&columns, "How many columns? (1-100)", 1, 100);
    interface::Input(&rows, "How many rows? (1-100)", 1, 100);
    boards.push_back(new Boards::Board(rows, columns));
  }
  void Environment::PlaceShips(int i)
  {
	  
    if (boards.size()==0) return;
    //std::cout << "Rows: " << boards[0]->GetRows() << " Columns: " << boards[0]->GetColumns() << std::endl;

    //Copy the vector of ships.
    //Sort it by ships size.
    std::sort(ships.begin(), ships.end(), Ships::ShipCompare);

    //An array of row coords for ships, and one for column coords for ship. Init it with -1.
    int* rowCoords;
    int* columnCoords;
    rowCoords = new int[ships.size()];
    columnCoords = new int[ships.size()];

    for (int i=0; i < ships.size(); i++)
    {
      rowCoords[i] = -1;
      columnCoords[i] = -1;
    }

    //Calculate maximum row and maximum columnindex
    int maxRow, maxColumn;
    //If there are more columns than rows, we are going to place the ships horizontally.
    if (boards[i]->GetRows() <= boards[i]->GetColumns())
    {
      //The max column index is simple:
      maxColumn = boards[i]->GetColumns()-1;
      //The rows are cut down by half (we will skip every second row to leave it as a border for ships.)
      maxRow = boards[i]->GetRows() % 2 == 1 ? boards[i]->GetRows()/2 + 1 : boards[i]->GetRows()/2;
    }
    //If there are more rows than columns, we are going to place the ships vertically.
    else
    {
      //The max row index is simple:
      maxRow = boards[i]->GetRows()-1;
      //The columns are cut down by half (we will skip every second column to leave it as a border for ships.)
      maxColumn = boards[i]->GetColumns() % 2 == 1 ? boards[i]->GetColumns()/2 + 1 : boards[i]->GetColumns()/2;
    }

    //An array of last index for every row/column.
    int* lastIndex;
    if (boards[i]->GetRows() <= boards[i]->GetColumns())
    {
      lastIndex = new int[maxColumn];
      for (int i = 0; i<maxColumn; i++) lastIndex[i] = 0;
    }
    else
    {
      lastIndex = new int[maxRow];
      for (int i = 0; i<maxRow; i++) lastIndex[i] = 0;
    }

    int row, column; //Current x(row) and y(column)
    row = 0;
    column = 0;

    int iter = 0;

    int index = ships.size()-1;

    //DEBUG
    std::cout << "Max column: " << maxColumn << " max row: " << maxRow << std::endl;
    //DEBUG

     //Place the ships on board starting from the largest. Iterate until there are ships to place.

     //If there are more rows than columns, place the ships vertically (iterate through rows, then through columns):
      if (boards[i]->GetRows() > boards[i]->GetColumns())
      {
        //Iterate through all ships
        for (int k = ships.size()-1; k >= 0; k--)
        {
          //Zero iteration for the k-th ship
          iter = 0;
          //DEBUG
          std::cout << "Figuring out for a ship " << ships[k]->GetID() << " of size " << ships[k]->GetSize() << std::endl;
          //DEBUG

          AHMM:
          //Increase iteration by one (preventing an infinite loop)
          iter++;
          //DEBUG
          std::cout << "Iter: " << iter  << "Current row: " << row << "Current column: " << column << "LAst index in column: " << lastIndex[column]<< std::endl;
          //DEBUG

          //If there is enough place in a column
          if (lastIndex[column]+ships[k]->GetSize() <= maxRow)
          {
            //DEBUG
            std::cout << "There is enough place in column" <<std::endl;
            //DEBUG

            rowCoords[k] = row;
            columnCoords[k] = column;

            row+= ships[k]->GetSize();
            //If the ship won't take up whole space in column, add one unit of border.
            if (row<maxRow)
            {
              //DEBUG//
              std::cout << "Adding one unit of border" <<std::endl;
              //DEBUG//
              row+=1;
            }

            //last occupied index in this row is the column
            lastIndex[column] = row;
            continue;
          }
          //If there isn't enough place in a column, jump to the next column.
          else if (column+2 <= maxColumn)
          {
            //DEBUG
            std::cout << "Moving on to next column" <<std::endl;
            //DEBUG
            column+=2;
            row = lastIndex[column];
            goto AHMM;
          }
          //If there isn't enough place in the last column, start all over
          else
          {
            //DEBUG
            std::cout << "Starting all over" <<std::endl;
            //DEBUG
            column = 0;
            row = lastIndex[0];
            if (iter>=(2*maxColumn)+1) continue;
            goto AHMM;
          }
        }
      }
      //If there is more columns than rows, place the ships horizontally
      else
      {
        //Iterate through all ships
        for (int k = ships.size()-1; k >= 0; k--)
        {
          iter = 0;
          //DEBUG
          std::cout << "Figuring out for a ship " << ships[k]->GetID() << " of size " << ships[k]->GetSize() << std::endl;
          //DEBUG

          //If there is enough place in a row, add a ship to the row. (Iterate through columns, then through rows)
          ARGH:
          iter++;
          //DEBUG
          std::cout << "Iter: " << iter << std::endl;
          //DEBUG
          //DEBUG
          std::cout << "Iter: " << iter  << "Current row: " << row << "Current column: " << column << "LAst index in column: " << lastIndex[column]<< std::endl;
          //DEBUG
          if (lastIndex[row]+ships[k]->GetSize() <= maxColumn)
          {
            //DEBUG
            std::cout << "There is enough place in column" <<std::endl;
            //DEBUG
            rowCoords[k] = row;
            columnCoords[k] = column;

            column += ships[k]->GetSize();
            //If the ship doesn't take all space in the row, add one unit of border.
            if (column<maxColumn)
            {
              //DEBUG//
              std::cout << "Adding one unit of border" << std::endl;
              //DEBUG//
              column+=1;
            }

            lastIndex[row] = column;

            continue;
          }
          //If there isn't enough place in row, move on to the next one.
          else if (row+2 <= maxRow)
          {
            //DEBUG
            std::cout << "Moving on to next column" <<std::endl;
            //DEBUG
            row+=2;
            column = lastIndex[row];
            goto ARGH;
          }
          //If there isn't enogh place in last row, start all over.
          else
          {
            //DEBUG
            std::cout << "Starting all over" <<std::endl;
            //DEBUG
            row = 0;
            column = lastIndex[0];
            if (iter>=(2*maxRow)+1) continue;
            goto ARGH;
          }
        }
      }
      std::cout << "Calculated all ships:" <<std::endl;

      /*test:
      for(int i=0; i<ships.size(); i++)
      {
        std::cout << "A ship size: " << ships[i]->GetSize() << " ,x: " << xCoords[i] << " ,y " << yCoords[i] << std::endl;
      }*/

      //If there is more columns than rows, place the ships horizontally.
      if (boards[i]->GetRows() <= boards[i]->GetColumns())
        for (int k=0; k<ships.size(); k++)
          ships[k]->MakeVertical(false);
      else
        for (int k=0; k<ships.size(); k++)
          ships[k]->MakeVertical(true);

      std::cout << "Place the ships:" <<std::endl;
      //Place ships:
      for (int k=0; k<ships.size(); k++)
      {
        ships[k]->PlaceShipOnBoard(*boards[i], rowCoords[k], columnCoords[k]);
      }

  }
  void Environment::RemoveShipBorders(int b)
  {
    if (boards.size()<=b) return;
    for (int i = 0; i < ships.size(); i++)
      ships[i]->RemoveShipBorders(*boards[b]);
  }
  void Environment::Display(int b)
  {
      if (boards.size()<=b) return;
      boards[b]->DisplayBoard();
  }
  void ShowMenu()
  {
    std::cout << "\ta)Add a new ship to the list" << std::endl;
    std::cout << "\tb)Add a new board" << std::endl;
    std::cout << "\tc)Place ships from a list to a board" << std::endl;
    std::cout << "\td)Show menu" << std::endl;
    std::cout << "\te)Automatic test" << std::endl;
    std::cout << "\tf)Write to file" << std::endl;
    std::cout << "\tg)Read from file" << std::endl;
    std::cout << "\tq)Exit" << std::endl;
  }
  void Environment::WriteToFile()
  {
    std::ofstream file;
    std::string name;
    std::cout << "Give a file name: ";
    std::cin >> name;
    file.open(name.c_str());
    if (file.good())
      std::cout << "File is correct!" <<std::endl;
    else
    {
      std::cout << "File is wrong!" << std::endl;
      return;
    }
    file << boards.size() << std::endl;
    for (int i=0; i<boards.size(); i++)
      file << boards[i]->GetRows() << " " << boards[i]->GetColumns() << std::endl;
    file << ships.size() << std::endl;
    for (int i=0; i<ships.size(); i++)
      file << ships[i]->GetSize() << std::endl;
    file.close();
  }
  void Environment::ReadFromFile(char* str)
  {
    std::ifstream file;
    file.open(str);
    if (file.good())
    {
      std::cout << "Good!" << std::endl;
      int boardsC, shipsC, rows, columns;
      file >> boardsC;
      for (int i=0; i<boardsC; i++)
      {
        file >> rows >> columns;
        boards.push_back(new Boards::Board(rows, columns));
      }
      file >> shipsC;
      for (int i=0; i<shipsC; i++)
      {
        file >> rows;
        switch(rows)
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
          default:
          break;
        }
      }
      file.close();
      return;
    }
    std::cout << "File is incorrect!" << std::endl;
  }

  void Environment::AutonomicTest()
  {
    std::cout << "Doing an autonomic test." << std::endl;
    std::cout << "Creating a 10x10 board." << std::endl;
    boards.push_back(new Boards::Board(10, 10));
    std::cout << "Displaying a board." << std::endl;
    boards[boards.size()-1]->DisplayBoard();
    std::cout << "Creating two one-masted ships." << std::endl;
    ships.push_back(new Ships::One_Masted());
    ships.push_back(new Ships::One_Masted());
    std::cout << "Creating a two-masted ship." << std::endl;
    ships.push_back(new Ships::Two_Masted());
    std::cout << "Creating a three-masted ship." << std::endl;
    ships.push_back(new Ships::Three_Masted());
    std::cout << "Creating a four-masted ship." << std::endl;
    ships.push_back(new Ships::Four_Masted());
    PlaceShips(boards.size()-1);
    RemoveShipBorders(boards.size()-1);
    boards[boards.size()-1]->DisplayBoard();
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

  template <class T>
  void swap(T& t1, T& t2)
  {
        T buf = t1;
        t1 = t2;
        t2 = buf;
    }

}
