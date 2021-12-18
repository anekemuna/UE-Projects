// File: concordance.cpp
// concordance creation program
//
// ----------------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 7a- concord   Date assigned: April 27, 2020
// Programmer: Munachimso Aneke      Date completed: May 4, 2020

#include <iostream>  // cin, cout, endl
#include <cstdlib>   // exit()
#include <fstream>   // ifstream, ofstream
#include <vector>    // vectors definition
#include <list>      // list definition
#include <string>    // string definition
#include <algorithm> // find


/** FUNCTION PROTOTYPES **/

/* Function: insert_word
   inserts word into list
   Objects                         Type      Movement       Name
   ------------------------------------------------------------------
   list for word to be inserted    list     P'BACK/ REC'D   l_string
   word to insert                  string   REC'D           word
*/
void insert_word (std::list <std::string> & l_string, std::string word);

/* Function: print_vector_list
   prints of each list in the vector
   Objects                         Type      Movement       Name
   ------------------------------------------------------------------
   vector of list strings          vector    REC'D          v_list
   output stream                   ostream   P'BACK/ REC'D  out
*/
void print_vector_list (const std::vector <std::list <std::string> > v_list,
			std::ostream & out);


int main (int argc, char * argv[])
{
   using namespace std;

   // 1. Checking arguments   
   if (argc != 3)
   {
      cerr << "Usage: " << argv[0] << " inputfile" << " outputfile" << endl;
      exit(1);   
   }

   // 2. Open input file  
   ifstream input_file (argv[1]);

   // 2.1 Check for file sucessful open
   if (!input_file)
   {
      cerr << "Error: Cannot open input file!" << endl;
      exit(1);
   }

   // 3. Open output file
   ofstream output_file (argv[2]);

   // 3.1 Check for file sucessful open
   if (!output_file)
   {
      cerr << "Error: Cannot open output file!" << endl;
      exit(1);
   }
   
   // 4. Read in data from input file
   
   string word;   // word from input file
   vector <list <string> > v_list (26); // vectors of list
   int i;       // index
   while (input_file >> word)
   {
      i = word[0] - 'a';  // calculate the index using ASCII
      insert_word(v_list[i], word);
      
   }
   print_vector_list(v_list, output_file);
   
   // Close files
   input_file.close();
   output_file.close();
   
   return 0;
}


/** FUNCTION DEFINITIONS **/
void insert_word (std::list <std::string> & l_string, std::string word)
{
   // check if list is not empty

   if(!l_string.empty())
   {
      // Check if word exists in list

      // Create a list iterator
      std::list <std::string>::iterator it;

      // go through list
      for (it = l_string.begin(); it != l_string.end(); it++)
      {
	 if (*it == word) // of word exist, break loop
	 {
	    return;
	 }
	 else if (*it > word) // if it is bigger add word before
	 {
	    l_string.insert(it, word);
	    return;
	 }
      }
      
      if ( it == l_string.end()) // if word does not exist
      {
	 l_string.push_back(word); // add word
      }
      
   }
   else // if list is empty
   {
      l_string.push_back(word); // add word
   }
}


void print_vector_list (const std::vector <std::list <std::string> > v_list,
			std::ostream & out)
{
   for (int i = 0; i < v_list.size(); i++) // for each list in the vector
   {
      if(!v_list[i].empty()) // for each element in the list
      {
	 for (auto j = v_list[i].begin(); j != v_list[i].end(); j++)
	 {
	    out << *j << std::endl;
	 }
      }
   }
}
