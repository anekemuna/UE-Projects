/* File: cards.h
 *Blackjack Game (header file)
 *
 * --------------------------------------------------------------------
 * Class: CS 210                       Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 7   Date assigned: April 16, 2019
 * Programmer: Munachimso S. Aneke     Date completed: April 30, 2019
 */

#ifndef CARDS_H
#define CARDS_H

/* Data structure: card_t
 represents the suit and value of a card
*/
typedef struct
    {
        char suit;
        int value;
    } card_t;

/* Function: card_create
 Reads a suit and a value and returns a card of type card_t
 Objects     Type    Movement  Name
 ---------------------------------------------------------
 card suit   char    Received  card_suit
 card value  int     Received  card_value
 card        card_t  Returned  card
*/
card_t card_create(char card_suit, int card_value);

/* Function: card_get_suit
 Returns the character representing the suit of the card
 Objects    Type    Movement  Name
 ---------------------------------------------------------
 card       card_t  Received  card
 card suit  char    Returned
*/
char card_get_suit(card_t card);

/* Function: card_get_value
 Returns the integer representing the value of the card
 Objects    Type    Movement  Name
 ---------------------------------------------------------
 card       card_t  Received  card
 card value char    Returned
*/
int card_get_value(card_t card);

/* Function: card_blackjack_points
 Returns blackjack game points
 Objects               Type   Movement  Name
 ---------------------------------------------------------
 card                  card_t Received  card
 blackjack game points int    Returned  game_points
*/
int card_blackjack_points(card_t card);

/* Function: card_print
 Prints description of a card
 Objects               Type   Movement  Name
 ---------------------------------------------------------
 card                  card_t Received  card
*/
void card_print(card_t card);

/* Data structure: shoe_t
 represents the number of decks in a shoe
*/
typedef struct
    {
        card_t *card_array;
        int no_decks;
        int next_card_index;
    } shoe_t;

/* Function: shoe_create
 Returns a shoe of shuffled cards
 Objects          Type    Movement  Name
 ---------------------------------------------------------
 number of decks  int     Received  no_decks
 shoe             shoe_t  Returned  shoe
*/
shoe_t shoe_create(int no_decks);

/* Function: shoe_draw_card
 returns the next card
 Objects      Type    Movement    Name
 ---------------------------------------------------------
 shoe         shoe_t  Received    shoe
 shoe         shoe_t  Passed back shoe
 next card    card_t  Returned    next_card
*/
card_t shoe_draw_card(shoe_t *shoe);

/* Function: shoe_cards_left
 returns the number of cards left
 Objects          Type    Movement    Name
 ---------------------------------------------------------
 shoe             shoe_t  Received    shoe
 no of card left  int     Returned
*/
int shoe_cards_left(shoe_t shoe);

/* Function: shoe_reshuffle
 randomizes the cards within a shoe
 Objects   Type    Movement  Name
 ---------------------------------------------------------
 shoe      shoe_t  Received     shoe
 shoe      shoe_t* Passed back  shoe
*/
void shoe_reshuffle(shoe_t *shoe);

/* Function: shoe_free
 deallocates the dynamic array in the shoe
 Objects   Type    Movement     Name
 ---------------------------------------------------------
 shoe      shoe_t  Received     shoe
 shoe      shoe_t* Passed back  shoe
*/
void shoe_free(shoe_t *shoe);

/* Data structure: hand_t
 represents the number of cards the dealer has and their value
*/
typedef struct
    {
        card_t card_array[21];
        int no_cards;
    } hand_t;

/* Function: hand_create_empty
 returns an empty hand
 Objects     Type    Movement   Name
 ---------------------------------------------------------
 empty hand  hand_t  returned   hand
*/
hand_t hand_create_empty();

/* Function: hand_print
 prints out each card in hand
 Objects   Type    Movement    Name
 ---------------------------------------------------------
 hand      hand_t  received    hand
*/
void hand_print(hand_t hand);

/* Function: hand_print_first_card
 prints out the first card in hand
 Objects   Type    Movement    Name
 ---------------------------------------------------------
 hand      hand_t  received    hand
*/
void hand_print_first_card(hand_t hand);

/* Function: hand_add_card
 prints out the first card in hand
 Objects             Type    Movement       Name
 ---------------------------------------------------------
 hand to add to      hand_t  received       hand
 hand to add to      hand_t  passed back    hand
 card to be added    card_t  received       card
*/
void hand_add_card(hand_t *hand, card_t card);

/* Function: hand_blackjack_points
 returns the blackjack game points of the hand
 Objects             Type    Movement     Name
 ---------------------------------------------------------
 hand                hand_t  received     hand
 game point of hand  int     returned     sum_points
*/
int hand_blackjack_points(hand_t hand);


#endif // CARDS_H_INCLUDED

