// File: sweepergrid.cpp
// Sweepergrid class functions definitions
//
// ------------------------------------------------------------
// Class: CS 215                        Instructor: Dr. Deborah Hwang
// Assignment: Project4- Minesweeper    Date assigned: March 2, 2020
// Programmer: Munachimso Aneke         Date completed: March 29, 2020

#include <stdexcept>     // throw, out_of_range
#include <cstdlib>       // srand(), exit(), rand()
#include <ctime>         // time()
#include <algorithm>     // copy, swap 
#include "sweepercell.h" // SweeperCell class
#include "sweepergrid.h" // SweeperGrid class


// Private Helper Functions
SweeperCell& SweeperGrid::at(int row, int col) 
{
   // Bounds check
   if (row < 0 || row >= num_rows || col < 0 || col >= num_columns) 
   {
      throw std::out_of_range("Error: Location out of range. Try again!");
   }

   return grid[(row * num_columns) + col];
}

const SweeperCell& SweeperGrid::at(int row, int col)const 
                                                         
{
   // Bounds check
   if (row < 0 || row >= num_rows || col < 0 || col >= num_columns) 
   {
      throw std::out_of_range("Error: Location out of range. Try again!");
   }

   return grid[(row * num_columns) + col];
}


// Default constructor
SweeperGrid::SweeperGrid(int initial_rows, int initial_cols,       
			 int density) :    num_rows(initial_rows),
					   num_columns(initial_cols),
					   num_bombs(0)
{
   srand(time(0)); // seeded random generator
   //srand(5);
   
   // Bounds check
   if((initial_rows < 5) || (initial_cols < 5) || (density < 10) ||
      (density > 50))
   {
      std::cerr
	 << "Error: Grid not large enough/ too many or no cells contain bomb!"
	 << std::endl;
      
      exit(1);
   }

   // Dynamic Allocation
   grid = new SweeperCell[num_rows * num_columns];
   
   //Place bombs
   for(int row = 0; row < num_rows; row++)
   {
      for(int col = 0; col < num_columns; col++)
      {
	 if((rand() % 100 + 1) < density) // use random generator
	 {
	    place_bomb(row, col);
	 }
      }
   }
}


// Copy Constructor
SweeperGrid::SweeperGrid (const SweeperGrid & source)
{
   // copy the primitive data
   num_rows = source.num_rows;  /* Note: num_rows refers to this->num_rows*/
   num_columns = source.num_columns;
   num_bombs = source.num_bombs;

   // allocate a new grid dynamically
   grid = new SweeperCell[num_rows * num_columns];

   // copy grid values of source into copy
   for(int i = 0; i < num_rows * num_columns; i++)
   {
      grid[i] = source.grid[i];
   }
   
}


// Destructor
SweeperGrid::~SweeperGrid()
{
   // deallocate grid array
   delete [] grid;
}


// Accessors
int SweeperGrid::rows() const
{
   return num_rows;
}

int SweeperGrid::columns() const
{
   return num_columns;
}

int SweeperGrid::bombs() const
{
   return num_bombs;
}


// Mutators
void SweeperGrid::place_bomb(int row, int col)
{
   // Bounds Check
   if(row < 0 || row >= num_rows || col < 0 || col >= num_columns)
   {
      throw std::out_of_range("Error: Location out of range!");
}
   else
   {
      // check if there's bomb
      if(at(row, col).has_bomb())
      {
	 return;
      }
      else // if no bomb, place bomb
      {
	 at(row, col).place_bomb();
	 num_bombs ++;
	 
	 // increase bomb counting in all 8 directions
	 // Top
	 if(row > 0)
	 {
	    at(row-1, col).incr_num_adjacent();
	 }
	 
	 // Bottom
	 if(row < num_rows - 1)
	 {
	    at(row+1, col).incr_num_adjacent();
	 }
	 
	 // Left
	 if(col > 0)
	 {
	    at(row, col-1).incr_num_adjacent();
	 }
	 
	 // Right
	 if(col < num_columns - 1)
	 {
	    at(row, col+1).incr_num_adjacent();
	 }
	 
	 // Top-left
	 if((row > 0) && (col > 0))
	 {
	    at(row-1, col-1).incr_num_adjacent();
	 }
	 
	 // Top-right
	 if((row > 0) && (col < num_columns - 1))
	 {
	    at(row-1, col+1).incr_num_adjacent();
	 }
	 
	 // Bottom-left
	 if((row < num_rows - 1) && (col > 0))
	 {
	    at(row+1, col-1).incr_num_adjacent();
	 }
	 
	 // Bottom-right
	 if((row < num_rows - 1) && (col < num_columns - 1))
	 {
	    at(row+1, col+1).incr_num_adjacent();
	 }
      }
   }
}

void SweeperGrid::remove_bomb(int row, int col)
{
   // Bounds Check
   if(row < 0 || row >= num_rows || col < 0 || col >= num_columns)
   {
      throw std::out_of_range("Error: Location out of range!");
   }
   else
   {
      // check if there's no bomb
      if(!(at(row, col).has_bomb()))
      {
	 return;
      }
      else // if there's a bomb, remove bomb
      {
	 at(row, col).remove_bomb();
	 num_bombs --;

	 // decrease bomb counting in all 8 directions
	 // Top
	 if(row > 0)
	 {
	    at(row-1, col).decr_num_adjacent();
	 }
	 
	 // Bottom
	 if(row < num_rows - 1)
	 {
	    at(row+1, col).decr_num_adjacent();
	 }
	 
	 // Left
	 if(col > 0)
	 {
	    at(row, col-1).decr_num_adjacent();
	 }
	 
	 // Right
	 if(col < num_columns - 1)
	 {
	    at(row, col+1).decr_num_adjacent();
	 }
	 
	 // Top-left
	 if((row > 0) && (col > 0))
	 {
	    at(row-1, col-1).decr_num_adjacent();
	 }
	 
	 // Top-right
	 if((row > 0) && (col < num_columns - 1))
	 {
	    at(row-1, col+1).decr_num_adjacent();
	 }
	 
	 // Bottom-left
	 if((row < num_rows - 1) && (col > 0))
	 {
	    at(row+1, col-1).decr_num_adjacent();
	 }
	 
	 // Bottom-right
	 if((row < num_rows - 1) && (col < num_columns - 1))
	 {
	    at(row+1, col+1).decr_num_adjacent();
	 }
	 
      }
   }
}

bool SweeperGrid::uncover(int row, int col)
{
   // Bounds Check
   if(row < 0 || row >= num_rows || col < 0 || col >= num_columns)
   {
      throw std::out_of_range("Error: Location out of range!");
   }
   else // uncover cell
   {
      at(row, col).uncover();
      
      // if cell has bomb, uncover will be false
      if (at(row, col).has_bomb())
      {
	 return false;
      }
      else // else uncover will be true
      {
	 return true;
      }
   }
}

void SweeperGrid::mark(int row, int col)
{
    // Bounds Check
   if(row < 0 || row >= num_rows || col < 0 || col >= num_columns)
   {
      throw std::out_of_range("Error: Location out of range!");
   }
   else  // mark cell
   {
      at(row,col).mark();
   }
}

void SweeperGrid::unmark(int row, int col)
{
   // Bounds Check
   if(row < 0 || row >= num_rows || col < 0 || col >= num_columns)
   {
      throw std::out_of_range("Error: Location out of range!");
   }
   else  // unmark cell
   {
      at(row,col).unmark();
   }
}

void SweeperGrid::write(std::ostream & out) const
{
   for (int row = 0; row < num_rows; row++) // for each row
   {
      for(int col = 0; col < num_columns; col++) // for each column
      {
	 out << "  " << at(row, col);  // print out each cell
      }
      
      out << std::endl;
   }
}

bool SweeperGrid::game_won()
{
   for (int row = 0; row < num_rows; row++) // for each row
   {
      for(int col = 0; col < num_columns; col++) // for each column
      {
	 // check if bomb is marked and has a bomb or
	 //    uncovered and does not have a bomb
	 if((!at(row, col).is_marked() && at(row, col).has_bomb()) ||
	    (at(row, col).is_covered() && !at(row, col).has_bomb()))
	 {
	    return false;
	 }
      }
   }

   return true;
}

SweeperGrid & SweeperGrid::operator= (const SweeperGrid & source)
{
   // make a copy of the source
   SweeperGrid copy(source);

   //swap contents of this object using swap algorithm
   std::swap (num_rows, copy.num_rows);
   std::swap (num_columns, copy.num_columns);
   std::swap (num_bombs, copy.num_bombs);
   std::swap (grid, copy.grid);
   return *this;
}


/* EXTRA CREDIT */

void SweeperGrid::auto_open_recursive(int row, int col)
{
   // Base case
   if(at(row, col).is_covered())
   {
      uncover(row, col);
   }

   // Recursive call if cell has no bomb and cell is valid
   // Top
   if((row > 0) && (!at(row-1, col).has_bomb()) &&
      (at(row-1, col).is_covered()))
   {
      auto_open_recursive(row-1, col);
   }
   
   // Bottom
   if((row < num_rows - 1) && (!at(row+1, col).has_bomb()) &&
      (at(row+1, col).is_covered()))
   {
      auto_open_recursive(row+1, col);
   }
   
   // Left
   if((col > 0) && (!at(row, col-1).has_bomb()) &&
      (at(row, col-1).is_covered()))
   {
      auto_open_recursive(row, col-1);
   }
   
   // Right
   if((col < num_columns - 1) && (!at(row, col+1).has_bomb()) &&
      (at(row, col+1).is_covered()))
   {
      auto_open_recursive(row, col+1);
   }
   
   // Top-left
   if((row > 0) && (col > 0) && (!at(row-1, col-1).has_bomb()) &&
      (at(row-1, col-1).is_covered()))
   {
      auto_open_recursive(row-1, col-1);
   }
   
   // Top-right
   if((row > 0) && (col < num_columns - 1) && (!at(row-1, col+1).has_bomb())
      && (at(row-1, col+1).is_covered()))
   {
      auto_open_recursive(row-1, col+1);
   }
   
   // Bottom-left
   if((row < num_rows - 1) && (col > 0) && (!at(row+1, col-1).has_bomb())
      && (at(row+1, col-1).is_covered()))
   {
      auto_open_recursive(row+1, col-1);
   }
   
   // Bottom-right
   if((row < num_rows - 1) && (col < num_columns - 1) &&
      (!at(row+1, col+1).has_bomb()) && (at(row+1, col+1).is_covered()))
   {
      auto_open_recursive(row+1, col+1);
   }
}


void SweeperGrid::no_bomb(int row, int col)
{
   // if cell has bomb, remove bomb
   if(at(row,col).has_bomb())
   {
      remove_bomb(row, col);

      // place bomb in another cell
      for(int i = 0; i < num_rows; i++)
      {
	 for(int j = 0; j < num_columns; j++)
	 {
	    // place_bomb in a cell that has no bomb and adjacent number is 0
	    if((!at(i, j).has_bomb()) && (at(i, j).get_num_adjacent() == 0))
	    {
	       // the cell must not be equal to the current cell
	       if((i != row) && (j != col))
	       {
		  place_bomb(i, j);
		  return;
	       }
	    }
	 }
      }
   }
}
