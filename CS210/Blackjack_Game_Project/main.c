/* File: main.c
 *Blackjack Game
 *
 * --------------------------------------------------------------------
 * Class: CS 210                       Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 7   Date assigned: April 16, 2019
 * Programmer: Munachimso S. Aneke     Date completed: April 30, 2019
 */


#include <stdio.h> //printf, scanf
#include <stdlib.h>
#include <ctype.h>  //toupper
#include <time.h> //srand

#include "cards.h"

int main()
{

    srand(time(0)); //seed

    int player_stake = 1000, //output: player's stake
        player_bet,  //input: how much the player bets
        no_decks, //input: number of decks
        //money_left, //output: money left after losing or wining
        player_score,  //output: score of the player
        dealer_score;  //output: score of the dealer
    shoe_t shoe; //output: shoe containing decks of card
    hand_t dealer_hand, //output: dealer's hand
           player_hand; //output: player's hand
    char player_choice; //input: player's choice


    //1. Print the greeting
    printf("Welcome to Blackjack!\n\n");

    //2a. Ask the player how many decks to create
    do
    {
        printf("How many decks do you wish to play with (1-10)? ");
        scanf("%d",&no_decks);
    }
    while((no_decks < 1) || (no_decks > 10));

    //2b. Create number of decks of card to be in shoe
    shoe = shoe_create(no_decks);

    //3. while the player still has money and a positive bet
    do
    {
        //3a. Print stake and number of cards remaining
        printf("Your stake: $%d\n", player_stake);
        printf("Cards left in the shoe: %d\n", shoe_cards_left(shoe));

        //3b. Ask player for bet
        do
        {
            printf("\nEnter your bet (negative to quit): ");
            scanf("%d", &player_bet);

        }
        while(player_bet > player_stake);

        if(player_bet < 0)
        {
            printf("You ended the night with $%d\n", player_stake);
            return 0;
        }
        else
        {
            //3c. If bet is more than 0, draw initial hand for dealer
            //     and player
            dealer_hand = hand_create_empty();
            player_hand = hand_create_empty();

            hand_add_card(&dealer_hand, shoe_draw_card(&shoe));
            hand_add_card(&player_hand, shoe_draw_card(&shoe));

            hand_add_card(&dealer_hand, shoe_draw_card(&shoe));
            hand_add_card(&player_hand, shoe_draw_card(&shoe));

            //3d. Display first card of dealer
            printf("The dealer is showing ");
            hand_print_first_card(dealer_hand);
            printf("\n\n");

            printf("Your cards:\n");
            hand_print(player_hand);
            player_score = hand_blackjack_points(player_hand);
            printf("Score =  %d\n", player_score );

            //3e. As player to Hit or Stand
            do
            {
                do
                {
                    printf("\nDo you want to (H)it or (S)tand? ");
                    scanf(" %c", &player_choice);
                    player_choice = toupper(player_choice);

                }
                while(player_choice != 'S' && player_choice != 'H');
                if(player_choice == 'H')
                {
                    hand_add_card(&player_hand, shoe_draw_card(&shoe));
                    printf("Your cards:\n");
                    hand_print(player_hand);
                    player_score = hand_blackjack_points(player_hand);
                    printf("Score =  %d\n", player_score);

                }
            }
            while((player_score < 21) && (player_choice != 'S'));
            if(player_choice == 'S')
            {
                dealer_score = hand_blackjack_points(dealer_hand);
                while(dealer_score < 17)
                {
                    hand_add_card(&dealer_hand, shoe_draw_card(&shoe));
                    dealer_score = hand_blackjack_points(dealer_hand);
                }

                printf("Dealer cards:\n");
                hand_print(dealer_hand);
            }
        }
        //3f. Determine the winner   and...
        //4. Print the result
        if(player_score > 21)
        {
            printf("You Busted. You lose!\n");
            player_stake -= player_bet;
        }
        else if((dealer_score <= 21) && (player_score < dealer_score))
        {
            printf("Dealer wins with a score of %d. You Lose!\n",
                   dealer_score);
            player_stake -= player_bet;
        }
        else if((dealer_score > 21))
        {
            printf("Dealer Busts. You Win %d!\n", player_bet * 2);
            //player_stake = money_left + (player_bet * 2);
            player_stake += (player_bet *2);
        }
        else if((player_score <= 21) && player_score > dealer_score)
        {
            printf("You win with a score of %d. You win $%d\n",
                   player_score, (player_bet * 2));
            player_stake += (player_bet * 2);
        }
        else if( player_score == dealer_score)
        {
            printf("It's a tie. You get back $%d.\n", player_bet);
        }

}
while((player_stake) > 0 && (player_bet > 0));
printf("You've lost your entire stake!\n");

return 0;
}
