/* File: main.c
 * Game of Nim
 *
 * -------------------------------------------------------------------------------
 * Class: CS 210-02                        Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 3       Date assigned:  February 7, 2019
 * Programmer: Munachimso S. Aneke         Date completed:  February 15, 2019
 */

#include <stdio.h> //printf, scanf definitions
#include <stdlib.h>
#include <ctype.h> //tolower

/*FUNCTION PROTOTYPES*/

/* Function:  print_greeting
  Print out the greeting at the beginning of the program.
 */
void print_greeting ();

/* Function: user_wants_to_play_again
   Returns true (1) if user enters 'y', false (0) if use enters 'n'
*/
int user_wants_to_play_again();

/* Function: print_scoreboard
 Print out the current numbers of win by computer and by user
 Objects                  Type  Movement Name
 ----------------------------------------------------
 number of computer wins  int   received comp_wins
 number of user wins      int   received user_win

*/
void print_scoreboard (int user_wins, int comp_wins);

/* Function: play_nim
 To play one game of Nim
 Objects                           Type  Movement Name
 ------------------------------------------------------------------
 Number of the player that starts  int   received starting_player
 Number of the player that won     int   returned winner

*/
int play_nim (int starting_player);

/* Function: get_computer_move
 that computes value of the computer
 Objects                            Type  Movement      Name
 -------------------------------------------------------------------------------
 Three heaps of stones              int   received      heap_a, heap_b, heap_c

 Computer's chosen heap             char  passed back   chosen_heap
 Computer's chosen number of stones int   passed back   number_to_remove

*/
void get_computer_move (int heap_a, int heap_b, int heap_c, char *chosen_heap, int *number_to_remove);


int main()
{
    //Analysis- data needed
    int comp_wins, //computer score
        user_wins, //user score
        starting_player, //number of the player playing
        winner; //calculate the winner of the game

    //Design- steps needed

    //1. Print the greeting for the game
    print_greeting();

    //Initializing variables
    //2a. Initialize the scores for user and computer
    user_wins = 0;
    comp_wins = 0;

    starting_player = 1; //2b.player one starts first- initializing

    //use a loop to do parts needed to be repeated
    do
    {

        //2c.initialize winner and return value from play_nim() function
        winner = play_nim(starting_player);

        //3. Calculate winner of the game score
        if (winner == 2)
        {
            comp_wins = comp_wins + 1;
            starting_player = 1;
        }
        else if (winner == 1)
        {
            user_wins = user_wins + 1;
            starting_player = 2;


        }


        //4. Add the calculated score to the score board
        print_scoreboard(user_wins, comp_wins);

    }
    while (user_wants_to_play_again()); //keep repeating until user say 'n'



    return 0;
}

/*FUNCTION DEFINITION*/

void print_greeting() //Print inductory greeting statements
{
    //Print the greeting for the game
    printf("Welcome to the Ancient Game of Nim\n");
    printf("Player 1 is you (the human)\n");
    printf("Player 2 is me (the computer)\n");
}

int user_wants_to_play_again() // ask if user wants to play again
{
    char response;  // Input: user's response

    // Do the following in a do-while loop
    do
    {
        // Ask the user for y/n
        printf ("\nDo you wish to play again? (y/n) ");
        scanf (" %c", &response);

        // Convert response to lowercase
        response = tolower(response);

        // Print an error message if not a 'y' or an 'n'
        if ((response != 'y') && (response != 'n'))
            printf ("Bad input! Try again.\n");

        // While response is not a 'y' or an 'n'
    }
    while ((response != 'y') && (response != 'n'));
    // While response is not a 'y' or an 'n', do loop again

    return response == 'y'; //return value if response is equal to 'y'
}

void print_scoreboard (int user_wins, int comp_wins) //Print scores
{
    printf("\n* * * * * * * * * * *");
    printf("\nCurrent Score:");
    printf("\nPlayer 1 (Human):    %d", user_wins); //user score
    printf("\nPlayer 2 (Computer): %d\n", comp_wins); //computer score
}

int play_nim(int starting_player) //play game
{
    //Analysis- data needed
    int heap_a, //local variable- count of number of stones in heap A
        heap_b, //local variable-count of number of stones in heap B
        heap_c, //local variable-count of number of stones in heap C
        track_player_turn, //local variable-track which player turn it is
        empty, // local variable- used check if all heaps are empty
        number_to_remove,//local variable - number of stones to remove
        winner; //local variable - winner of the game

    char chosen_heap; //local variable - heap chosen to remove stones from

    //Design- Steps needed
    //1. Note the number of stones at the beginning
    heap_a = 5;
    heap_b = 4;
    heap_c = 3;

    //2. track player's turn
    track_player_turn = starting_player;

    //3. Print who starts first
    printf("Player %d goes first this time!\n", track_player_turn);

    // steps to be repeated put in a loop
    do
    {

        //4. Write the player number and the Heaps heading
        printf("\nPlayer %d\n", track_player_turn);
        printf("Heaps:\n");

        //5. Note the number of stones remaining in all the heaps
        printf("A: %d\n",heap_a);
        printf("B: %d\n",heap_b);
        printf("C: %d\n",heap_c);

        //6. If it's player 1, request for users input, if not get_computers_move
        if (track_player_turn == 1)//when it's player one's turn
        {
            //get user's input
            printf("Enter the letter of the heap and number of stones to remove: ");
            scanf(" %c%d", &chosen_heap, &number_to_remove);

            //convert uppercase letters to lowercase
            chosen_heap = tolower(chosen_heap);

            //Invalid move if the number_to_remove is less than the heap number
            //Invalid move if the chosen_heap does not exist .i.e not a,b,c
            switch (chosen_heap)
            {
            case 'a':
                if (number_to_remove <= heap_a)
                {
                    heap_a = heap_a - number_to_remove;
                    track_player_turn = 2;
                }
                else
                {
                    printf("Illegal move! Try again.\n");
                    track_player_turn = 1;
                }
                break;
            case 'b':
                if (number_to_remove <= heap_b)
                {
                    heap_b = heap_b - number_to_remove;
                    track_player_turn = 2;
                }
                else
                {
                    printf("Illegal move! Try again.\n");
                    track_player_turn = 1;
                }
                break;
            case 'c':
                if (number_to_remove <= heap_c)
                {
                    heap_c = heap_c - number_to_remove;
                    track_player_turn = 2;
                }
                else
                {
                    printf("Illegal move! Try again.\n");
                    track_player_turn = 1;
                }
                break;
            default:
                printf("Illegal move! Try again.\n");
                track_player_turn = 1;
                break;
            }


        }
        //When it is player 2's turn run function get_computer_move
        else if (track_player_turn == 2)
        {
            get_computer_move(heap_a, heap_b, heap_c, &chosen_heap, &number_to_remove);
            printf("COMPUTER moves %c%d\n", chosen_heap, number_to_remove);
            //read value and carry out calculate the value of stones left in the heap
            if (chosen_heap == 'a')
            {
                heap_a = heap_a - number_to_remove;
            }
            else if (chosen_heap == 'b')
            {
                heap_b = heap_b - number_to_remove;
            }
            else if (chosen_heap == 'c')
            {
                heap_c = heap_c - number_to_remove;
            }
            track_player_turn = 1;

        }

        //check if there is still stones
        if ((heap_a == 0) && (heap_b == 0) && (heap_c == 0))
        {
            empty = 0;//empty is 0 if no stones are left
        }
        else
        {
            empty = 1; //empty is 1 if there are still stones left in any heap

        }

    }
    while (empty != 0); //run loop if there are still stones left

    //7. Print out who the winner is

    if (track_player_turn == 2)
    {
        winner = 1;
    }
    else
    {
        winner = 2;
    };
    printf("Player %d wins!\n", winner);

    return winner;
}

void get_computer_move(int heap_a, int heap_b, int heap_c, char *chosen_heap, int *number_to_remove)
{
    int nim_number; //local variable

    //given this information
    nim_number = heap_a ^ heap_b ^ heap_c;

    //If the nim_number is 0, check out each heap to find the one with stones left
    if (nim_number == 0)
    {
        if (heap_a > 0)
        {
            *chosen_heap = 'a';
            *number_to_remove = 1;
        }
        else if (heap_b > 0)
        {
            *chosen_heap = 'b';
            *number_to_remove = 1;
        }
        else if (heap_c > 0)
        {
            *chosen_heap = 'c';
            *number_to_remove = 1;
        }

    }
    else
    {
        if ((heap_a ^ nim_number) < heap_a)
        {
            *chosen_heap = 'a' ;
            *number_to_remove = heap_a - (heap_a ^ nim_number);
        }
        else if ((heap_b ^ nim_number) < heap_b)
        {
            *chosen_heap = 'b' ;
            *number_to_remove = heap_b - (heap_b ^ nim_number);
        }
        else if ((heap_c ^ nim_number) < heap_c)
        {
            *chosen_heap = 'c' ;
            *number_to_remove = heap_c - (heap_c ^ nim_number);
        }
    }
}
