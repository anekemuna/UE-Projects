// File: card.cpp
// Implementations of Card class and friend operator functions
//
// -------------------------------------------------------------------
// Class: CS 215                      Instructor: Dr. Deborah Hwang
// Assignment: Project 2 -Cards       Date Assigned: February 12 2020
// Programmer: Munachimso Aneke       Date Completed: February 19 2020

#include <iostream> // cout, endl;
#include <string>   // string definitions
#include <sstream>  // ostream, istream
#include "card.h"   // Card class

// Class Invariant
//     - The value of the suit must be either 'C','D','S', or 'H'
//     - the value of the number must be either 'A','2','3','4','5',
//                                   '6','7','8','9','T','J','Q','K'
//

/* Function: invariant_checker
   Checks if the invariant of the class is true
   Objects                      Type       Movement         Name
   -------------------------------------------------------------------------
   card value                   char       REC'D            value_char
   card suit                    char       REC'D            suit_char
   if invariant is true/false   bool       Returned
*/
bool invariant_checker (char value_char, char suit_char)
{
   // Check if value is valid
   if((value_char != 'A') && (value_char != '2') &&
      (value_char != '3') && (value_char != '4') &&
      (value_char != '5') && (value_char != '6') &&
      (value_char != '7') && (value_char != '8') &&
      (value_char != '9') && (value_char != 'T') &&
      (value_char != 'J') && (value_char != 'Q') &&
      (value_char != 'K'))
   {
      return false;
   }

   //check if suit is valid
   if((suit_char != 'C') && (suit_char != 'D') &&
      (suit_char != 'H') && (suit_char != 'S') )
   {
      return false;
   }

   return true;
}

Card::Card (char initial_value, char initial_suit) : value_char(initial_value),
						     suit_char(initial_suit)
{
   using namespace std;

   // Check if it follows class invariant
   if(!invariant_checker(initial_value, initial_suit))
   {
      value_char = 'A';
      suit_char = 'C';
      cerr << "Card value is invalid. Card reset to default" << endl;
   }

}

char Card::value() const // get value character
{
   return value_char;
}

char Card::suit() const // get suit character
{
   return suit_char;
}

int Card::numeric_value() const // gets the numeric value of the card
{
   switch (value_char) 
   {
      case 'A':
	 return 1;
	 break;
      case '2':
	 return 2;
	 break;
      case '3':
	 return 3;
	 break;
      case '4':
	 return 4;
	 break;
      case '5':
	 return 5;
	 break;
      case '6':
	 return 6;
	 break;
      case '7':
	 return 7;
	 break;
      case '8':
	 return 8;
	 break;
      case '9':
	 return 9;
	 break;
      case 'T':
	 return 10;
	 break;
      case 'J':
	 return 11;
	 break;
      case 'Q':
	 return 12;
	 break;
      case 'K':
	 return 13;
	 break;
      default:
	 return 0;
   }

 
}

std::string Card::to_string() const // returns the output in the form VS
{
   std::string str_value,
               str_suit,
               str_result;

   switch (value_char) // get the character representation of the value
   {
      case 'A':
	 str_value = "A";
	 break;
      case '2': 
	 str_value = "2";
	 break;
      case '3':
	 str_value = "3";
	 break;
      case '4':
	 str_value = "4";
	 break;
      case '5':
	 str_value = "5";
	 break;
      case '6':
         str_value = "6";
	 break;
      case '7':
	 str_value = "7";
	 break;
      case '8':
	 str_value = "8";
	 break;
      case '9':
         str_value = "9";
	 break;
      case 'T':
	 str_value = "T";
	 break;
      case 'J':
	 str_value = "J";
	 break;
      case 'Q':
	 str_value = "Q";
	 break;
      case 'K':
	 str_value = "K";
	 break;
	 
   }

   switch(suit_char)
   {
      case 'C':
	 str_suit = "C";
	 break;
      case 'D':
	 str_suit = "D";
	 break;
      case 'H':
	 str_suit = "H";
	 break;
      case 'S':
	 str_suit = "S";
	 break;
   }

   str_result = str_value + str_suit; //concatenate the strings

   return str_result;
}

std::string Card::full_name() const // print out the full name of the card 
{
   std::string str_value,
               str_suit,
               str_result;

   switch (value_char)  // get the name of the value
   {
      case 'A':
	 str_value = "Ace";
	 break;
      case '2': 
	 str_value = "Two";
	 break;
      case '3':
	 str_value = "Three";
	 break;
      case '4':
	 str_value = "Four";
	 break;
      case '5':
	 str_value = "Five";
	 break;
      case '6':
         str_value = "Six";
	 break;
      case '7':
	 str_value = "Seven";
	 break;
      case '8':
	 str_value = "Eight";
	 break;
      case '9':
         str_value = "Nine";
	 break;
      case 'T':
	 str_value = "Ten";
	 break;
      case 'J':
	 str_value = "Jack";
	 break;
      case 'Q':
	 str_value = "Queen";
	 break;
      case 'K':
	 str_value = "King";
	 break;
	 
   }

   switch(suit_char)  // get the name of the suit
   {
      case 'C':
	 str_suit = " of Clubs";
	 break;
      case 'D':
	 str_suit = " of Diamonds";
	 break;
      case 'H':
	 str_suit = " of Hearts";
	 break;
      case 'S':
	 str_suit = " of Spades";
	 break;
   }

   str_result = str_value + str_suit; // concatenate the strings

   return str_result;
}

bool operator==(const Card & lhs, const Card & rhs) // true if lhs == rhs
{
   return ((lhs.value_char == rhs.value_char) &&
	   (lhs.suit_char == rhs.suit_char));
}

bool operator<(const Card & lhs, const Card & rhs) // true if lhs < rhs
{
   if (lhs.numeric_value() < rhs.numeric_value())
   {
      return true;
   }
   else if (lhs.numeric_value() > rhs.numeric_value())
   {
      return false;
   }
   else
   {
      if( lhs.suit_char < rhs.suit_char)
      {
	 return true;
      }
      else
      {
	 return false;
      }
   }
}


bool operator<=(const Card & lhs, const Card & rhs) // true if lhs <= rhs
{
   if ((lhs == rhs) || (lhs < rhs))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool operator>(const Card & lhs, const Card & rhs) // true if lhs > rhs
{
   if((lhs == rhs) || (lhs < rhs))
   {
      return false;
   }
   else
   {
      return true;
   }
}

bool operator>=(const Card & lhs, const Card & rhs) // true if lhs >= rhs
{
   if ((lhs < rhs))
   {
      return false;
   }
   else
   {
      return true;
   }
}

bool operator!=(const Card & lhs, const Card & rhs) // true if lhs != rhs
{
   if (!(lhs == rhs))
   {
      return true;
   }
   else
   {
      return false;
   }
}


std::istream & operator>>(std::istream & in_stream, // read in card type   
			  Card & a_card)            //  variables
{
   std::string word;  // Local data variable 
   
   in_stream >> word; // Read in data into local variables

   if(!in_stream) // check if stream input is valid
   {
      return in_stream;
   }

   if(word.length() != 2) // Check if number of characters is valid
   {
      in_stream.setstate(std::ios::failbit);
      return in_stream;
   }
   
  
   if(!invariant_checker(word[0], word[1])) // check invariant is true
   {
      in_stream.setstate(std::ios::failbit);
      return in_stream;
   }

   // if input valid set data attributes
   a_card.value_char = word[0];
   a_card.suit_char = word[1];
   
   return in_stream;
}

std::ostream & operator<<(std::ostream & out_stream, // print out card type
			  const Card & a_card)       //  variables
{
   out_stream << a_card.value_char << a_card.suit_char;
   return out_stream;
}
