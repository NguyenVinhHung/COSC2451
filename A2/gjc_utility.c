/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 3 2012 Assignment #2
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

#include <string.h>
#include "gjc.h"
#include "gjc_options.h"
#include "gjc_utility.h"

/* This is used to compensate for the extra character spaces taken up by
   the '\n' and '\0' when user is asked for input through fgets(). */
#define EXTRA_SPACES 2

/* Specifies the maximum input length a user can enter for the options
   menu. */
#define MAX_OPTION_INPUT 1

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
    FILE *mF, *smF; /* menu file & submenu file */
    char *mRec, *smRec; /* menu record (4 fields) & submenu record (7 fields) */

    mF = fopen(menuFile, "r");
    smF = fopen(submenuFile, "r");

    if(mF==NULL) /* Print message if menu file cannot be opened */
    {
        printf("Menu file cannot be opened\n");
    }

    if(smF==NULL) /* Print message if submenu file cannot be opened */
    {
        printf("Submenu file cannot be opened\n");
    }

    if(mF==NULL || smF==NULL) /* Abort program if at least one file can't be opened*/
    {
        printf("Program abort\n");
        exit(0);
    }

    

    fclose(mF);
    fclose(smF);
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
    printf("\nMain Menu:\n");
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

/*Check if there is no '\n' in the input, or the input has error.*/
int validateInput(char input[])
{
    if(!strchr(input, '\n') || input==NULL)
    {			
        readRestOfLine();
        return FAILURE;
    }
    return SUCCESS;
}

/*
  Let the user input which option they'd like to use.
  If the input is invalid, return FALSE. Otherwise, return 
  the option number.
*/
int inputOption()
{	
    char opt[MAX_OPTION_INPUT + EXTRA_SPACES];
    int option;

    fgets(opt, MAX_OPTION_INPUT + EXTRA_SPACES, stdin);

    /* Check if there's an error in the input */
    if(validateInput(opt) == FAILURE)
    {
        return FAILURE;
    }

    /* 
      Check if the input is invalid, which is less than 1,
      bigger than 7, or not a number.
    */	
    if(*opt<'1' || *opt>'9'|| *(opt+1)!='\n')
    {
        return FAILURE;
    }

    option = (int)*opt - 48;

    return option;
}
