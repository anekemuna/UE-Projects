// File: document2.h
// Document class function prototypes
//
// -------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 5- Editor2    Date assigned: March 30, 2020
// Programmer: Munachimso Aneke      Date completed: April 11, 2020


#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>    // string definitions

class Document
{
  private:
   typedef std::string T; // set parameter T for Node struct
   #include "dnode.h"     // doubly-linked Node struct definition

   // Attribute declarations
   Node * headPtr; // pointer to header node of a list of lines
   Node * currentPtr;  // pointer to current line

  public:
   // Operation prototypes

   /* Function: Document
      Default constructor: creates an empty document
   */
   Document ();

   /* Function: Document
      Explicit-value Constructor: creates a document from an input stream
      Objects         Type     Movement        Name
      ----------------------------------------------------
      input stream    istream  REC'D/P'BACK    inputStream
   */
   Document (std::istream & inputStream);

   /* Function: Document
      Copy Constructor: creates a copy of source document
      Objects           Type       Movement    Name
      ----------------------------------------------------
      Source document   Document   REC'D       Source
   */
   Document (const Document & source);
   
   /* Function: ~Document
      Destructor: deallocates documents node
   */
   ~Document ();
   
   /* Function: load  
      Reads lines of a document from input stream
      Objects         Type     Movement        Name 
      ------------------------------------------------------
      input stream    istream  REC'D/P'BACK    inputStream
   */
   void load(std::istream & inputStream);

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
      line to insert  string   REC'D       new_line
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
      removes the current line from document
   */
   void erase();

   /* Function: find
      finds the first line containing target string
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

   /* Function: operator=
      overloaded assignment operator function
      Objects            Type         Movement    Name 
      ------------------------------------------------------
      source document    Document     REC'D      source
      this document      Document &   returned   *this
   */
   Document & operator=(const Document & source);
   
};

#endif // DOCUMENT_H_
