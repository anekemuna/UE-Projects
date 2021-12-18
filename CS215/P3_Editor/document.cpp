// File: document.cpp
// Document class function definitions
//
// ­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 3- Editor     Date assigned: February 21, 2020
// Programmer: Munachimso Aneke      Date completed: March 3, 2020

#include <iostream>   // cin, endl, cout
#include <sstream>    // istream, ostream
#include <vector>     // vector template definitions
#include <string>     // string definitions
#include <stdexcept>  // throw, out_of_range
#include "document.h" // document class


Document::Document() // Default Constructor
{
   curr = 0; // set index to 0
}

Document::Document(std::istream& in) // Explicit constructor
{
   std::string line;
   while(getline(in, line)) // read line in
   {
      lines.push_back(line); // add line to document
   }

   curr = 0; // set current line to first line
}

void Document::load (std::istream& in)
{
   std::string line;
   
   lines.clear(); // clears out document
   
   while(getline(in, line)) // read in line 
   {
      lines.push_back(line); // add line to document
   }

   curr = 0;  // set current line to first line
}

bool Document::empty() const
{
   return lines.empty(); // return true if document is empty
}

void Document::insert(const std::string & new_line)
{
   lines.push_back(""); // resize vector by placing an empty string

   for( int i = lines.size()-1; i > curr; i--)
   {
      lines[i] = lines[i - 1]; // copy previous strings into next
   }

   lines[curr] = new_line; // insert string into current line
}

void Document::append(const std::string & new_line)
{
   lines.push_back(new_line); // add string to vector
   curr = lines.size() - 1;    // setting index to current line 
}

void Document::replace(const std::string & new_line)
{
   if(lines.empty()) // if document is empty
   {
      throw std::out_of_range("Error: Document is empty");
   }
      lines[curr] = new_line; // setting current line to new_line
}

void Document::erase()
{
   if(lines.empty()) // if document is empty
   {
      throw std::out_of_range("Error: Document is Empty");
   }
   
   if(curr == lines.size()-1) // if current line is last line
   {
      curr = curr - 1;    // set current line to previous line
   }
   else
   {
      for(int i = curr; i < lines.size(); i++) 
      {
	 lines[i] = lines[i + 1]; // copy strings into previous
      }
   }
   
   lines.pop_back(); // reducing vector size by delete last line
}

bool Document::find(const std::string & target)
{
   size_t found;
   for(int i = 0; i < lines.size(); i++) // for each line
   {
      found = lines[i].find(target);
      
      if(found != std::string::npos) // if substring found
      {
	 curr = i; // set current line
	 return true; // if found
      }
   }

   return false;  // not found
}

void Document::set_current(int n)
{
   if((n < 0) || (lines.size() < n+1))
   {
      throw std::out_of_range("Error: Index out of range");
   }
   else
   {
      curr = n; // set current line to n 
   }
}

void Document::move_current(int n)
{
   if( (curr + n >= lines.size()) || (curr + n < 0)) // Check if move is valid
   {
      throw std::out_of_range("Error: Index out of range");
   }

   curr = curr + n; // move to n units
}

void Document::write_line(std::ostream & out) const
{
   if(!lines.empty())
   {
      out << lines[curr] << std::endl; // print out current line
   }
}

void Document::write_all(std::ostream & out) const
{
   for(int i = 0; i < lines.size(); i++) // for each line...
   {
      out << lines[i] << std::endl;   // ... print out line
   }
}
