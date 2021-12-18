// File: huffman.h
// HuffmanTree class function prototypes
//
// -------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment: Project 6- Huffman    Date assigned: April 15, 2020
// Programmer: Munachimso Aneke      Date completed: April 27, 2020

#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_


class HuffmanTree
{
  private:
   // Node struct definition
   struct Node
   {
      // Data Attributes for Node struct
      char data;     // letter
      Node * lchild; // link to left child
      Node * rchild; // link to right child

      /* Function: Node
	 Explicit-value Constructor: initializes the atrributes of the struct
	 
	 Default
	 Objects             Argument      Type     Movement     Name
	 ---------------------------------------------------------------------
	 letter              '*'          char     REC'D        initial_letter
	 link to left child   nullptr     Node *   REC'D        initial_lchild
	 link to right child  nullptr     Node *   REC'D        initial_rchild
      */      
      Node (const char& initial_letter = '*', Node * initial_lchild = nullptr,
	    Node * initial_rchild = nullptr): data(initial_letter),
	 lchild(initial_lchild), rchild(initial_rchild) {}
   };
   
   // Attribute declarations
   Node * root; // pointer to the root
   
  public:
   // Operation prototypes
   
   /* Function: HuffmanTree
      Explicit-value constructor: builds the codetree from an input stream
                                   connected to a codefile

      Objects                                Type     Movement      Name
      ---------------------------------------------------------------------
      input stream connected to codefile   istream   REC'D/ P'BACK  codefile
   */
   HuffmanTree(std::istream & codefile);

   /* Function: HuffmanTree
      Copy Constructor: creates a copy of source HuffmanTree
      Objects           Type          Movement    Name
      -------------------------------------------------------
      original tree     HuffmanTree   REC'D       Source
   */
   HuffmanTree(const HuffmanTree & source);

   /* Function: ~HuffmanTree
      delete all HuffmanTree nodes 
   */
   ~HuffmanTree();
   
   /* Function: write
      writes out the codetree "sideways" to an output stream
      Objects           Type       Movement       Name
      ----------------------------------------------------
      output stream     ostream    REC'D/ P'BACK  out
   */
   void write(std::ostream & out) const;

   /* Function: decode
      decodes message from input stream, writes result to output stream
      Objects           Type       Movement        Name
      -----------------------------------------------------------
      input stream      istream    REC'D/ P'BACK   message_file
      output stream     ostream    REC'D/ P'BACK   out
   */
   void decode(std::istream & message_file, std::ostream & out);

   /* Function: encode
      encodes message from input stream, writes result to output stream
      Objects           Type       Movement        Name
      ----------------------------------------------------
      input stream      istream    REC'D/ P'BACK   message_file
      output stream     ostream    REC'D/ P'BACK   out
   */
   void encode(std::istream & message_file, std::ostream & out);

   /* Function: operator=
      assigment operator
      Objects             Type             Movement    Name
      -------------------------------------------------------
      original tree       HuffmanTree     REC'D        source
      this tree           HuffmanTree &   returned     *this
   */
   HuffmanTree & operator=(const HuffmanTree & source);


  private:
   // Helper function prototypes

   /* Function: write_tree
      recursively write out a (sub)tree to an output stream using RNL traversal
      Objects                 Type       Movement       Name
      -------------------------------------------------------
      output stream           ostream    REC'D/ P'BACK  out
      root of tree to write   Node *     REC'D          local_root
      level of node           int        REC'D          level
   */
   void write_tree(std::ostream & out, Node * local_root, int level) const;

   /* Function: char_to_code
      recursively find an encoding from the codetree
      Objects                         Type     Movement   Name
      ---------------------------------------------------------------
      char to encode                  char     REC'D      ch
      Node of tree being traversed    Node *   REC'D      local_root
      path constructed so far         string   REC'D      path_so_far
      encoding for character          string   returned   code
   */
   std::string char_to_code(char ch, Node * local_root,
			    const std::string & path_so_far);

   /* Function: copy_tree
      recursively copies a binary tree, returns a pointer to root of the copy
      Objects                 Type       Movement      Name
      -------------------------------------------------------
      root of source tree     Node *     REC'D         local_root
      root of copy            Node *     returned      copy_root
   */
   Node * copy_tree(Node * local_root);

   /* Function: delete_tree
      recursively deletes binary tree nodes
      Objects                 Type       Movement      Name
      ------------------------------------------------------------
      root of source tree     Node *     REC'D         local_root
   */
   void delete_tree(Node * local_root);
};

#endif // HUFFMANTREE_H_
