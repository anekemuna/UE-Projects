// File: sweeper.cpp
// Minesweeper game 
//
// ------------------------------------------------------------
// Class: CS 215                        Instructor: Dr. Deborah Hwang
// Assignment: Project4- Minesweeper    Date assigned: March 2, 2020
// Programmer: Munachimso Aneke         Date completed: March 30,2020


#include <iostream>       // cin, cout, endl
#include <cstdlib>        // cerr, exit()
#include <string>         // stoi
#include <stdexcept>      // throw, out_of_range
#include <cctype>         // tolower
#include "sweepergrid.h"  // class SweeperGrid definitions
#include "sweepercell.h"  // class SweeperCell definitions

// FUNCTION PROTOTYPES

/* Function: uncover_all
   uncover all cells in grid
   Objects           Type          Movement        Name 
   ----------------------------------------------------
   game grid         SweeperGrid   REC'D/ P'BACK   grid   
*/
void uncover_all(SweeperGrid & grid);

int main(int argc, char * argv[])
{
   using namespace std;

   // 1. Check for correct number of arguements
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " row_number column_number density_number"
	   << endl;
      exit(1);
   }

   // 2. Assign arguments to variable
   int row_num = stoi(argv[1]);
   int col_num = stoi(argv[2]);
   int density = stoi(argv[3]);

   // 3. Create sweeper grid
   SweeperGrid game_grid;

   // 4. Check if arguments are valid
   // 4.1 If not valid, print out error message`
   if((row_num < 5) || (col_num < 5) || (density < 10) || (density > 50))
   {
      cerr << "Error: Invalid Arguments!\n" << endl;
   }
   // 4.2 if arguments are valid, create user specified SweeperGrid
   else 
   {
      game_grid = SweeperGrid(row_num, col_num, density);
   }

  
   // Debugging
   /* game_grid.write(cout);
   cout << endl << endl;
   uncover_all(game_grid);
   game_grid.write(cout);*/
  

   cout << "Number of bomb(s): " << game_grid.bombs() << endl;

   char command; // local variable- user's command choice
   int row,      // local variable- user's row choice    
       col;      // local variable -user's col choice
   SweeperCell check; // local variable- check if a cell with a mine
                      //                 has been uncovered
   
   do
   {
      // 5. Print out grid
      game_grid.write(cout);

      // 6. Ask user for a command
      cout << endl << "Enter u to uncover, m to mark, k to unmark, q to quit: ";
      cin >> command;

      command = tolower(command);  // make command lowercase

      // 7. if statements for each possible command
      if(command == 'u')
      {
	 cout << "Enter a location (row col) to uncover: ";
	 cin >> row >> col;
	 try
	 {
	    game_grid.uncover(row, col);  // 7.1 Uncover cell
	    
	    // if uncover is false
	    if(!game_grid.uncover(row, col))
	    {
	       cout << "You've uncovered a mine! Game over!! "
		    << "Here's the uncovered grid: " << endl << endl;
	       break;
	    }
	 }
	 catch (const std::out_of_range & ex)
	 {
	    cout << ex.what() << endl;
	 }

      }
      else if(command == 'm')
      {
	 cout << "Enter a location (row col) to mark: ";
	 cin >> row >> col;

	 try
	 {
	    game_grid.mark(row, col);  // 7.2 mark mcell
	 }
	 catch (const std::out_of_range & ex)
	 {
	    cout << ex.what() << endl;
	 }
      }
      else if(command == 'k')
      {
	 cout << "Enter a location (row col) to unmark: ";
	 cin >> row >> col;

	 try
	 {
	    game_grid.unmark(row, col);  // 7.3 Unmark cell
	 }
	 catch (const std::out_of_range & ex)
	 {
	    cout << ex.what() << endl;
	 }
      }
      else if(command == 'q')
      {
	 cout << "Sorry to see you go! Here's the uncovered grid:" << endl
	      << endl;
      }
      else
      {
	 cerr << "Error: Invalid command! Try again!" << endl << endl;
      }
   }
   while((command != 'q') &&  // 8. Game continues if the user doesn't quits
	 (!game_grid.game_won()));   //     or the game is not won
	                           //     or a mine is not uncover

   // print if game is won
   if(game_grid.game_won())
   {
      cout << "You won!!! Here's the uncovered grid:" << endl << endl;
   }

   // 9. Print out all cells of the grid uncovered

   uncover_all(game_grid);
   game_grid.write(cout);
   
   return 0;
}


// FUNCTION DEFINITION

void uncover_all(SweeperGrid & grid)
{
   for(int row = 0; row < grid.rows(); row++)
   {
      for(int col = 0; col < grid.columns(); col++)
      {
	 grid.uncover(row, col); // uncover each cell
      }
   }
}
