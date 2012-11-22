/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 2012C Assignment #1
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

/* Header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants. */
#define NUM_OPTION_STATS 6

/* This is used to compensate for the extra character spaces taken up by
   the '\n' and '\0' when user is asked for input through fgets(). */
#define EXTRA_SPACES 2

/* Specifies the maximum input length a user can enter for the options
   menu. */
#define MAX_OPTION_INPUT 1

/* Used for input validation. */
#define TRUE 1
#define FALSE 0

/* Constants for clock array parameters. */
#define CLOCK_WIDTH 18
#define CLOCK_HEIGHT 9
#define CLOCK_TICKS 13

/*
#ifndef println(a)
#define println(a) printf("%s\n", a)
#endif

#ifndef println()
#define println() printf("\n")
#endif
*/


/* Function prototypes. */
void asciiTranslation(int*, char*);
int displayClock(int*, int, int);
void displayClock2(int*);
void convertRomanNumeral(int*, char *);
void minesweeper(int*, int, int, int);
void sessionSummary(int*);

/* My defined utility function prototypes. */
void readRestOfLine();
void newln();
void println(char *);
void displayMenu();
void displayMsgForInvalid();
void displayMsgForInputError(char *);
int validateInput(char *);
int fromStringToInteger(char *);
