/* File: cards.c
 *Blackjack Game (source file)
 *
 * --------------------------------------------------------------------
 * Class: CS 210                       Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 7   Date assigned: April 16, 2019
 * Programmer: Munachimso S. Aneke     Date completed: April 30, 2019
 */

#include <stdio.h> //printf, scanf
#include <stdlib.h>
#include <ctype.h> //toupper
#include <string.h>

#include "cards.h"


card_t card_create(char card_suit, int card_value)
{
    card_t card; //local variable- returned: a single card

    card_suit = toupper(card_suit);

    switch(card_suit)
    {
    case 'S':
    case 'H':
    case 'D':
    case 'C':
        card.suit = card_suit;
        break;
    default:
        card.suit = 'C';
        break;
    }

    if (card_value >= 1 && card_value <= 13)
    {
        card.value = card_value;
    }
    else
    {
        card.value = 2;
    }

    return card;
}

char card_get_suit(card_t card)
{
    return card.suit;
}

int card_get_value(card_t card)
{
    return card.value;
}

int card_blackjack_points(card_t card)
{
    int game_points; //local variable- returned: number of blackjack
                     // game points

    if(card.value >= 1 && card.value <= 10)
    {
        game_points = card.value;
    }
    else
    {
        game_points = 10;
    }

    return game_points;
}

void card_print(card_t card)
{
    char suit_name[20]; //local variable: number name of suit

    switch(card.suit)
    {
    case 'S':
        strcpy(suit_name, "Spades");
        break;
    case 'H':
        strcpy(suit_name, "Hearts");
        break;
    case 'D':
        strcpy(suit_name, "Diamonds");
        break;
    case 'C':
        strcpy(suit_name, "Clubs");
        break;
    default:
        break;
    }

    if(card.value == 13)
    {
        printf("King of %s", suit_name);
    }
    else if(card.value == 12)
    {
        printf("Queen of %s", suit_name);
    }
    else if(card.value == 11)
    {
        printf("Jack of %s", suit_name);
    }
    else if(card.value == 1)
    {
        printf("Ace of %s", suit_name);
    }
    else
    {
        printf("%d of %s", card.value, suit_name);
    }
}

shoe_t shoe_create(int no_decks)
{
    shoe_t shoe; //local variable- output: one shoe
    int i, //loop control variable
        j, //loop control variable
        k, //loop control variable
        l, //loop control variable
        m, //loop control variable
        n; //loop control variable

    shoe.no_decks = no_decks;
    shoe.card_array = (card_t *)calloc ((shoe.no_decks * 52),
                                        sizeof(card_t));

    for(i = 0; i < shoe.no_decks; i++)
    {
            j = i * 52;

            for(k = 0; k < 13; k++)
            {
                shoe.card_array[j + k] = card_create('S', k + 1);
            }
            for(l = 0; l < 13; l++)
            {
                shoe.card_array[j + k + l] = card_create('H', l + 1);
            }
            for(m = 0; m < 13; m++)
            {
                 shoe.card_array[j + k + l + m] = card_create('D', m + 1);
            }
            for(n = 0; n < 13; n++)
            {
                 shoe.card_array[ j + k + l + m + n] = card_create('C', n + 1);
            }

    }
    shoe_reshuffle(&shoe);
    return shoe;
}

card_t shoe_draw_card(shoe_t *shoe)
{
    card_t next_card; //local variable- returned: card to be drawn
    if(shoe_cards_left(*shoe) == 0)
    {
        shoe_reshuffle(shoe);
    }

    next_card = shoe->card_array[shoe->next_card_index];

    shoe->next_card_index++;
    return next_card;
}

int shoe_cards_left(shoe_t shoe)
{
    return (shoe.no_decks * 52) - shoe.next_card_index;
}

void shoe_reshuffle(shoe_t *shoe)
{
    int random_position,
        n, //local variable: number of cards to shuffle
        i; //loop control variable

    card_t temp; //local variable: temporary card

    n = shoe->no_decks * 52;
    shoe->next_card_index = 0;

    printf("\nSHUFFLING!\n");



    for(i = 0; i < n; i++)
    {
        random_position = i + rand()%(n - i);
        temp = shoe->card_array[random_position];
        shoe->card_array[random_position] = shoe->card_array[i];
        shoe->card_array[i] = temp;
    }

}

void shoe_free(shoe_t *shoe)
{
    free(shoe->card_array);
}

hand_t hand_create_empty()
{
    hand_t hand; //local variable- returned: empty hand

    hand.no_cards = 0;

    return hand;
}

void hand_print(hand_t hand)
{
    int i; //loop control variable

    for(i = 0; i < hand.no_cards; i++)
    {
        card_print(hand.card_array[i]);
        printf("\n");
    }

}

void hand_print_first_card(hand_t hand)
{
    card_print(hand.card_array[0]);
}

void hand_add_card(hand_t *hand, card_t card)
{
    hand->card_array[hand->no_cards] = card;
    hand->no_cards++;
}

int hand_blackjack_points(hand_t hand)
{
    int sum_points, //local variable- returned: sum of game points
        i,  //loop control variable
        ace_counter; //local variable: check for Aces

    sum_points = 0;
    ace_counter = 0;

    for(i = 0; i < hand.no_cards; i++)
    {
        sum_points += card_blackjack_points(hand.card_array[i]);
        if (card_get_value(hand.card_array[i]) == 1)
        {
            ace_counter += 1;
        }
    }

    if((ace_counter > 0)&& (sum_points < 12))
    {
        sum_points += 10;
    }
    return sum_points;
}

