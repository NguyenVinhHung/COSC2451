/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 3 2012 Assignment #2
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

#ifndef GJC_OPTIONS_H
#define GJC_OPTIONS_H

/* Function prototypes. */
void displaySummary(GJCType*, char);
void categoryReport(GJCType*);
void addCategory(GJCType*);
void deleteCategory(GJCType*);
void addItem(GJCType*);
void deleteItem(GJCType*);
void saveData(GJCType*, char*, char*);

#endif
