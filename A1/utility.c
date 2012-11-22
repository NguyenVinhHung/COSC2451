/********************************************************************************
* COSC2541 - Programming Techniques
* Semester 2012C Assignment #1
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
*********************************************************************************/

#include "a1.h"
#include <string.h>

/* Function readRestOfLine() is used for buffer clearing */
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}

/*Print a string and then move to next line*/
void println(char *str)
{
	printf("%s\n", str);
}

/*Move to next line*/
void newln()
{
	printf("\n");
}

/*Print out the main menu.*/
void displayMenu()
{
	printf("Main Menu:\n");
	printf("1) ASCII/Hexadecimal/Binary table generator\n");
	printf("2) Simple clock display\n");
	printf("3) Current date/time display\n");
	printf("4) Converting a Roman numeral\n");
	printf("5) Minesweeper\n");
	printf("6) Session summary\n");
	printf("7) Exit\n");
	printf("Select your option: ");
}

/*Display a message to tell the user that the input option is invalid.*/
void displayMsgForInvalid()
{
	printf("This option is invalid.\n");
	printf("Please enter a valid option, which is from 1 to 7\n\n");
}

/*Display a message to tell the user that the input has error*/
void displayMsgForInputError(char *requirement)
{
	printf("Invalid input.\n");
	printf("Please enter %s, ", requirement);
	printf("or press Enter to go back to the menu.\n");
}

/*Check if there is no '\n' in the input, or the input has error.*/
int validateInput(char input[])
{
	if(!strchr(input, '\n') || input==NULL)
	{			
		readRestOfLine();
		return FALSE;
	}
	return TRUE;
}

/*Check if the user want to go back to the menu.
  TRUE if the input is only Enter.
*/
int isBackToMenu(char *str)
{
	if(*str == '\n')
	{
		return TRUE;
	}
	return FALSE;
}

int fromStringToInteger(char *str)
{
	int num = 0, i;
	printf("From STRING: %s LEN: %d ", str, strlen(str));
	for(i=0; i<strlen(str)-1; i++)
	{
		num *= 10;
		num += (int)(*(str+i) - 48);
	}
	printf("To INT: %d\n", num);
	return num;
}
