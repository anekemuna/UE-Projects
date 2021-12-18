/* File: main.c
 * Permits the user to convert either 2-point form or point-slope form into
 * slope-intercept form.
 *
 * --------------------------------------------------------------
 * Class: CS 210                      Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 4  Date assigned: February 21, 2019
 * Programmer: Munachimso S. Aneke    Date completed: March 2, 2019
 */

#include <stdio.h> // printf, scanf definitions
#include <stdlib.h>
#include <ctype.h> //tolower- to convert uppercase to lowercase

/*FUNCTION PROTOTPYE*/

/* Function:  print_heading
  Print out the heading at the beginning of the program.
 */
void print_heading ();

/* Function: get_problem
 Displays the user menu and returns the chosen value
 Objects                 Type  Movement   Name
 ----------------------------------------------------
 problem number selected int   returns    option
*/
int get_problem ();

/* Function: get2_pt
 prompts the user for 2 x-y coordinate points
 Objects              Type   Movement        Name
 ----------------------------------------------------
 first x coordinate   double REC'D & P'BACK  x1
 first y coordinate   double REC'D & P'BACK  y1
 second x coordinate  double REC'D & P'BACK  x2
 second y coordinate  double REC'D & P'BACK  y2
*/
void get2_pt(double *x1, double *y1, double *x2, double *y2);

/* Function: get_pt_slope
 prompts the user for a slope and x-y coordinate point
 Objects        Type   Movement        Name
 ----------------------------------------------------
 x coordinate   double REC'D & P'BACK  x1
 y coordinate   double REC'D & P'BACK  y1
 slope          double REC'D & P'BACK  m
*/
void get_pt_slope(double *x1, double *y1, double *m);

/* Function: slope_intcpt_from_2pt
 calculates slope and y-intercept after given the coordinates of 2 points
 Objects              Type   Movement       Name
 ----------------------------------------------------
 first x coordinate   double Received       x1
 first y coordinate   double Received       y1
 second x coordinate  double Received       x2
 second y coordinate  double Received       y2
 slope                double Passed back    m
 y-intercept          double Passed back    b
*/
void slope_intcpt_from_2pt(double x1, double y1, double x2, double y2, double *m, double *b);

/* Function: intcpt_from_pt_slope
 calculates the y-intercept
 Objects        Type   Movement   Name
 ----------------------------------------------------
 x coordinate   double Received   x1
 y coordinate   double Received   y1
 slope          double Received   m
 y-intercept    double Returned   b
*/
double intcpt_from_pt_slope(double x1, double y1, double m);

/* Function: display2_pt
displays the 2 point line equation with heading
 Objects              Type   Movement  Name
 ----------------------------------------------------
 first x coordinate   double Received  x1
 first y coordinate   double Received  y1
 second x coordinate  double Received  x2
 second y coordinate  double Received  y2
*/
void display2_pt(double x1, double y1, double x2, double y2);

/* Function: display_pt_slope
displays the point-slope line equation with heading
 Objects       Type   Movement  Name
 ----------------------------------------------------
 x coordinate  double Received  x1
 y coordinate  double Received  y1
 slope         double Received  m
*/
void display_pt_slope(double x1, double y1, double m);

/* Function: display_slope_intcpt
displays the slope-intercept line equation with heading
 Objects       Type   Movement  Name
 ----------------------------------------------------
 slope         double Received  m
 y-intercept   double Received  b
*/
void display_slope_intcpt(double m, double b);


/* Function: user_wants_to_continue
   Returns true (1) if user enters 'y', false (0) if user enters 'n'
*/
int user_wants_to_continue();


int main()
{
    int option; //local variable: the option number chosen by the user
    double x1,  //local variable: first x coordinate
           y1,  //local variable: first y coordinate
           x2,  //local variable: second x coordinate
           y2,  //local variable: second y coordinate
           m,   //local variable: slope
           b;   //local variable: y-intercept

    //1. print heading of application
    print_heading();

    do
    {
        //2. print menu and collect user's choice
        option = get_problem();

        //2b. Validate option choice
        if ((option != 1) && (option != 2))
        {
            printf("Invalid choice!\n");
        }
        else if (option == 1)
        {
            //get the coordinate of 2 points
            get2_pt(&x1, &y1, &x2, &y2);

            //find the slope and y-intercept
            slope_intcpt_from_2pt(x1, y1, x2, y2, &m, &b);

            //display the 2-point line equation
            display2_pt(x1, y1, x2, y2);

            //display the slop-intercept line equation
            display_slope_intcpt(m, b);

        }
        else if (option == 2)
        {
            //get the coordinates of the point and slope
            get_pt_slope(&x1, &y1, &m);

            //find the y-intercept
            b = intcpt_from_pt_slope(x1, y1, m);

            //display the slope-point line equation
            display_pt_slope(x1, y1, m);

            //display the slop-intercept line equation
            display_slope_intcpt(m, b);
        }
    } //3. Ask if user wants to continue
    while(user_wants_to_continue());
    printf("\nThat's all!\n");

    return 0;
}



/*FUNCTION DEFINTIONS*/

void print_heading() //Print heading statement
{
    //Print the heading
    printf("SLIPPERY SLOPES\n");
}

int get_problem () //display user menu
{
    int option; //local variable: the option number chosen by the user

    //Display menu
    printf("\nSelect the form that you would like to convert to slope-intercept\n");
    printf("  1) Two-point form (you know two points on the line)\n");
    printf("  2) Point-slope form (you know the line's slope and one point)\n");

    //ask for user's choice
    printf("Enter your choice: ");
    scanf("%d", &option);
    return option;
}

void get2_pt(double *x1, double *y1, double *x2, double *y2)
//ask for 2 x-y coordinates
{
    //ask for first point coordinate
    printf("\nEnter the x-y coordinates of the first point (separated by spaces): ");
    scanf("%lf %lf", &*x1,&*y1);

    //ask for second point coordinate
    printf("Enter the x-y coordinates of the second point (separated by spaces): ");
    scanf("%lf %lf", &*x2, &*y2);
}

void get_pt_slope(double *x1, double *y1, double *m)
//ask for slope and x-y coordinate
{
    printf("\nEnter the slope: "); //ask for slope value
    scanf("%lf", &*m);

    //ask for x-y coordinates
    printf("Enter the x-y coordinates of the point (separated by spaces): ");
    scanf("%lf %lf", &*x1,&*y1);
}

void slope_intcpt_from_2pt(double x1, double y1, double x2, double y2, double *m, double *b)
//calculates m and b
{
    *m = ( y2 - y1)/(x2 - x1); //calculate slope (m)

    *b = y1 - (*m * x1);  //calculate y-intercept (b)
}

double intcpt_from_pt_slope(double x1, double y1, double m)
//calculates the y-intercept (b)
{
    double b; //local variable: y intercept

    b = y1 - (m * x1); //calculate y- intercept

    return b;
}

void display2_pt(double x1, double y1, double x2, double y2)
//displays 2 point line equation
{
    printf("\nTwo-point form\n"); //display heading
    // display equation
    printf("    (%.2lf - %.2lf)\n", y2, y1);
    printf("m = ---------------\n");
    printf("    (%.2lf - %.2lf)\n", x2, x1);
}

void display_pt_slope(double x1, double y1, double m)
//displays point-slope line equation
{
    printf("\nPoint-slope form\n"); //display heading
    printf("y - %.2lf = %.2lf(x - %.2lf)\n", y1, m, x1); //display equation
}

void display_slope_intcpt(double m, double b)
//displays slope-intercept line equation
{
    printf("\nSlope-intercept form\n"); //display heading
    printf("y = %.2lfx + %.2lf\n", m, b); //display equation
}

int user_wants_to_continue() // ask if user wants to play again
{
    char response;  // Input: user's response

    // Do the following in a do-while loop
    do
    {
        // Ask the user for y/n
        printf ("\nDo you want to do another problem (y/n)? ");
        scanf (" %c", &response);

        // Convert response to lowercase
        response = tolower(response);

        // Print an error message if not a 'y' or an 'n'
        if ((response != 'y') && (response != 'n'))
            printf ("Bad input. Try again.\n");

        // While response is not a 'y' or an 'n'
    }
    while ((response != 'y') && (response != 'n'));
    // While response is not a 'y' or an 'n', do loop again

    return response == 'y'; //return value if response is equal to 'y'
}
