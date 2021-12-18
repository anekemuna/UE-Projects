/* File: pixel.h
 * Transformation of images
 *
 * --------------------------------------------------------------------
 * Class: CS 210                       Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 6   Date assigned: March 28, 2019
 * Programmer: Munachimso S. Aneke     Date completed: April 11, 2019
 */

#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

/* Data structure: pixel_t
 represents one pixel of an image
*/
typedef struct
    {
        int red,
            green,
            blue;
    } pixel_t;

/* Function: read_pixel_from_file
 Read one pixel object from input file
 Objects           Type    Movement   Name
 ---------------------------------------------------------
 file pointer      *FILE   Received   input_file
 one pixel data    pixel_t Returned   pixel_object
*/
pixel_t read_pixel_from_file(FILE *input_file);

/* Function: write_pixel_to_file
 write one pixel object into output file
 Objects           Type    Movement   Name
 ---------------------------------------------------------
 file pointer      *FILE   Received   output_file
 one pixel data    pixel_t Received   pixel_object
*/
void write_pixel_to_file(FILE *output_file, pixel_t pixel_object);

#endif // PIXEL_H_INCLUDED
