/* File: main.c
 *  Allows two users to play one match of Rock, Paper, Scissors, Lizard, Spock.
 *
 * --------------------------------------------------------------
 * Class: CS 210-02                     Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 2    Date assigned: January 29, 2019
 * Programmer: Munachimso S. Aneke      Date completed: February 7, 2019
 */

#include <stdio.h> //printf, scanf definitions
#include <stdlib.h>
#include <ctype.h>  //toupper- converts lowercase to uppercase

/* FUNCTION PROTOTYPES */

/* Function:  print_greeting
  Print out the greeting at the beginning of the program.
 */
void print_greeting();

/* Function: get_pick
 Prompt a (single) user by player number to enter either R for Rock, P for Paper,S for Scissors,
 L for Lizard, or K for Spock,  and return the character entered in uppercase.

 Objects                                       Type  Movement       Name
 -------------------------------------------------------------------------
 player's number                               int   received       player_num
 character user picked converted to uppercase  char  returned       ch
*/
char get_pick(int player_num);

/* Function: print_picks
 print out what each user has picked
 Objects                             Type Movement Name
 ---------------------------------------------------------------
 character picked by first user      char received player1
 character picked by second user     char received player2

*/
void print_picks(char player1, char player2);

/* Function: compute_winner
 Returns a number that represents the outcome of the match
 Objects                            Type Movement Name
 ----------------------------------------------------
 character picked by first user     char received player1
 character picked by second user    char received player2
 result                             int  returned winner
*/
int compute_winner(char player1, char player2);




int main()
{
    char player1, //player one's character
         player2; //player two's character
    int winner;

    //1. Print the greeting function
    print_greeting(); //Display game heading

    //2. Get the first user's pick
    player1 = get_pick(1); //Player 1's input

    //3. Get the second user's pick
    player2 = get_pick(2); //Player 2's input

    //4. Print out player's picks
    print_picks(player1, player2);

    //5. Determine the winner using compute_winner function
    winner = compute_winner(player1, player2);


    //6. If the winner value is negative, print Player 1 wins!
    if (winner == -1)
        printf("\nPlayer 1 wins!\n");
    //7. If the winner value is positive, print Player 2 wins!
    else if (winner == 1)
        printf("\nPlayer 2 wins!\n");
    //8. Otherwise, print Tie!
    else
        printf("\nTie!\n");




    return 0;
}


/* FUNCTION DEFINITIONS */
void print_greeting()
{
    printf("Welcome to the RPSLK Game!\nLet's play!!\n");
}

char get_pick(int player_num)
{
    char ch;
    //1.Ask the user by player number for an input of R, P, S, L, K
    printf("Player %d, Pick (R)ock, (P)aper, (S)cissors, (L)izard, or Spoc(K): ", player_num);

    //2.Read in the input
    scanf(" %c", &ch);

    //3.Convert the input to uppercase
    ch = toupper(ch);

    //4.Return the input
    return ch;

}

void print_picks(char player1, char player2)
{
    switch(player1) //Print out what player one chose
    {
        case 'R':
            printf("\nPlayer 1 chose Rock");
            break;
        case 'P':
            printf("\nPlayer 1 chose Paper");
            break;
        case 'S':
            printf("\nPlayer 1 chose Scissors");
            break;
        case 'L':
            printf("\nPlayer 1 chose Lizard");
            break;
        case 'K':
            printf("\nPlayer 1 chose Spock");
            break;
        default:
            printf("\nPlayer 1 chose Unknown");
    }

    switch(player2) //Print out what player 2 chose
    {
        case 'R':
            printf("\nPlayer 2 chose Rock");
            break;
        case 'P':
            printf("\nPlayer 2 chose Paper");
            break;
        case 'S':
            printf("\nPlayer 2 chose Scissors");
            break;
        case 'L':
            printf("\nPlayer 2 chose Lizard");
            break;
        case 'K':
            printf("\nPlayer 2 chose Spock");
            break;
        default:
            printf("\nPlayer 2 chose Unknown");
    }

}

int compute_winner(char player1, char player2)
{
    int winner;
    if (player1 == 'R')
    {
        switch(player2)
    {
        case 'R':
            winner = 0;
            break;
        case 'P':
            winner = 1;
            break;
        case 'S':
            winner = -1;
            break;
        case 'L':
            winner = -1;
            break;
        case 'K':
            winner = 1;
            break;
        default:
            winner = -1;
    }

    }
    else if (player1 == 'P')
    {
        switch(player2)
    {
        case 'R':
            winner = -1;
            break;
        case 'P':
            winner = 0;
            break;
        case 'S':
            winner = 1;
            break;
        case 'L':
            winner = 1;
            break;
        case 'K':
            winner = -1;
            break;
        default:
            winner = -1;
    }

    }
    else if (player1 == 'S')
    {
        switch(player2)
    {
        case 'R':
            winner = 1;
            break;
        case 'P':
            winner = -1;
            break;
        case 'S':
            winner = 0;
            break;
        case 'L':
            winner = -1;
            break;
        case 'K':
            winner = 1;
            break;
        default:
            winner = -1;
    }

    }
    else if (player1 == 'L')
    {
        switch(player2)
    {
        case 'R':
            winner = 1;
            break;
        case 'P':
            winner = -1;
            break;
        case 'S':
            winner = 1;
            break;
        case 'L':
            winner = 0;
            break;
        case 'K':
            winner = -1;
            break;
        default:
            winner = -1;
    }

    }
    else if (player1 == 'K')
    {
        switch(player2)
    {
        case 'R':
            winner = -1;
            break;
        case 'P':
            winner = 1;
            break;
        case 'S':
            winner = -1;
            break;
        case 'L':
            winner = 1;
            break;
        case 'K':
            winner = 0;
            break;
        default:
            winner = -1;
    }

    }
    else if ((player1 != 'R') || (player1 != 'P') || (player1 != 'S') || (player1 != 'L')|| (player1 != 'K'))
    {
        switch(player2)
    {
        case 'R':
            winner = 1;
            break;
        case 'P':
            winner = 1;
            break;
        case 'S':
            winner = 1;
            break;
        case 'L':
            winner = 1;
            break;
        case 'K':
            winner = 1;
            break;
        default:
            winner = 0;
    }

    }

    return winner;
}

