/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 3 2012 Assignment #2
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

#include "gjc.h"
#include "gjc_options.h"
#include "gjc_utility.h"

/****************************************************************************
* Function readRestOfLine() is used for buffer clearing.
* Please refer to "test_fgets.c" on Blackboard:
* "Course Documents"->"Function Examples"->"Input Validation Examples"
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}


/****************************************************************************
* Initialises the system to a safe empty state.
****************************************************************************/
int systemInit(GJCType *menu)
{
}


/****************************************************************************
* Loads all data into the system.
****************************************************************************/
int loadData(GJCType *menu, char *menuFile, char *submenuFile)
{
}


/****************************************************************************
* Deallocates memory used in the program.
****************************************************************************/
void systemFree(GJCType *menu)
{
}

/* Display the main menu */
void displayMenu()
{
	printf("Main Menu:\n");
	printf("(1) Hot Drinks Summary\n");
	printf("(2) Cold Drinks Summary\n");
	printf("(3) Detailed Menu Report\n");
	printf("(4) Add Menu Category\n");
	printf("(5) Delete Menu Category\n");
	printf("(6) Add Menu Item\n");
	printf("(7) Delete Menu Item\n");
	printf("(8) Save & Exit\n");
	printf("(9) Abort\n");
	printf("Select your option (1-9): ");
}
