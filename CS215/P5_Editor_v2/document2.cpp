// File: document2.cpp
// Document class function definitions
//
// -------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 5- Editor2    Date assigned: March 30, 2020
// Programmer: Munachimso Aneke      Date completed: April 15, 2020

#include <iostream>    // cin, cout, endl
#include <string>      // string definitions
#include <algorithm>   // swap
#include <stdexcept>   // throw, out_of_range
#include "document2.h" // document class


// Default Constructor
Document::Document ()
{
   headPtr = new Node;   // allocate Node
   headPtr->llink = headPtr; // llink point to header
   headPtr->rlink = headPtr; // rlink point to header
   currentPtr = headPtr; // current point to header node
}

// Explicit-value Constructor 
Document::Document (std::istream & inputStream)
{
   headPtr = new Node;   // allocate Node
   headPtr->llink = headPtr; // llink point to header
   headPtr->rlink = headPtr; // rlink point to header
   currentPtr = headPtr; // current point to header node

   std::string line;

   while( getline(inputStream, line)) // read in line
   {
      append(line); // add line
   }

   currentPtr = headPtr->rlink; // current points to first line

}

// Copy Constructor
Document::Document (const Document & source)
{
   using namespace std;
   
   // allocate new node
   headPtr = new Node;   // allocate Node
   headPtr->llink = headPtr; // llink point to header
   headPtr->rlink = headPtr; // rlink point to header
   currentPtr = headPtr; // current point to header node
   
   Node * ptr = source.headPtr->rlink;
   Node * ptr2 = headPtr;
   Node * ptr3;
   
   // copy the source list into the this list
   while(ptr != source.headPtr) // loop control variable
   {
      ptr3 = new Node;
      ptr3->data = ptr->data;
      ptr3->llink = ptr2;
      ptr3->rlink = headPtr;
      ptr2->rlink = ptr3;
      
      // make current point to source current point
      if(ptr == source.currentPtr)
      {
   	 currentPtr = ptr3;
      }
      
      ptr = ptr->rlink;   // update statement 1
      ptr2 = ptr2->rlink; // update statement 2

   }
   headPtr->llink = ptr3;

   // // using append
   // while(ptr != source.headPtr)
   // {
   //    append(ptr->data);
   //    ptr = ptr->rlink;  // update statement
   // }
   // ** currentptr not set
}

// Destructor
Document::~Document ()
{
   // deallocate pointers
   Node * del_ptr = headPtr->rlink;
   while(del_ptr != headPtr)
   {
      Node * ptr = del_ptr->rlink;
      delete del_ptr; // delete
      del_ptr = ptr; // update statement
   }
   
   delete headPtr;
}

void Document::load(std::istream & inputStream)
{   
   // delete previous lines
   Node * del_ptr = headPtr->rlink;
   while(del_ptr != headPtr)
   {
      Node * ptr = del_ptr->rlink;
      delete del_ptr; // delete
      del_ptr = ptr; // update statement
   }

   // set head pointer rlink and llink
   headPtr->llink = headPtr; // llink point to header
   headPtr->rlink = headPtr; // rlink point to header

   std::string line;
   while( getline(inputStream, line))
   {
      append(line);
   }

   currentPtr = headPtr->rlink; // current points to first line    
}

bool Document::empty() const
{
   return (headPtr->rlink == headPtr);
}

void Document::insert(const std::string & new_line)
{
   Node * ptr = new Node;
   
   // copy new line into node pointer
   ptr->data = new_line;

   // set llink & rlink of ptr
   ptr->llink = currentPtr->llink;// make llink point to prev node
   ptr->rlink = currentPtr;   // make rlink point to next node
      
   // make the rlink of the prev node point to the new line
   currentPtr->llink->rlink = ptr; 

   // make the llink of the next node point to the new line
   currentPtr->llink = ptr;

   // set current pointer to new line
   currentPtr = ptr;
}
  
void Document::append(const std::string & new_line)
{
   Node * ptr = new Node;

   // copy new line into node pointer
   ptr->data = new_line;

   // set llink & rlink of ptr
   ptr->llink = headPtr->llink; // make llink point to prev node
   ptr->rlink = headPtr;        // make rlink point to next node

   // make the rlink of the prev node point to the new line
   headPtr->llink->rlink = ptr;
   
   // make the llink of the next node point to the new line
   headPtr->llink = ptr;
   
   // make current line point to last line
   currentPtr = ptr; 
}
  
void Document::replace(const std::string & new_line)
{
   // exeception if document is empty
   if(empty())
      throw std::out_of_range("Error: Document is empty!");
   else
      // replace current line with new_line
      currentPtr->data = new_line;
}
   
void Document::erase()
{
   // exeception if document is empty
   if(empty())
      throw std::out_of_range("Error: Document is empty!");
   else
   {
      // erase current line
      
      Node * ptr = currentPtr;
      
      // set prev rlink to next node & next llink node to prev
      ptr->llink->rlink = ptr->rlink;
      ptr->rlink->llink = ptr->llink;
	 
      // if current line is last line
      if(currentPtr->rlink == headPtr)
      {
	 currentPtr = currentPtr->llink;
      }
      else
      {
	 currentPtr = currentPtr->rlink;
      }

      delete ptr;
   }
}

bool Document::find(const std::string & target)
{
   size_t found;
   Node * ptr = headPtr->rlink;
   
   while (ptr != headPtr)
   {
      // search for target
      found = ptr->data.find(target);
      
      if (found != std::string::npos) // if target substring is found
      {
	 // set current to the pointer with substring
	 currentPtr = ptr;
	 return true;
      }

      ptr = ptr->rlink; // update statement
   }

   return false;  // if target not found
}
  
void Document::set_current(int n)
{
   // Count lines in document
   Node * ptr = headPtr->rlink;
   int count = 0;
   
   while(ptr != headPtr)
   {
      count++;
      ptr = ptr->rlink; // update statement
   }
   
   // Exception if n < 0 or document size < n+1
   if (n < 0 || n >= count)
      throw std::out_of_range("Error: Index out of range!");
   else
   {
      // after while loop, ptr = headPtr so create new ptr
      Node * ptr2 = headPtr->rlink;
      
      for (int i = 0; i < n; i++)
      {
	 ptr2 = ptr2->rlink; // update ptr
      }
      currentPtr = ptr2;
   }
}   
  
void Document::move_current(int n)
{
   Node * ptr = headPtr->rlink;
   int count = 0;

   // count # of lines in document
   while(ptr != headPtr)  
   {
      count++;
      ptr = ptr->rlink; // update statement
   }
   
   Node * ptr2 = headPtr->rlink;
   int track_curr = 0;

   // track current position
   while(ptr2 != currentPtr)  
   {
      track_curr++;
      ptr2 = ptr2->rlink; // update statement
   }

   Node * ptr3 = currentPtr;
   
   // Exception not n is not a valid move
   if ((track_curr + n  >= count) || (track_curr + n < 0))
      throw std::out_of_range("Error: Index out of range!");
   else
   {
      if(n > 0) // if n greater than 0, move n places forward
      {
	 for (int i = 0; i < n; i++)
	    ptr3 = ptr3->rlink;

	 currentPtr = ptr3;
      }
      else if (n < 0) // if n less than 0, move n places backward
      {
	 for (int i = 0; i > n; i--)
	    ptr3 = ptr3->llink;

	 currentPtr = ptr3;
      }
   }
}   
   
void Document::write_line(std::ostream & out) const
{
   if(!empty())
      out << currentPtr->data << std::endl; // print out current line
}

void Document::write_all(std::ostream & out) const
{
   Node * ptr = headPtr->rlink;
   
   while ( ptr != headPtr) // for all lines
   {
      out << ptr->data << std::endl; // print out line
      ptr = ptr->rlink;  // update statement
   }
}

Document & Document::operator=(const Document & source)
{
   // make copy of source
   Document copy(source);

   // swap contents of this objects using swap algorithm
   std::swap (headPtr, copy.headPtr);
   std::swap (currentPtr, copy.currentPtr);
   
   // return object
   return *this;
}

