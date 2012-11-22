/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 2012C Assignment #1
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"a1.h"

#define ASCII_TRANS 1
#define SIMPLE_CLOCK 2
#define CURR_TIME 3
#define CONVERT_ROMAN_NUM 4
#define MINESWEEPER 5
#define SESSION_SUMMARY 6

#define BACK_TO_MENU(a) if(isBackToMenu(a)==TRUE){return;}

int inputOption();
void option1();
void option2();

int main(void)
{
    int optionStats[NUM_OPTION_STATS];
	/*The option which will receive input from user*/
	int option;

	do
	{		
		displayMenu();
		option = inputOption();		

		if(option == FALSE)
		{
			displayMsgForInvalid();
		}

		switch(option)
		{
			case ASCII_TRANS: option1(); break;
			case SIMPLE_CLOCK: option2(); break;
			case CURR_TIME: ; break;
			case CONVERT_ROMAN_NUM: ; break;
			case MINESWEEPER: ; break;
			case SESSION_SUMMARY: ; break;
		}
		
	} while(option != 7);
		
    return EXIT_SUCCESS;
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
	if(validateInput(opt) == FALSE)
	{
		return FALSE;
	}
	
	/* 
	  Check if the input is invalid, which is less than 1,
	  bigger than 7, or not a number.
	*/	
	if(*opt<'1' || *opt>'7'|| *(opt+1)!='\n')
	{
		return FALSE;
	}

	option = (int)*opt - 48;

	/*
	if(scanf("%d", &option) != 1)
	{
		readRestOfLine();
		return FALSE;
	}

	readRestOfLine();

	if(option<1 || option>7)
	{
		return FALSE;
	}
	*/

	return option;
}

void option1()
{	
	char input[6 + EXTRA_SPACES];	
	
	printf("\nASCII to binary and hexadecimal table generator\n");
	printf("-----------------------------------------------\n");

	while(1)
	{
		printf("Enter a string (1-5 characters), or press Enter to go back: ");

		fgets(input, 6 + EXTRA_SPACES, stdin);

		/* Check if there's an error in the input */
		if(validateInput(input) == FALSE)
		{
			/*printf("Invalid input.\n");
			printf("Please enter a string with the length from 1 to 5 characters, ");
			printf("or press Enter to go back to the menu.\n");*/
			displayMsgForInputError("a string with the length from 1 to 5 characters");
			continue;
		}

		/* Back to menu if the input is only Enter*/
		/*
		if(isBackToMenu(input) == TRUE)
		{
			return;
		}
		*/
		BACK_TO_MENU(input);
	
		asciiTranslation(0, input);
		return;
	}
}

void option2()
{
	int h, m; /*hour, and minute*/
	char hChar[5 + EXTRA_SPACES], mChar[3 + EXTRA_SPACES]; /*hour and minute in char*/

	printf("\nSimple clock display\n");
	printf("--------------------\n");

	while(1)
	{
		printf("Enter <hours> <minutes>, or press Enter to go back: ");

		fgets(hChar, 5 + EXTRA_SPACES, stdin);

		/* Check if there's an error in the input of hour character */
		/*
		if(validateInput(hChar) == FALSE)
		{
			displayMsgForInputError("an hour number");
			continue;
		}

		/* Back to menu if the input is only Enter*/
		/*
		if(isBackToMenu(hChar) == TRUE)
		{
			return;
		}

		fgets(mChar, 3 + EXTRA_SPACES, stdin);

		/* Check if there's an error in the input of hour character */
		/*
		if(validateInput(mChar) == FALSE)
		{
			displayMsgForInputError("a minute number");
			continue;
		}

		/* Back to menu if the input is only Enter*/
		/*
		if(isBackToMenu(mChar) == TRUE)
		{
			return;
		}*/
		
		scanf("%d%d", &h, &m);
		readRestOfLine();

		/*
		h = fromStringToInteger(hChar);
		m = fromStringToInteger(mChar);*/

		if(displayClock(0, h, m) == FALSE)
		{
			printf("Please enter valid numbers for both hour and minute.\n\n");
		}

		return;
	}
}
