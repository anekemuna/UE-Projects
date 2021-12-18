// File: document.h
// Document class function prototypes
//
// ­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 3- Editor     Date assigned: February 21, 2020
// Programmer: Munachimso Aneke      Date completed: March 3, 2020


#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <vector> // vector template definitions

class Document
{
  public:
/* Function: Document  
   Default constructor: creates an empty document   
*/
   Document();

/* Function: Document  
   Explicit Constructor: creates a document from an input stream
   Objects         Type     Movement        Name 
   ------------------------------------------------------
   input stream    istream  REC'D/P'BACK    in
*/
   Document(std::istream& in);

/* Function: load  
   Reads lines of a document from input stream
   Objects         Type     Movement        Name 
   ------------------------------------------------------
   input stream    istream  REC'D/P'BACK    in
*/
   void load(std::istream& in); 
   
/* Function: empty  
   returns true if the document is empty
   Objects         Type     Movement        Name 
   ------------------------------------------------------
   boolean result  bool     Returned
*/
   bool empty() const;

/* Function: insert 
   insert a line in front of the current line
   Objects         Type     Movement    Name 
   ------------------------------------------------------
   line to insert  string   REC'D       new_line
*/
   void insert(const std::string & new_line);

/* Function: append 
   insert a line at  the end of document
   Objects         Type     Movement    Name 
   ------------------------------------------------------
   line to append  string   REC'D       new_line
*/
   void append(const std::string & new_line);

/* Function: replace
   replaces current line with new line
   Objects           Type     Movement    Name 
   ------------------------------------------------------
   replacement line  string   REC'D       new_line
*/
   void replace(const std::string & new_line);

/* Function: erase
   erases current line with new line
*/
   void erase();

/* Function: find
   finds a target line
   Objects           Type     Movement    Name 
   ------------------------------------------------------
   target string     string   REC'D       target
   boolean result    bool     returned
*/
   bool find(const std::string & target);

/* Function: set_current
   sets current line index to n
   Objects                              Type     Movement    Name 
   ---------------------------------------------------------------
   line number of the new current line  int      REC'D       n
*/
   void set_current(int n);

/* Function: move_current
   moves current line index |n| places
   Objects                                  Type    Movement   Name 
   ----------------------------------------------------------------
   number of lines to move the current line int     REC'D      n
*/
   void move_current(int n);

/* Function: write_line
   write current line to an output stream
   Objects           Type      Movement      Name 
   ------------------------------------------------------
   Output stream     ostream   REC'D/P'BACK  out
*/
   void write_line(std::ostream & out) const;

/* Function: write_all
   writes the document
   Objects           Type      Movement      Name 
   ------------------------------------------------------
   Output stream     ostream   REC'D/P'BACK  out
*/
   void write_all(std::ostream & out) const;

   
  private:
   // Data attributes
   std::vector<std::string> lines; // vector of lines
   int curr; // index of current line
   
}; // end class document

#endif // DOCUMENT_H_
