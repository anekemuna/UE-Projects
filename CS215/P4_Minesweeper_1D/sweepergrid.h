// File: sweepergrid.h
// Sweepergrid class function prototypes
//
// ------------------------------------------------------------
// Class: CS 215                        Instructor: Dr. Deborah Hwang
// Assignment: Project4- Minesweeper    Date assigned: March 2, 2020
// Programmer: Munachimso Aneke         Date completed: March 20, 2020

#ifndef GRID_H_
#define GRID_H_

#include "sweepercell.h" // SweeperCell class

class SweeperGrid
{
  public:

   // Constructors
   /* Function: SweeperGrid
      constructor of class sweepergrid
      Objects            Default   Type    Movement   Name 
      ----------------------------------------------------------
      no of rows         5         int     REC'D      initial_rows
      no of columns      5         int     REC'D      initial_cols
      density percentage 10        int     REC'D      density
   */
   SweeperGrid(int initial_rows = 5, int initial_cols = 5,
	       int density =  10);

   // Copy Constructors
   /* Function: SweeperGrid
      creates a new SweeperGrid- identical to existing one
      Objects                    Type         Movement    Name 
      ----------------------------------------------------------
      source SweeperGrid object  SweeperGrid  REC'D       source
   */
   SweeperGrid (const SweeperGrid & source);

   // Destructors
   /* Function: ~SweeperGrid
      deallocates the grid array
   */
   ~SweeperGrid();
   
   // Accessors
   /* Function: rows
      returns the number of rows in the grid
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      no of rows        int       returned      num_rows
   */
   int rows() const;

   /* Function: columns
      returns the number of columns in the grid
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      no of columns     int       returned      num_columns
   */
   int columns() const;

   /* Function: bombs
      returns the number of bombs in the grid
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      no of bombs       int       returned      num_bombs
   */
   int bombs() const;

   // Mutators
   /* Function: place_bomb
      place a bomb in grid cell at location (row, col)
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      row index         int       REC'D         row
      column index      int       REC'D         col
   */
   void place_bomb(int row, int col);

   /* Function: remove_bomb
      remove a bomb from grid cell at location (row, col)
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      row index         int       REC'D         row
      column index      int       REC'D         col
   */
   void remove_bomb(int row, int col);

   /* Function: uncover
      uncovers grid cell at location (row, col)
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      row index         int       REC'D         row
      column index      int       REC'D         col
      bomb check        bool      Returned    
   */
   bool uncover(int row, int col);

   /* Function: mark
      marks the grid cell at location(row, col)
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      row index         int       REC'D         row
      column index      int       REC'D         col
   */
   void mark(int row, int col);

   /* Function: unmark
      unmarks grid cell at location(row, col)
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      row index         int       REC'D         row
      column index      int       REC'D         col
   */
   void unmark(int row, int col);

    /* Function: write
      prints the SweeperGrid in a 2D grid to an output stream
      Objects           Type      Movement        Name 
      ------------------------------------------------------
     output stream      ostream   REC'D/ P'BACK   out
   */
   void write(std::ostream & out) const;

    /* Function: game_won
      returns true if the game has been won
      Objects           Type      Movement      Name 
      ------------------------------------------------------
      win result        bool      Returned
   */
   bool game_won();

   /* Function: operator=
      overloaded assignment operator
      Objects                    Type           Movement    Name 
      ---------------------------------------------------------
      source SweeperGrid object  SweeperGrid    REC'D      source
      this document              SweeperGrid&   REC'D      *this
   */
   SweeperGrid & operator= (const SweeperGrid & source);
   
   
  private:
   // Data Attributes
   int num_rows,   // number of rows
      num_columns, // number of columns
      num_bombs;   // number of bombs in the grid
   
   SweeperCell* grid; // pointer to grid

   // Helper Function
   
   /* Function: at
      returns a  reference to the sweeperCell
      Objects                 Type          Movement      Name 
      ------------------------------------------------------
      row index               int           received      row
      column index            int           received      col
      reference to the cell   SweeperCell&  returned
      at logical location
      grid[r][c]
   */
   SweeperCell& at(int row, int col);

   const SweeperCell& at(int row, int col) const;
   
}; // end class SweeperGrid

#endif // GRID_H_

