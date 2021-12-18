// File: dnode.h
// Doubly linked-list node


#ifndef DNODE_H_
#define DNODE_H_

// This struct is intended to be used as an inner class where T has
// been defined as a type parameter.  T can also be defined before
// the header file is included.

struct Node                    
{                              
   T data;          // the data
   Node* llink;     // pointer to previous (backward, left) node
   Node* rlink;     // pointer to next (forward, right) node

   // Constructor
   Node (const T & item = T(), Node* left = nullptr, Node *right = nullptr):
      data(item), llink(left), rlink(right) {}
};

#endif  // DNODE_H_
