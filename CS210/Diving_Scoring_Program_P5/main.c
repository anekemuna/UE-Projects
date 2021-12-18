/* File: main.c
 * A simple diving scoring program
 *
 * --------------------------------------------------------------
 * Class: CS 210-02                     Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 5    Date assigned: March 19, 2019
 * Programmer: Munachimso S. Aneke      Date completed: March 29, 2019
 */

#include <stdio.h> // printf, scanf definitions
#include <stdlib.h>

#define SENTINEL -1.0
#define MAX_SIZE 100

/*FUNCTION PROTOTPYE*/

/* Function:  print_greeting
   Print out the greeting. Tell user what the program is about.
 */
void print_greeting();

/*Function: get_file
  asks user for input file name and opens the file
 Objects                Type    Movement   Name
 ----------------------------------------------------
 pointer to open file   *FILE   returned   file
*/
FILE *get_file();

/* Function: fill_array
 reads diving data from file and computes diving score
 Objects                  Type     Movement    Name
 ----------------------------------------------------
 pointer to open file of  FILE*    received    input_file
 array of competition IDs int[]    passed back ids
 array of round scores    double[] passed back scores
 number of divers         int*     passed back num_divers
 */
void fill_array (FILE* input_file, int ids[], double scores[],
                 int *num_divers);

/*Function: compute_score
  computes score for a single dive
 Objects                  Type    Movement   Name
 ----------------------------------------------------
 pointer to open file     *FILE   received   input_file
 final score of one dive  double  returned   final_score
*/
double compute_score(FILE* input_file);

/*Function: sum_of_scores
  computes the sum of scores and subtracts the 2 minimum and maximum scores
 Objects                            Type      Movement   Name
 ---------------------------------------------------------------------
 array of scores                    double[]  received   score
 number of scores in array          int       received   num_scores
 sum of score without min and max   double    returned   sum
*/
double sum_of_scores(double score[], int num_scores);

/*Function: select_sort
  orders the array
 Objects                    Type      Movement   Name
 -------------------------------------------------------
 array to be sorted         int[]    REC'D/P'BACK   ids
 array to be sorted         double[] REC'D/P'BACK   scores
 number of value in array   int      REC'D          num
*/
void select_sort (int ids[], double scores[], int num);

/*Function: find_index_of_smallest_in_range
  swaps the value
 Objects                        Type     Movement  Name
 -------------------------------------------------------------------
 array of score                 double[] Received an_array
 lower range value              int      Received lower
 upper range value              int      Received upper
 index of largest of number     int      Returned index_of_largest
*/
int index_of_largest_in_range(const double an_array[], int lower, int upper);

/*Function: print_result
  Print out the result.
  Objects                  Type     Movement   Name
 ---------------------------------------------------------------------
  array of ids             int[]    received   ids
  array of round scores    double[] received   scores
  number of divers         int      returned   y
 */
void print_result(int ids[], double scores[], int y);



int main()
{
    FILE* input_file; //input: file containing data
    double scores[MAX_SIZE]; //output array of scores
    int ids[MAX_SIZE], //output array of id numbers
        y = 0, //input: number of values in array
        i;  //loop control variable

    //1.Print out the greeting statement
    print_greeting();

    //2.get the file to collect data from
    input_file = get_file();

    //3. Fill the array and compute the scores of each dive
    fill_array(input_file, ids,scores, &y);

    //4.Sort the function in the descending order
    select_sort(ids, scores, y);

    //5.print the result of each diver
    print_result(ids, scores, y);

    //6.close file
    fclose(input_file);

    return 0;
}

/*FUNCTION DEFINTIONS*/

void print_greeting() //print greeting statement
{
    printf("Welcome to the diving competition scoring program.\n\n");

}

FILE *get_file() //get file with diving scores
{
    FILE *file; //local variable: returned object
    char filename[FILENAME_MAX]; //local variable: input

    // 1. Ask the user for a filename
    printf ("Enter the diving data file name: ");
    scanf ("%s", filename);

    // 2. Open the file
    file = fopen(filename, "r");

    // 3. Check if successful
    while(file == NULL)
    {
        printf ("Unable to open file. Try again.\n");
        printf ("Enter the diving data file name: ");
        scanf ("%s", filename);
        file = fopen(filename, "r");
    }

    //4. Return the file pointer
    return file;
}

void fill_array (FILE* input_file, int ids[], double scores[],
                 int *num_divers)
{
    int i, //loop control variable
        j; //loop control variable
    double final_score = 0, //local variable- the final score for each dive
           round_score; //total dive score for a diver

    *num_divers = 0; //initialization

    //get the id of the diver and end the loop when there's no more id's
    for(i= 0; fscanf(input_file,"%d", &ids[i]) != EOF; i++)
    {

        round_score = 0; //initialization of round score
        //gets the round score for a particular diver
        for(j = 0; j < 6; j++)
        {
            final_score = compute_score(input_file);
            round_score += final_score;
        }

        //put the round scores into an array with the same index
        //no as their id's
        scores[i] = round_score;

        //count the number of divers
        *num_divers = *num_divers + 1;
    }
}

double compute_score (FILE* input_file)
{
    int i; //loop control variable
    double final_score = 0, //returned: final score of the dive
           difficulty_value = 0, //local variable: level of
                                 //difficulty of dive
           scores[50], //local variable: array of scores for one dive
           score_value = 0, //local variable: value of score
           sum = 0; //local variable: sum of three scores

    //get the value for the level of difficulty
    fscanf(input_file, "%lf", &difficulty_value);

    //get the value for the of the scores into an array,
    //use sentinel value to end the loop
    fscanf(input_file, "%lf", &score_value);


    for(i = 0; score_value != SENTINEL; i++)
    {

        scores[i] = score_value;
        fscanf(input_file, "%lf", &score_value);

    }

    //find the sum of the scores without the 2 maximum and 2 minimum numbers
    sum = sum_of_scores(scores, i);

    //find the final score for each round
    final_score = sum * difficulty_value;

    //return the result
    return final_score;

}

double sum_of_scores(double scores[], int num_scores)
{
    int j; //local variable - loop control variable
    double max1 = 0.0, //local variable - largest number in the list
           max2 = 0.0, //local variable - largest 2nd number in the list
           min1 = 10.0, //local variable - smallest number in the list
           min2 = 10.0, //local variable - 2nd smallest number in the list
           sum = 0; //returned value- sum of values in the list
    //get the 2 highest value and 2 lowest value
    for(j = 0; j < num_scores ; j++)
    {
        //sum the values of all scores
        sum += scores[j];


        if(scores[j] > max1) //find the 2 highest values
        {
            max2 = max1;
            max1 = scores[j];

        }
        else if(scores[j] > max2)
        {
            max2 = scores[j];
        }
        if(scores[j] < min1) //find the 2 lowest values
        {
            min2 = min1;
            min1 = scores[j];
        }
        else if(scores[j] < min2)
        {
            min2 = scores[j];
        }

    }
    //calculate the sum when the 2 highest and lowest are subtracted
    sum = sum - (min1 + min2 + max1 +max2);

    //return the value
    return sum;

}

void select_sort (int ids[], double scores[], int num)
                            //arrange array in descending order
{
    int i = 0,
        index_of_largest,
        id_temporary_value;

    double scores_temporary_value;
    while(i < num - 1)
    {
        //get the index of the largest value
        index_of_largest = index_of_largest_in_range(scores, i, num);

        if(i != index_of_largest)
        {
            scores_temporary_value = scores[i];
            scores[i] = scores[index_of_largest];
            scores[index_of_largest] = scores_temporary_value;

            id_temporary_value = ids[i];
            ids[i] = ids[index_of_largest];
            ids[index_of_largest] = id_temporary_value;
        }
        i = i + 1;
    }

}

int index_of_largest_in_range(const double an_array[],int lower, int upper)
//find the index of the largest number in an array
{
    int i, //loop control variable- lcv
        index_of_largest; // index of the largest value seen so far

    //Assume the first element is the largest
    index_of_largest = lower;

    // for each statement see if it larger than the current larger
    // start at the second element of the range
    for(i = lower +1; i < upper; i++)
        //check if the element at 1 is larger
        if (an_array[i] > an_array[index_of_largest])
        {
            // keep track of the new smaller value
            index_of_largest = i;
        }

    //index_of_largest is the index of the largest value
    return index_of_largest;
}

void print_result(int ids[], double scores[], int y) //prints the result out
{
    int i; //loop control variable;
    printf("\nID  Score\n");
    printf("--- ------\n");

    for(i = 0; i < y; i++)
    {
        printf("%d %.2lf\n", ids[i], scores[i]);
    }

}
