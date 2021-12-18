// File: carddriver.cpp
// Testing Card class definitions and implementation
//
// -------------------------------------------------------------------
// Class: CS 215                      Instructor: Dr. Deborah Hwang
// Assignment: Project 2 -Cards       Date Assigned: February 12 2020
// Programmer: Munachimso Aneke       Date Completed: February 19 2020

#include <iostream> // cin, cout, endl
#include <string>   // string definitions
#include "card.h"  // card class

int main()
{
   using namespace std;
   
   Card c1; // default value
   // Testing value(), suit(), to_string(), full_name(), numeric_value()
   cout << "c1's value character is: " << c1.value() << endl
	<< "c1's suit character is: "  << c1.suit() << endl
	<< "c1's numeric value is: "   << c1.numeric_value() << endl
	<< "c1's is a card " << c1.to_string() << endl
	<< "c1's is a/an " << c1.full_name() << endl << endl;
   
   Card c2 ('D','C'); // Invalid card
   // Testing value(), suit(), to_string(), full_name(), numeric_value()
   cout << "c2's value character is: " << c2.value() << endl
	<< "c2's suit character is: "  << c2.suit() << endl
	<< "c2's numeric value is: "   << c2.numeric_value() << endl
	<< "c2's is a card " << c2.to_string() << endl
	<< "c2's is a/an " << c2.full_name() << endl << endl;

   Card c3 ('K','S'); // valid card
   // Testing value(), suit(), to_string(), full_name(), numeric_value()
    cout << "c3's value character is: " << c3.value() << endl
	<< "c3's suit character is: "  << c3.suit() << endl
	<< "c3's numeric value is: "   << c3.numeric_value() << endl
	<< "c3's is a card " << c3.to_string() << endl
	<< "c3's is a/an " << c3.full_name() << endl << endl;

    // Testing boolean operators
    // ==
    if (c1 == c2)
    {
       cout << c1.to_string() << " == " << c2.to_string() << endl;
    }

    if ( c1 == c3)
    {
       cout << c1.to_string() << " == " << c3.to_string() << endl;
    }

    // < 
    if (c1 < c2)
    {
       cout << c1.to_string() << " < " << c2.to_string() << endl;
    }

    if ( c1 < c3)
    {
       cout << c1.to_string() << " < " << c3.to_string() << endl;
    }

    // <=
    if (c1 <= c2)
    {
       cout << c1.to_string() << " <= " << c2.to_string() << endl;
    }

    if ( c1 <= c3)
    {
       cout << c1.to_string() << " <= " << c3.to_string() << endl;
    }

    // >
     if (c1 > c2)
    {
       cout << c1.to_string() << " > " << c2.to_string() << endl;
    }

    if ( c3 > c1)
    {
       cout << c3.to_string() << " > " << c1.to_string() << endl;
    }

    // >=
    if (c1 >= c2)
    {
       cout << c1.to_string() << " >= " << c2.to_string() << endl;
    }

    if ( c3 > c1)
    {
       cout << c3.to_string() << " >= " << c1.to_string() << endl;
    }

    // !=
    if (c1 != c2)
    {
       cout << c1.to_string() << " != " << c2.to_string() << endl;
    }

    if ( c3 != c1)
    {
       cout << c3.to_string() << " != " << c1.to_string() << endl << endl;
    }

    // Testing ostream and istream
    Card c4;

    cout << "Enter a value and suit character in the form VS: ";
    cin >> c4;

    cout << "c4 = " << c4 << endl << endl;

    // Testing all functions together

    Card c5 ('7','H'), c6;

    cout << "TESTING ALL FUNCTIONS ...." << endl << endl;
    cout << "Enter a value and a suit character in the form VS: ";
    cin >> c6;

    cout << "c6's value character is: " << c6.value() << endl
	 << "c6's suit character is: "  << c6.suit() << endl
	 << "c6's numeric value is: "   << c6.numeric_value() << endl
	 << "c6's is a card " << c6.to_string() << endl
	 << "c6's is a/an " << c6.full_name() << endl << endl;

    cout << "c5 is " << c5 << " which is a " << c5.full_name() << endl << endl;

    if (c5 == c6)
    {
       cout << c5 << " == " << c6 << endl;
    }
    if (c5 != c6)
    {
       cout << c5 << " != " << c6 << endl;
    }
    if (c5 < c6)
    {
       cout << c5 << " < " << c6 << endl;
    }
    if (c5 <= c6)
    {
       cout << c5 << " <= " << c6 << endl;
    }
    if (c5 > c6)
    {
       cout << c5 << " > " << c6 << endl;
    }
    if (c5 >= c6)
    {
       cout << c5 << " >= " << c6 << endl;
    }
   
    
   
}
