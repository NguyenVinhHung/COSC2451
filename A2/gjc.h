/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 3 2012 Assignment #2
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

#ifndef GJC_H
#define GJC_H

/* System-wide header files. */
#include <stdio.h>
#include <stdlib.h>

/* System-wide constants. */
#define ID_LEN 5
#define MIN_NAME_LEN 1
#define MAX_NAME_LEN 25
#define MIN_DESC_LEN 1
#define MAX_DESC_LEN 250
#define NUM_PRICES 3
#define HOT 'H'
#define COLD 'C'

#define SUCCESS 1
#define FAILURE 0

typedef struct category *CategoryTypePtr;
typedef struct item *ItemTypePtr;

/* Structure definitions. */
typedef struct price
{
   unsigned dollars;
   unsigned cents;
} PriceType;

typedef struct item
{
   char itemID[ID_LEN + 1];
   char itemName[MAX_NAME_LEN + 1];
   PriceType prices[NUM_PRICES];
   char itemDescription[MAX_DESC_LEN + 1];
   ItemTypePtr nextItem;
} ItemType;

typedef struct category
{
   char categoryID[ID_LEN + 1];
   char categoryName[MAX_NAME_LEN + 1];
   char categoryType; /* (H)ot or (C)old. */
   char categoryDescription[MAX_DESC_LEN + 1];
   CategoryTypePtr nextCategory;
   ItemTypePtr headItem;
   unsigned numItems;
} CategoryType;

typedef struct gjc
{
   CategoryTypePtr headCategory;
   unsigned numCategories;
} GJCType;

#endif
