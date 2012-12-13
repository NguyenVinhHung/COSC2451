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

int main(int argc, char* argv[])
{
    GJCType gjc;

    int initFlag, dataFlag;

    /* Initialise the Gloria Jean's Coffee system to a safe empty state. */
    initFlag = systemInit(&gjc);

    /* Populate the Gloria Jean's Coffee system with data from the data files. */
    /* Uncomment this line when you are ready to use command line arguments:
    dataFlag = loadData(&gjc, argv[1], argv[2]); */

    /* Testing to see if both systemInit(.) and loadData(.) are ok */
    if (initFlag == FAILURE || dataFlag == FAILURE)
        exit(EXIT_FAILURE);

    /* Interactive menu providing user with access to the 9 menu options */
    do
    {		
	displayMenu();
	option = inputOption();		

	if(option == FALSE)
	{
	    printf("This option is invalid.\n");
	    printf("Please enter a valid option, which is from 1 to 9\n\n");
	}

	switch(option)
	{
	    case 1: option1(optionStats); break;
            case 2: option2(optionStats+1); break;
	    case 3: displayClock2(optionStats+2); break;
	    case 4: option4(optionStats+3); break;
	    case 5: option5(optionStats+4); break;
	    case 6: sessionSummary(optionStats); break;
            case 7: option4(optionStats+3); break;
	    case 8: option5(optionStats+4); break;
	    case 9: exit(EXIT_SUCCESS);
        }
    } while(option != 7);

    /* Deallocate all dynamically allocated memory. */
    systemFree(&gjc);

    exit(EXIT_SUCCESS);

}
