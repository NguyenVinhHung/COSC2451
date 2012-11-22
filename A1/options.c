/***************************************************************************
* COSC2541 - Programming Techniques
* Semester 2012C Assignment #1
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
***************************************************************************/

#include "a1.h"

/* This source file contains important functions to be developed and
 * used by various menu options, as indicated. Note that every
 * function has as its first parameter the optionsStats array, which
 * will be appropriately updated for later reporting of menu option 6.
 * You may ignore this parameter and its relevance to each function
 * until you develop the sessionSummary() function.
 */


/* Function asciiToBinary() converts a given character (inputChar) to
 * its 8-bit binary equivalent, stored as a string of 0s and 1s in
 * binaryString. This function will be used in menu option 1.
 */
void asciiToBinary(char inputChar, char *binaryString)
{
	/* The decimal value of the input char */
	int dec = (int)inputChar;
	int i;		
	char tmp;

	for(i=0; i<8; i++)
	{
		*(binaryString+i) = (dec % 2) + 48;
		dec /= 2;
	}

	for(; i >= 4; i--)
	{
		tmp = *(binaryString + 7-i);
		*(binaryString + 7-i) = *(binaryString + i);
		*(binaryString + i) = tmp;		
	}

	*(binaryString+8) = '\0';
}

/* Convert an integer to hexadecimal character */
char fromDecToHexChar(int dec)
{
	if(dec > 9) {
		return (char)(dec + 55);
	}
	else
	{
		return (char)(dec + 48);
	}
}

/* Function asciiToHexadecimal() converts a given character (inputChar) to
 * its hexadecimal (base 16) equivalent, stored as a string of
 * hexadecimal digits in hexString. This function will be used in menu
 * option 1.
 */
void asciiToHexadecimal(char inputChar, char *hexString)
{
	/* The decimal value of the input char */
	int dec = (int)inputChar;
	int secondChar = dec % 16;
	int firstChar = dec / 16;

	*hexString = fromDecToHexChar(firstChar);
	*(hexString + 1) = fromDecToHexChar(secondChar);
	*(hexString + 2) = '\0';
}


/* Function asciiTranslation() converts each character in a string
 * (asciiString) into its ascii, binary and hexadecimal form. For the
 * given string you are required to generate a table with three
 * columns. Each character of the string should be displayed in the
 * first column, with the other two columns containing the
 * corresponding binary and hexadecimal representations of the
 * character. You must use the two function prototypes provided above
 * for translation. This function will be used in menu option 1.
 */
void asciiTranslation(int *optionStats, char *asciiString)
{
	char binaryStr[9];
	char hexStr[3];
	int i;
	
	printf("Character\tBinary\t\tHexadecimal\n");
	
	for(i=0; *(asciiString+i) != '\n'; i++)
	{
		asciiToBinary(*(asciiString+i), binaryStr);
		asciiToHexadecimal(*(asciiString+i), hexStr);
		
		printf("%c\t\t%s\t\t%s\n", *(asciiString+i), binaryStr, hexStr);
	}

	printf("\n");
}


/* Function displayClock() will display a clock as per menu option 2,
 * using the hours and minutes arguments. These are assumed to reflect
 * 24-hour time, or else the function returns an error code. This
 * function has been partially written for you. This function will be
 * used in menu option 2. (A test driver for displayClock() is
 * provided in the file dc.c, which may be compiled separately.
 */
int displayClock(int *optionStats, int h, int m)
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
								 /*  1,  2,  3,  4,  5, 6, 7, 8, 9, 10,11,12 */

    /* Hour and minute codes */
    const char hs = 'H', ms = 'm';

    int i, j; /* Declare other variables as needed */

    /* The next 5 comments require code to be developed by you! */

    /* Ensure that h and m are in range and, if not, return
     * appropriate error value. Otherwise adjust h if it is 0 or it
     * exceeds 12
     */

	if(h<0 || h>12 || m<0 || m>59) {
		return FALSE;
	}

	/* If h=0, get the position of number 12 */
	if(h == 0)
	{
		h = 12;
	}

	m = (m+2) / 5; /* Get the nearest number of the minute */

	/* If m=0, get the position of number 12 */
	if(m == 0)
	{
		m = 12;
	}

	if(h == m)
	{
		*(*(clock+hr[h]) + hc[h]) = ms;
		*(*(clock+hr[h]) + hc[h]+1) = hs;
	}
	else 
	{
		*(*(clock+hr[h]) + hc[h]) = hs;
		*(*(clock+hr[h]) + hc[h]+1) = hs;
		*(*(clock+hr[m]) + hc[m]) = ms;
		*(*(clock+hr[m]) + hc[m]+1) = ms;
	}
	

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

    return TRUE;
}


/* Function displayClock2() will display a clock as per menu option 2,
 * but after first obtaining and displaying the current date/time in
 * text form (as per date command). Apart from adding code to display
 * the text date/time, its remaining functionality will be identical
 * to displayClock(). This function will be used in menu option 3.
 */
void displayClock2(int *optionStats)
{
}



/* This function converts a Roman numeral into its decimal equivalent.
 * The function prompts the user for a Roman numeral, which is entered
 * as a character string. The function first converts the Roman numeral
 * to decimal and then prints the decimal numeral. The function halts
 * when the user enters a string that is not a valid Roman numeral.
 * This function will be used in menu option 4.
 */
void convertRomanNumeral(int *optionStats, char *romanNumeral)
{
}


/* Function minesweeper() creates a field of N x M for the game of
 * minesweeper. The function first reads in integers N and M, and the
 * number of mines allowed, then output a field of the same size,
 * with the "." characters replaced by the number of mines adjacent to
 * that square. Note that the mine squares are randomly placed on the field.
 * (see requirement#6 for an example). This function will be used in
 * menu option 5.
 */
void minesweeper(int *optionStats, int n, int m, int numMines)
{
}


/* See requirement #7  "Session summary" of the assignment specs.
 * Function sessionSummary() reports the program usage.
 */
void sessionSummary(int *optionStats)
{
}
