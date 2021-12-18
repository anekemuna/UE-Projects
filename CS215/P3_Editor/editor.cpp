// File: editor.cpp
// Text manipulator
//
// ­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 3- Editor     Date assigned: February 21, 2020
// Programmer: Munachimso Aneke      Date completed: March 3, 2020


#include <iostream>   // cin, cout, endl
#include <fstream>    // ifstream, ofstream
#include <cstdlib>    // exit()
#include <cctype>     // toupper() 
#include <stdexcept>  // throw, try, catch
#include <string>     // string defintions
#include <vector>     // vector definitions
#include "document.h" // class document defintions

// FUNCTION PROTOTYPES

/* Function: display_menu 
   Displays command help menu
*/
void display_menu ();


int main(int argc, char * argv[])
{
   using namespace std;
   
   // 1. Check Arguments
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " inputfile" << endl;
      exit(1);
   }

   // 2. Open input file

   ifstream input_file (argv[1]);
   
   // 2.2 Check for file sucessful open
   if(!input_file)
   {
      cerr << "Error: Cannot open input file" << endl;
      exit(1);
   }

   // 3. Create document from input file

   Document text(input_file);

   // 4. Editing textfile
   
   char command; // local variable, refers to what command to be carried out
   string new_line; // local variable, new line of strings
   int n; // local variable, index no/ no of units to move
   
   do
   {
      cout << "Enter a command: "; // ask user for a command
      cin >> command;
      
      command = toupper(command);  // make command uppercase

      if(command == 'I')
      {
	 cin.ignore(); // ignore space
	 getline(cin, new_line); // get new_line
	 text.insert(new_line); // insert line
      }
      else if(command == 'A')
      {
	 cin.ignore(); // ignore space
	 getline(cin, new_line); // get new line
	 text.append(new_line); // append 
      }
      else if(command == 'R')
      {
	 cin.ignore(); // ignore space
	 getline(cin, new_line); // get new line
	 try
	 {
	    text.replace(new_line);  // replace
	 }
	 catch (const std::out_of_range & ex)
	 {
	    cout << ex.what() << endl;
	 }
      }
      else if(command == 'D')
      {
	 try
	 {
	    text.erase(); // delete line
	 }
	 catch (const std::out_of_range & ex)
	 {
	    cout << ex.what() << endl;
	 }
      }
      else if(command == 'F')
      {
	 cin.ignore();  // ignore space
	 getline(cin, new_line); // get substring
	 
	 if(!text.find(new_line))
	 {
	    cerr << "Target not found" << endl;
	 }
	 else
	 {
	    text.find(new_line);
	 }
      }
      else if(command == 'S')
      {
	 cin.ignore(); // ignore space
	 cin >> n; // new index line

	 try
	 {
	    text.set_current(n); // set new current line
	 }
	 catch (const std::out_of_range & ex)
	 {
	    cout << ex.what() << endl;
	 }
      }
      else if(command == 'M')
      {
	 cin.ignore(); // ignore space
	 cin >> n; // number of units to move

	 try
	 {
	    text.move_current(n); // move current line
	 }
	 catch (const std::out_of_range & ex)
	 {
	    cout << ex.what() << endl;
	 }
	 
      }
      else if(command == 'C')
      {
	 if(text.empty()) // if document is empty
	 {
	    cerr << "Error: Document Empty" << endl;
	 }
	 else
	 {
	    text.write_line(cout); // write current line
	 }
      }
      else if(command == 'P')
      {
	 if(text.empty()) // if document is empty
	 {
	    cerr << "Error: Document Empty" << endl;
	 }
	 else
	 {
	    text.write_all(cout); // print entire document
	 }
      }
      else if(command == 'W')
      {
	 cin.ignore(); // ignore space
	 getline(cin, new_line); // get file name

	 ofstream output_file(new_line); // create output file

	 if(!output_file) // check if file opens successfull
	 {
	    cerr << "Error: Cannot open output file" << endl;
	 }
	 else
	 {
	    text.write_all(output_file); // print to output file
	    output_file.close();
	 }
	 
      }
      else if(command == 'L')
      {
	 cin.ignore(); // ignore space
	 getline(cin, new_line); // get filename

	 ifstream input_file2(new_line); // get input file

	 if(!input_file2) // error checking
	 {
	    cerr << "Error: Cannot open input file 2" << endl;
	 }
	 else
	 {
	    text.load(input_file2); // load file
	    input_file2.close();
	 }
      }
      else if(command == 'H')
      {
	 display_menu();
      }
      else if(command == 'Q')
      {
	 cerr << "Error: Invalid command" << endl;
      }
    
   }
   while(command != 'Q');

   // 5. Close file
   input_file.close();

   return 0;
}


// FUNCTION DEFINITIONS

void display_menu ()
{
   using namespace std;
   
   cout << "This line editor can do the following commands:" << endl << endl
	<< "  I line   - insert line in front of current line" << endl
	<< "  A line   - append line to the end of document" << endl
	<< "  R line   - replace current line" << endl
	<< "  D        - delete the current line" << endl
	<< "  F target - makes line containing target current line" << endl
	<< "  S n      - set current line to nth line" << endl
	<< "  M n      - move current line n places" << endl
	<< "  C        - display current line to screen" << endl
	<< "  P        - display entire document to screen" << endl
	<< "  W file   - write document to file" << endl
	<< "  L file   - load file into this editor" << endl
	<< "  H        - display lists of command" << endl
	<< "  Q        - quit the editor (does not save changes)" << endl
	<< endl;

}
