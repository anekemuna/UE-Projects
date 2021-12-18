// File: card.h
// Card class definitions and friend operator function prototypes
//
// -------------------------------------------------------------------
// Class: CS 215                      Instructor: Dr. Deborah Hwang
// Assignment: Project 2 -Cards       Date Assigned: February 12 2020
// Programmer: Munachimso Aneke       Date Completed: February 19 2020

#ifndef CARD_H_
#define CARD_H_

class Card
{ 
  public:    // Visible to all user  
    // Constructors
    // Default/ Explicit- value constructor
    Card (char initial_value = 'A', char initial_suit = 'C');

    // Accessors
    char value() const; // Returns the value of this card
    char suit() const;  // Returns the suit of this card
    int  numeric_value() const; // returns the numeric character
    std::string to_string() const; // returns the output eqivalent
    std::string full_name() const; // returns the full name

    // Overloaded operators as friend functions
    friend bool operator==(const Card & lhs, const Card & rhs);// true if
                                                               // lhs == rhs
    friend bool operator<(const Card & lhs, const Card & rhs);// true if
                                                              // lhs < rhs
    friend bool operator<=(const Card & lhs, const Card & rhs);// true if
                                                               // lhs <= rhs
    friend bool operator>(const Card & lhs, const Card & rhs);// true if
                                                              //lhs > rhs
    friend bool operator>=(const Card & lhs, const Card & rhs);// true if
                                                               // lhs >= rhs
    friend bool operator!=(const Card & lhs, const Card & rhs);// true if
                                                               // lhs != rhs
    // I/O
    friend std::istream & operator>>(std::istream & in_stream, // reads card 
				     Card & a_card);           //  values
    friend std::ostream & operator<<(std::ostream & out_stream,// prints card
				     const Card & a_card);     // attributes
    
  private: // Visible to only operations of the class
    // Data attributes
    char value_char, suit_char;
    
}; //end Card

#endif // CARD_H_
