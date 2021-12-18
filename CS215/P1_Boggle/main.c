// File: boggle.cpp
// Boggle word checker
// ----------------------------------------------------------------
// Class: CS215                    Instructor: Dr. Deborah Hwang
// Assignment: Project 1           Date assigned: 2/3/2020
// Programmer: Munachimso Aneke    Date completed: 

#include <iostream> // cin, cout, endl
#include <fstream>  // ifstream, ofstream
#include <cstdlib>  // exit()
#include <string>   // string definitions

const int GRID_SIZE = 7; // Size of the grid with borders
const int SIZE = 5; // size of the grid without borders

struct Tile {
   char letter; // for letters
   bool used; // keep track is the letter is used or not
};

// Function Definition

/* Function: read_grid
   Reads the grid from input file into a an 2D array
   Objects          Type      Movement       Name
   -----------------------------------------------------------
   input file       ifstream  REC'D/ P'BACK  input_file
   grid of letters  Tile      P'BACK         grid
*/
void read_grid (std::ifstream & input_file,
		Tile grid[GRID_SIZE][GRID_SIZE]);

/* Function: print_grid
   Prints the 2D array into the output file
   Objects          Type      Movement       Name
   -----------------------------------------------------------
   output file      ofstream  REC'D/ P'BACK  output_file
   grid of letters  Tile      REC'D          grid
*/
void print_grid (std::ofstream & output_file,
		 Tile grid[GRID_SIZE][GRID_SIZE]);

/* Function: word_finder
   prints result
   Objects                Type      Movement       Name
   -----------------------------------------------------------
   input file             ifstream  REC'D/ P'BACK  input_file
   output file            ofstream  REC'D/P'BACK   output_file
   grid to find words in  Tile      REC'D          grid
*/
void word_finder (std::ifstream & input_file, std::ofstream & output_file,
		  Tile grid[GRID_SIZE][GRID_SIZE]);

/* Function: backtrack_recursive
   Searches for words inside the grid
   Objects                Type      Movement       Name
   -----------------------------------------------------------
   grid to find words in  Tile      REC'D          grid
   word to be found       string    REC'D          word
   no of row              int       REC'D          row
   no of col              int       REC'D          col
   if found?              bool      REC'D/P'BACK   found
   word_index             int       REC'D          word_index
*/
void backtrack_recursive (Tile grid[GRID_SIZE][GRID_SIZE], std::string word,
			  int row, int col, bool & found,
			  int word_index);


int main (int argc,     // argument count- number of arguments
	  char * argv[])  // argument vector- array of strings
{
   using namespace std;
   
   // 1.  Check for number of arguments
   if (argc != 3)
   {
      cerr << "Usage: " << argv[0] << " inputfile outputfile" <<endl;
      exit (1);
   }
   
   // 2.  Open input file
   ifstream input_file (argv[1]);
   
   // 2.1 Check input file opens
   if (!input_file)
   {
      cerr << "Cannot open file: " << argv[1] << endl;
      exit(1);
   }
   
   // 3.  Open output file
   ofstream output_file (argv[2]);
   
   // 3.1 Check output file opens
   if (!output_file)
   {
      cerr << "Cannot open file: " << argv[2] << endl;
      exit(1);
   }
						 
   // 4.  Read in input file

   Tile grid[GRID_SIZE][GRID_SIZE]; // 2D grid of "letters"

   read_grid (input_file, grid);

   // 5.  Print grid to the output file
   print_grid (output_file, grid);
   
   // 6.  Search for word and print result into outputfile
    word_finder(input_file, output_file, grid);
   
   // 7.  Close the files
   input_file.close();
   output_file.close();
						 
} // End of main


// Function Defintion

void read_grid (std::ifstream & input_file,
		Tile grid[GRID_SIZE][GRID_SIZE])
{
   int i, // no of rows
       j; // no of columns

   // Copy each character from the input file
   for (i = 1; i <= SIZE ; i++)
   {
      grid[i][0].letter = '+'; // set left border character
      
      for (j = 1; j <= SIZE; j++)
      {
	 input_file >> grid[i][j].letter;
	 grid[i][j].used = false;
      }

      grid[i][SIZE + 1].letter = '+'; // set right border character
   }
   
   // set top and bottom  border
   for (j = 0; j < GRID_SIZE; j++)
   {
      grid[0][j].letter = '+';
      grid[SIZE + 1][j].letter = '+';
   }

   /* //Debugging
    for (i = 0; i < GRID_SIZE ; i++)
   {      
      for (j = 0; j < GRID_SIZE; j++)
      {

	 std:: cout << " " << grid[i][j].letter;
      }

      std:: cout << std:: endl;
      }*/
    
}


void print_grid (std::ofstream & output_file,
		 Tile grid[GRID_SIZE][GRID_SIZE])
{
   int i, // no of rows
      j;  // no of columns

   // print each character into the output file
   for (i = 1; i <= SIZE; i++)
   {
      for (j = 1; j <= SIZE; j++)
      {
	 output_file << grid[i][j].letter;
      }
      output_file  << std::endl;
   }
}


void word_finder (std::ifstream & input_file, std::ofstream & output_file,
		  Tile grid[GRID_SIZE][GRID_SIZE])
{
   std::string word;
   bool found;
   int row, // row index
       col,  // col index
       index = 0; // word index

   
   while(input_file >> word)
   {
      found = false;
      // check each letter of the grid
      //std::cout << std::endl << word << std::endl; //debugging
      for (row = 1; (row <= SIZE) && (found == false); row++)
      {
	 for (col = 1;( col <= SIZE) && (found == false); col++)
	 {
	    // std::cout << grid[row][col].letter << " = "
	    //  << word[index] << std::endl;  // debugging
	    if (grid[row][col].letter == word[index])
	    {
	        backtrack_recursive ( grid, word, row, col, found,
				      index);
	    }
	 }
      }

	 // Print result out
	 if (found == true)
	 {output_file << word << " found" << std::endl;}
	 else 
	 {output_file << word << " not found" << std::endl;}

	 // Un-mark cells visited
	 for (row = 1; row <= SIZE; row++)
	 {
	    for (col = 1; col <= SIZE; col++)
	    {
	       grid[row][col].used = false;
	    }
	 }
   }
}

void backtrack_recursive (Tile grid[GRID_SIZE][GRID_SIZE], std::string word,
			  int row, int col, bool & found,
			  int word_index)
{
   // Base Cases:
   //  - If the word is found
   //  - If the word is not found
   //  - If the cell has been used/ a border

   // If the word is found
   if ( word_index == word.length()-1)
   {
     
      //std::cout << word_index << " = " << word.length()-1
      //        <<std::endl;  // debugging
      
      if((grid[row][col].letter == word[word.length()-1]) &&
	(grid[row][col].used == false))
      
      {
	 // std::cout << grid[row][col].letter << " = "
	 //	       << word[word.length()-1] <<std::endl; // debugging
	 found = true;
	 return;
      }
      
   }

   // If the word is not found
   if (grid[row][col].letter != word[word_index])
   {
      //std::cout << grid[row][col].letter << " != " << word[word_index]
      //	<<std::endl;  // debugging
      found = false;
      return;
   }

   // If the cell has been used/ is a border
   if ((grid[row][col].letter == '+') || (grid[row][col].used == true))
   {
      //std::cout << grid[row][col].letter << " || " << grid[row][col].used
      //	<< std::endl;  // debugging
      found = false;
      return;
   }

   // Smaller version
   grid[row][col].used = true; // mark current cell as used

   //Directions to check for the next letter if the previouse one is correct

   // left
   if(!found)
   {
      //std::cout << std::endl << "left" << std::endl;  // debugging      
      backtrack_recursive ( grid, word, row, col-1, found, word_index+1);
   }

   // right
   if(!found)
   {
      //std::cout << std::endl << "right" << std::endl; // debugging
      backtrack_recursive ( grid, word, row, col+1, found, word_index+1);    
   }

   // up
   if(!found)
   {
      //std::cout << std::endl << "up" << std::endl;  // debugging
      backtrack_recursive ( grid, word, row-1, col, found, word_index+1);
   }

   // down
   if(!found)
   {
      //std::cout << std::endl << "down" << std::endl;  // debugging
      backtrack_recursive ( grid, word, row+1, col, found, word_index+1);
   }

   // top-left
   if(!found)
   {
      //std::cout << std::endl << "top-left" << std::endl;  // debugging
      backtrack_recursive ( grid, word, row-1, col-1, found, word_index+1);
   }

   // down-left
   if(!found)
   {
      //std::cout << std::endl << "down-left" << std::endl;  // debugging
      backtrack_recursive ( grid, word, row+1, col-1, found, word_index+1);
   }

   // top-right
   if(!found)
   {
      //std::cout << std::endl << "top-right" << std::endl;  // debugging
      backtrack_recursive ( grid, word, row-1, col+1, found, word_index+1);
   }

   // down-right
   if(!found)
   {
      //std::cout << "down_right" << std::endl; // debugging
      backtrack_recursive ( grid, word, row+1, col+1, found, word_index+1);
   }

    if(!found)
   {
     grid[row][col].used = false; // unmark cell if not used
   }
}
