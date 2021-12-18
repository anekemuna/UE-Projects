/* File: main.c
 * Transformation of images
 *
 * --------------------------------------------------------------------
 * Class: CS 210                       Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 6   Date assigned: March 28, 2019
 * Programmer: Munachimso S. Aneke     Date completed: April 11, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel.h"
#define MAX_SIZE 500

/*FUNCTION PROTOTPYE*/

/* Function:  print_greeting
   Print out the greeting. Tell user what the program is about.
 */
void print_greeting();

/*Function: open_file
 Opens a file
 Objects           Type    Movement      Name
 ---------------------------------------------------------
 prompt string     char[]    REC'D      prompt
 mode string       char[]    REC'D      file_mode
 file pointer      *FILE     Returned   file

*/
FILE *open_file(char prompt[], char file_mode[]);

/*Function: read_ppm_image
 Store pixel data
 Objects                  Type         Movement  Name
 ---------------------------------------------------------
 array to store pixels    pixel_t[][]  P'BACK    p_array
 number of columns        int*         P'BACK    width
 number of rows           int*         P'BACK    height
 maximum colour value     int*         P'BACK    max_colour
*/
void read_ppm_image(pixel_t p_array[MAX_SIZE][MAX_SIZE],
                    int *width, int *height, int *max_colour);

/*Function: write_ppm_image
 writes out pixel data
 Objects                    Type         Movement  Name
 -----------------------------------------------------------
 array to store image info  pixel_t[][]  Received  image_array
 number of columns          int          Received  width
 number of rows             int          Received  height
 maximum colour value       int          Received  max_colour
*/
void write_ppm_image(pixel_t image_array[MAX_SIZE][MAX_SIZE],
                     int width, int height, int max_colour);

/*Function: flip_horizontal
flips image horizontally
  Objects                 Type         Movement Name
 ---------------------------------------------------------
 array to store pixels    pixel_t[][]  REC'D    p_array
 number of columns        int          REC'D    width
 number of rows           int          REC'D    height
 transformed image        pixel_t[][]  P'BACK   trans_array
*/
void flip_horizontal(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                     int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE]);

/*Function: flip_vertical
flips image vertically
  Objects                 Type         Movement Name
 ---------------------------------------------------------
 array to store pixels    pixel_t[][]  REC'D    p_array
 number of columns        int          REC'D    width
 number of rows           int          REC'D    height
 transformed image        pixel_t[][]  P'BACK   trans_array
*/
void flip_vertical(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                   int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE]);

/*Function: rotate_left
rotates image to the left
  Objects                 Type         Movement Name
 ---------------------------------------------------------
 array to store pixels    pixel_t[][]  REC'D    p_array
 number of columns        int          REC'D    width
 number of rows           int          REC'D    height
 transformed image        pixel_t[][]  P'BACK   trans_array
*/
void rotate_left(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                 int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE]);

/*Function: rotate_right
rotates image to the right
  Objects                 Type         Movement Name
 ---------------------------------------------------------
 array to store pixels    pixel_t[][]  REC'D    p_array
 number of columns        int          REC'D    width
 number of rows           int          REC'D    height
 transformed image        pixel_t[][]  P'BACK   trans_array
*/
void rotate_right(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                  int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE]);

/*Function: print_options
prints user options and returns choice
  Objects         Type   Movement   Name
 ---------------------------------------------------------
 users choice     int    Returned   choice
*/
int print_options();


int main()
{
    //Declare data value needed
    static pixel_t p_array[MAX_SIZE][MAX_SIZE];
    //local variable: input- array containing pixels read from input
    //file
    static pixel_t trans_array[MAX_SIZE][MAX_SIZE];
    //local variable: output- array containing transformed pixels to
    //be written

    int width, //local variable: input- no of columns
        height,//local variable: input - no of rows
        max_colour,//local variable: input - maximum colour value
        choice,//local variable: input - users choice
        temp_width;//local variable: input - the temporary number of
                       //columns

    //1. Print out the greeting
    print_greeting();

    //2. Read the data from the input file
    read_ppm_image(p_array, &width, &height, &max_colour);

    //3. Prompt user for choice and return value
    choice = print_options();

    //4. Depending on the user choice run the write transformation
    switch(choice)
    {
    case 1:
        //flip horizontally if choice is 1
        flip_horizontal(p_array, width, height, trans_array);
        break;
    case 2:
        //flip vertically if choice is 2
        flip_vertical(p_array, width, height, trans_array);
        break;
    case 3:
        //rotate left if choice is 3
        rotate_left(p_array, width, height, trans_array);
        temp_width = height;
        height = width;
        width = temp_width;
        break;
    case 4:
        //rotate right if choice is 4
        rotate_right(p_array, width, height, trans_array);
        temp_width = height;
        height = width;
        width = temp_width;
        break;
    default:
        break;
    }

    //5. Write transformed image data to output file
    write_ppm_image(trans_array, width, height, max_colour);

    //6. Print end message
    printf("Enjoy your new image!\n");

    return 0;
}


/*FUNCTION DEFINTIONS*/

void print_greeting() //print greeting statement
{
    printf("PPM Image Manipulator\n");

}

FILE *open_file(char prompt[], char file_mode[])
{
    FILE *file; //Returned object: Opened file
    char file_name[FILENAME_MAX]; //local variable: name of file
                                    //to be opened

    //Print out the prompt
    printf("%s", prompt);

    //scan the name of the file
    scanf ("%s", file_name);

    //open the file and store in the file type variable
    file = fopen(file_name, file_mode);

    //Check if the file opened
    //if not opened print error message
    if (file == NULL)
    {
        printf ("Error: Unable to open file %s.", file_name);
        exit(1); //terminate program with non-zero result
    }

    //return value
    return file;
}

void read_ppm_image(pixel_t p_array[MAX_SIZE][MAX_SIZE],
                    int *width, int *height, int *max_colour)
{
    FILE *input_file; //local variable: input- file to read data
                        //from
    int i, //loop control variable
        j; //loop control variable
    char file_mode[] = "r", //local variable: input - the mode of
                            //the file, read
         prompt[] = "Enter the name of a PPM image file: ", //local
                                            //variable: input- prompt
         header[20], //local variable: stores the value of the first
                       //line of the opened file
         red[] = "P3\n"; // local variable: used to compare and
         //make sure that P3 is the first line of the opened file

    //open file and store the file in the file variable
    input_file = open_file(prompt, file_mode);

    //get the first line of the opened file
    fgets(header, 20, input_file);

    //check if the file opened is a ppm file
    //print error message if not ppm file
    if (strcmp(header, red) != 0)
    {
        printf("Error: This is not a PPM image file.");
        exit(1); //terminate program with non-zero result
    }

    //read in column value
    fscanf(input_file, "%d", width);

    //read in row value
    fscanf(input_file, "%d", height);

    //read in maximum colour value
    fscanf(input_file, "%d", max_colour);

    //read in pixels from file and store in pixel_t object
    for(i = 0; i < *height; i++)
    {
        for (j = 0; j < *width; j++)
        {
            p_array[i][j] = read_pixel_from_file(input_file);
        }

    }

    //close file
    fclose(input_file);
}

void write_ppm_image(pixel_t image_array[MAX_SIZE][MAX_SIZE],
                     int width, int height, int max_colour)
{
    FILE *output_file; //local variable - file to write data into
    char file_mode[] = "w", //local variable - the mode of the file,
                            //write
         prompt[] = "Enter the name of the output file: ";//local
                       //variable: input- prompt
    int i, //loop control variable
        j; //loop control variable

    //open the file to which the data will be written into
    output_file = open_file(prompt, file_mode);

    //print the header of the file to the output file
    fprintf(output_file, "P3\n");

    //print the column, rows and maximum value to output file
    fprintf(output_file, "%d %d\n%d\n", width, height, max_colour);

    //print out pixel value to the output file
    for(i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            write_pixel_to_file(output_file, image_array[i][j]);

        }

    }

    //close output file
    fclose(output_file);

}

void flip_horizontal(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                     int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE])
{
    int i, //loop control variable
        j; //loop control variable

    //loop to transform image
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            trans_array[i][(width -1)- j] = p_array[i][j];
        }
    }
}

void flip_vertical(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                   int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE])
{
    int i, //loop control variable
        j; //loop control variable

    //loop to transform image
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            trans_array[(height -1)- j][i] = p_array[j][i];
        }
    }
}

void rotate_left(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                 int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE])
{
    int temp_width, //local variable: temporary save the width value
        i, //loop control variable
        j; //loop control variable

    //swap the height and width
    //transfer the height into the temporary width
    temp_width = height;
    //transfer the width in to the height
    height = width;
    //transfer the  temporary width into the width
    width = temp_width;

    //loop to transform image
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            trans_array[(height - 1) - j][i] = p_array[i][j];
        }
    }
}

void rotate_right(pixel_t p_array[MAX_SIZE][MAX_SIZE], int width,
                  int height, pixel_t trans_array[MAX_SIZE][MAX_SIZE])
{
    int temp_width, //local variable: temporary save the width value
        i, //loop control variable
        j; //loop control variable

    //swap the height and width
    //transfer the height into the temporary width
    temp_width = height;
    //transfer the width in to the height
    height = width;
    //transfer the  temporary width into the width
    width = temp_width;

    //loop to transform image
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            trans_array[(height - 1) - j][(width - 1) - i] =
             p_array[i][(height - 1) - j];
        }
    }
}

int print_options()
{
    int choice; //local variable: Returned value- the users choice

    //Ask user for choice
    printf("Available transformations\n");
    printf("   1. Flip horizontal\n");
    printf("   2. Flip vertical\n");
    printf("   3. Rotate left\n");
    printf("   4. Rotate right\n");
    printf("Choose a transformation: ");

    //scan choice value
    scanf("%d", &choice);

    //return choice value
    return choice;
}
