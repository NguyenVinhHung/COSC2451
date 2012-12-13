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

   /* Deallocate all dynamically allocated memory. */
   systemFree(&gjc);

   exit(EXIT_SUCCESS);

}
