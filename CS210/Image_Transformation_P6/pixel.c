/* File: pixel.c
 * Transformation of images
 *
 * --------------------------------------------------------------------
 * Class: CS 210                       Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 6   Date assigned: March 28, 2019
 * Programmer: Munachimso S. Aneke     Date completed: April 11, 2019
 */

#include <stdio.h> //printf, scanf
#include "pixel.h"

pixel_t read_pixel_from_file(FILE *input_file)
{
    pixel_t pixel_object;

    fscanf(input_file,"%d", &pixel_object.red);
    fscanf(input_file,"%d", &pixel_object.green);
    fscanf(input_file,"%d", &pixel_object.blue);

    return pixel_object;
}

void write_pixel_to_file(FILE *output_file, pixel_t pixel_object)
{
    fprintf(output_file, "%d %d %d\n", pixel_object.red,
            pixel_object.green, pixel_object.blue);
}

