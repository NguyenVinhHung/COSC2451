/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 2012C Assignment #1
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOCK_HEIGHT 9
#define CLOCK_WIDTH 18
#define CLOCK_TICKS 13

int displayClock(int hours, int minutes);

/* This is a test program for displayClock(). It is provided for your
 * information and to understand how the displayClock() function is
 * invoked.
 */
int main()
{
    int h, m;
    int display_error, end_of_input;

    /* Note: You should __never__ call scanf in real code.
     * This is quick for testing. */

    printf("\nEnter <hours> <minutes>: ");
    scanf("%d%d", &h, &m);

    display_error = displayClock(h, m);
    if (display_error)
        printf("Incorrect data received for hours and minutes\n");

    return 0;
}

int displayClock(int h, int m)
{
    /* The array to hold the hard-coded clock. Note: +1 for \0 */
    char clock[CLOCK_HEIGHT][CLOCK_WIDTH + 1] = {
        "        12        ",
        "   11        01   ",
        " 10            02 ",
        "                  ",
        "09      .       03",
        "                  ",
        " 08            04 ",
        "   07        05   ",
        "        06        "
    };

    /* Row and column numbers in clock array for hour positions. For
     * example, the "06" in the clock display is stored at position
     * [8, 8] in the clock matrix (see above) */
    const int hr[CLOCK_TICKS] = {0,  1,  2,  4,  6,  7, 8, 7, 6, 4, 2, 1, 0};
    const int hc[CLOCK_TICKS] = {0, 13, 15, 16, 15, 13, 8, 3, 1, 0, 1, 3, 8};

    /* Hour and minute codes */
    const char hs = 'H', ms = 'm';

    int i, j; /* Declare other variables as needed */

    /* The next 5 comments require code to be developed by you! */

    /* Ensure that h and m are in range and, if not, return
     * appropriate error value. Otherwise adjust h if it is 0 or it
     * exceeds 12
     */

    /* Now update the clock array accordingly, with the hour symbol */

    /* Round m to the nearest hour position */

    /* Update clock with minute symbol, taking into account a "clash"
     * with the hour symbol
     */

    /* Display the clock */
    for (i = 0; i < CLOCK_HEIGHT; i++)
    {
        for (j = 0; j < CLOCK_WIDTH; j++)
    	    printf("%c", clock[i][j]);
        printf("\n");
    }
    printf("\n");

    return 0;
}

