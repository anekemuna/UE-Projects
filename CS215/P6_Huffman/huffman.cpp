// File: huffman.cpp
// HuffmanTree class function definitions
//
// -------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 6- huffman    Date assigned: April 15, 2020
// Programmer: Munachimso Aneke      Date completed: April 27, 2020


#include <iostream>   // cout, cin, endl
#include <sstream>    // istream, ostream
#include <string>     // string definitions
#include <algorithm>  // swap
#include "huffman.h"  // HuffmanTree class


// Explicit-value Constructor
HuffmanTree::HuffmanTree(std::istream & codefile)
{
   int n; // # of lines in code file

   codefile >> n; // read in # of lines from codefile

   root = new Node; // dynamically allocate a Node
   Node * ptr;      // track ptr
   
   char letter;      // letter 
   std::string code; // code string for letter

   for (int i = 0; i < n; i++)
   {
      
      codefile >> letter; // read in letter
      codefile >> code;   // read in string

      ptr = root; // make track ptr point to root
      
      // iterate through string and create codetree
      for (int j = 0; j < code.length(); j++)
      {
	 // if 0, go to lchild
	 if(code[j] == '0')
	 {
	    // if lchild does not exist, create node
	    if (ptr->lchild == nullptr)
	    {
	       ptr->lchild = new Node;
	    }

	    // update ptr
	    ptr = ptr->lchild;
	 }
	 // if 1, go to rchild
	 else if(code[j] == '1')
	 {
	    // if rchild does not exist, create node
	    if (ptr->rchild == nullptr)
	    {
	       ptr->rchild = new Node;
	    }

	    // update ptr
	    ptr = ptr->rchild;
	 }
      }
	 // add data
	 if (letter == '%')    // if letter is %, data should be ' '
	    ptr->data = ' ';
	 else if (letter == '$') // if letter is $, data should be '\n'
	    ptr->data = '\n';
	 else
	    ptr->data = letter;
   }
}

// Copy constructor
HuffmanTree::HuffmanTree(const HuffmanTree & source)
{
   this->root = copy_tree(source.root); // copy data attribute
}

// Destructor
HuffmanTree::~HuffmanTree()
{
   delete_tree(root); // delete tree
}

void HuffmanTree::write(std::ostream & out) const
{
   int level = 0;  // first level
   
   write_tree(out, root, level); // recursively write tree
}

void HuffmanTree::decode(std::istream & message_file, std::ostream & out)
{
   Node * ptr;  // track ptr
   char ch;     // coded character

   while (message_file >> ch) // read character
   {
      ptr = root; // traverse from root

      do
      {
	 // go left
	 if (ch == '0') 
	 {
	    ptr = ptr->lchild;
	 }
	 // go right
	 else if (ch == '1') 
	 {
	    ptr = ptr->rchild;
	 }
	 
	 // debugging
	 /*else 
	 { std::cerr << "Error: Invalid Input! Input ignored!" << std::endl;}
	 */
	 
	 // while node is not a leaf node and still characters
      } while ((ptr->lchild != nullptr) && (message_file >> ch));

      out << ptr->data; // write out data
   }

   if(ptr->data != '\n') // if last character is not a new line
      out << std::endl;  //  add a new line.
   
}

void HuffmanTree::encode(std::istream & message_file, std::ostream & out)
{
   char ch; // character to be code
   std::string code, // coded character
               str;  // empty string for path_so_far
   while (message_file.get(ch))
   {
      code = char_to_code(ch, root, str); // code character
      out << code; // write out code 
   }

   out << std::endl;   // write out new line
}

HuffmanTree & HuffmanTree::operator=(const HuffmanTree & source)
 {
    // make copy of Hufffman tree
    HuffmanTree copy(source);
    // swap root with copy root
    std::swap(root, copy.root);
    // return result
    return *this;
 }

void HuffmanTree::write_tree(std::ostream & out, Node * local_root, int level)
   const
{
   // if tree is not empty()
   if (local_root != nullptr)
   {
      // write rchild
      write_tree(out, local_root->rchild, level + 1);

      // print # of ' '
      for (int i = 0; i < (8 * level); i++)
      {
	 out << " ";
      }

      // write node value
      if (local_root->data == ' ')    // if data is ' ', data should be %
	 out << "%" << std::endl;
      else if (local_root->data  == '\n') // if letter is '\n', data should be $
	 out << "$" << std::endl;
      else
	 out << local_root->data << std::endl;

      // write lchild
      write_tree(out, local_root->lchild, level + 1);    
   }
}

std::string HuffmanTree::char_to_code(char ch, Node * local_root,
				      const std::string & path_so_far)
{
   // if leaf node & leaf data value is the ch
   if ((local_root->data == ch) && (local_root->lchild == nullptr)) 
      return path_so_far;
   // if leaf node & leaf data value is not the ch
   else if ((local_root->lchild == nullptr) && (local_root->data != ch))
      return "";

   std::string str1;

   str1 = char_to_code(ch, local_root->lchild, path_so_far + "0");

   if(str1 != "")  // check left side
      return str1;
   else            // if not, check right
      return char_to_code(ch, local_root->rchild, path_so_far + "1");

}

HuffmanTree::Node * HuffmanTree::copy_tree(Node * local_root)
{
   Node * copy_root; // copy
   
   if(local_root != nullptr) // if not null
   {
      // Use pre-order: NLR
      copy_root = new Node;
      // copy data
      copy_root->data = local_root->data;
      // copy left
      copy_root->lchild = copy_tree(local_root->lchild);
      // copy right
      copy_root->rchild = copy_tree(local_root->rchild);
   }
   else // else, copy is null
   {
      copy_root = nullptr;
   }

   // return copy root
   return copy_root;
   
}

void HuffmanTree::delete_tree(Node * local_root)
{
   if (local_root != nullptr) // if tree not empty
   {
      // delete left side
      delete_tree(local_root->lchild);
      
      // delete right side
      delete_tree(local_root->rchild);
      
      //delete node
      delete local_root;
   }
}
