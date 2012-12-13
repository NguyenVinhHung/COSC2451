/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 3 2012 Assignment #2
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

#ifndef GJC_UTILITY_H
#define GJC_UTILITY_H

/* Function prototypes. */
void readRestOfLine();
int systemInit(GJCType*);
int loadData(GJCType*, char*, char*);
void systemFree(GJCType*);
void displayMenu();
int validateInput(char *);
int inputOption();

#endif
