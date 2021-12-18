// File: coder.cpp
// Huffman coding tree
//
// ----------------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 6- huffman    Date assigned: April 15, 2020
// Programmer: Munachimso Aneke      Date completed: April 27, 2020


#include <iostream>     // cin, cout, endl
#include <fstream>      // ifstream, ofstream
#include <cstdlib>      // exit()
#include <cctype>       // toupper()
#include <string>       // string definitions
#include "huffman.h"    // class HuffmanTree definitions


int main (int argc, char * argv[])
{
   using namespace std;

   // 1. Check arguments
   if (argc != 2)
   {
      cerr << "Usage: " << argv[0] << " codefile" << endl;
      exit(1);
   }

   // 2. Open input_file
   ifstream input_file (argv[1]);

   // 2.2 Check for file successful open
   if(!input_file)
   {
      cerr << "Error: Cannot open input file!" << endl;
      exit(1);
   }

   // 3. Create Huffman Tree from input file and close file

   HuffmanTree tree(input_file);
   input_file.close();

   // 4. Display tree
   cout << endl;
   tree.write(cout);
   cout << endl;

   // 5. Huffman encoding/decoding menu
   char choice; // local-variable: user's choice
   string infile_name; // local-variable: in file name
   string outfile_name;  // local-variable: out file name
   
   do
   {
      // 5.1 Display menu
      cout << "Please choose one of: " << endl << endl;
      cout << "   E - Encode a message" << endl;
      cout << "   D - Decode a message" << endl;
      cout << "   Q - Quit the program" << endl;
      cout << endl;
      
      // 5.2 Prompt for choice
      cout << "Enter your choice: ";
      cin >> choice;
      
      choice = toupper(choice); // convert choice to uppercase
      
      // 5.3 instructions for each choice
      // 5.3.1 if choice is E
      if (choice == 'E')
      {
	 // prompt for file name
	 cout << "Enter the name of a plaintext message file: ";
	 cin >> infile_name;
	 
	 // open file
	 ifstream inputfile(infile_name);
	 
	 // check if open is successful
	 if(!inputfile)
	 {
	    cerr << "Error: Cannot open inputfile" << endl << endl;
	 }
	 else
	 {
	    cout << "Enter name of output file: ";
	    cin >> outfile_name;

	    // open file
	    ofstream outputfile(outfile_name);

	    // check if file successful
	    if(!outputfile)
	    {
	       cerr << "Error: Cannot open inputfile" << endl << endl;
	    }
	    else
	    {
	       tree.encode(inputfile, outputfile); // encode
	    }
	    
	    // close file
	    outputfile.close();
	 }
	 
	 // close file
	 inputfile.close();
	 
      }
      // 5.3.2 if choice is D
      else if (choice == 'D')
      {
	 cout << "Enter the name of a compressed message file: " << endl;
	 cin >> infile_name;

	 // open file
	 ifstream inputfile(infile_name);

	 // check if open was successful
	 if(!inputfile)
	 {
	    cerr << "Error: Cannot open inputfile" << endl << endl;
	 }
	 else
	 {
	    cout << "Enter name of output file: ";
	    cin >> outfile_name;

	    // open file
	    ofstream outputfile(outfile_name);

	    // check if open was successful
	    if(!outputfile)
	    {
	       cerr << "Error: Cannot open inputfile" << endl << endl;
	    }
	    else // decode
	    {
	       tree.decode(inputfile, outputfile);
	    }
	    
	    // close files
	    outputfile.close();
	 }

	 // close files
	 inputfile.close();
	 
      }
      // 5.3.3 if choice if Q
      else if (choice != 'Q')
      {
	 cout << "Warning: Invalid choice!" << endl;
      }
   }
   while (choice != 'Q'); // keep running while not q
   
   return 0;
}
