/* File: main.c
 * Determining the phase of the moon when given time and date
 *
 * --------------------------------------------------------------
 * Class: CS 210-02                            Instructor: Dr. Deborah Hwang
 * Assignment: Programming Project 1           Date assigned: January 22, 2019
 * Programmer: Munachimso S. Aneke             Date completed: January 29, 2019
 */

#include <stdio.h> //printf, scanf definitions
#include <stdlib.h>
#include <math.h>  //sin, cos, pow, definitions
#define PI 3.14159

int main()
{   //Analysis- what is data is needed?
    int year,//Year of the date
        month,//month of the date
        day, // day of the month
        hour, //Hour of the day in 24 hour notation
        timezone; //The local timezone as an offset from UTC
    double jd, //julian date
           t, //proportion of julian century
           el, // moon's mean elongation in degrees
           ma, //moon's mean anomaly in degrees
           sa, // sun's mean anomaly in degrees
           pa; // phase angle of the moon in degrees
    //Design- Steps to compute the result?
    //1.Print the code banner
    printf("PHASE OF THE MOON\n");
    //2. Print code introduction
    printf("This program will calculate the phase of the moon for any date\n");
    printf("and time in hours. Full moon is 360 degrees, reducing to 180 degrees\n");
    printf("at new moon, and back to full moon at 0 degrees.\n");

    //3. Collect data information
    printf("\nEnter year: ");
    scanf("%d", &year);

    printf("Enter month (1-12): ");
    scanf("%d", &month);

    printf("Enter day: ");
    scanf("%d", &day);

    printf("Enter hour in 24-hour format: ");
    scanf("%d", &hour);

    printf("Enter timezone: ");
    scanf("%d", &timezone);

    //4. Calculate the julian date
    jd = (367 * year)-floor((7*(year + floor((month + 9)/12.0)))/4.0)+
         floor((275 * month)/9.0)+ day + (hour- timezone)/24.0 + 1721013.5;

    //5. Calculate the proportion of julian century
    t = (jd-2451545.0)/36525.0;

    //6. Calculate the  moon's mean elongation in degrees
    el = 297.8501921 + (445267.1114034 * t)-
        (0.0018819 * pow(t,2))+(pow(t,3))/545868.0 - (pow(t,4))/113065000.0;

    //7. calculate the moon's mean anomaly in degrees
    ma = 134.9633964 + (477198.8675055 * t)-
        (0.0087414 * pow(t,2))+(pow(t,3))/69699.0 - (pow(t,4))/14712000.0;

    //8. Calculate the  sun's mean anomaly in degrees
    sa = 357.5291092 + (35999.0502909* t) -(0.0001536 * pow(t,2))+(pow(t,3))/24490000.0;

    //9. Calculate the phase angle of the moon in degrees
    pa = 180.0 - el-(6.289* sin((ma* PI)/ 180.0 ))+(2.1*sin((sa*PI)/180.0))-
        (1.274*sin (((2*el)-ma)*(PI/180.0)))-(0.658*sin((2*el)*(PI/180.0)))-
        (0.214 *sin(2*ma*(PI/180.0 )))-(0.11*sin(el*(PI/180.0) ));

    //10.  Normalize the phase angle into the range [0..360] degrees
    pa = pa - floor(pa/360.0) * 360.0;

    //11. Print out result
    printf("\nPhase of the moon is %.0lf degrees.\n", pa);

    return 0;
}
