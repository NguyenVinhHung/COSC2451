/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 3 2012 Assignment #2
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
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

#define MENU_ERROR_MSG() printf("Menu file has error.\n"); return FAILURE;

int parseMenuFile(GJCType *, FILE *);
int parseSubmenuFile(GJCType *, FILE *);
int insertCategory(GJCType *, char *, char *, char *, char *);
int insertItem(GJCType *, char *, char *, char *, char *[], char *);
int strToPrice(char *, int *, int *);
int validateBasic(char *, int);
void exitByError(char *);
CategoryType *findCategoryById(GJCType *, char *);

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
    menu->headCategory = NULL;
    menu->numCategories = 0;

    return SUCCESS;
}


/****************************************************************************
* Loads all data into the system.
****************************************************************************/
int loadData(GJCType *menu, char *menuFile, char *submenuFile)
{
    FILE *mF, *smF; /* menu file & submenu file */

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
        return FAILURE;
    }

    if(parseMenuFile(menu, mF) == FAILURE)
    {
        printf("Menu file has error.\n");
        return FAILURE;
    }

    printf("Start parsing submenu file\n");

    if(parseSubmenuFile(menu, smF) == FAILURE)
    {
        printf("Submenu file has error.\n");
        return FAILURE;
    }

    fclose(mF);
    fclose(smF);

    return SUCCESS;
}

/* Parse the text from menu file */
int parseMenuFile(GJCType *menu, FILE *mF)
{    
    int len = ID_LEN + MAX_NAME_LEN + MAX_DESC_LEN + 3;  
    char record[500], *id, *type, *name, *desc;  

    fgets(record, len, mF);

    printf("\nStart parsing menu file\n\n");

    while(record != NULL) /* read each record */
    {
        id = strtok(record, "|");
        type = strtok(NULL, "|");
        name = strtok(NULL, "|");
        desc = strtok(NULL, "|");

	printf("%s - %s - %s - %s\n", id, type, name, desc);

        if(insertCategory(menu, id, type, name, desc) == FAILURE)
        {
            return FAILURE;
        }

        fgets(record, len, mF);
    }

    return SUCCESS;
}

/* Parse the text from submenu file */
int parseSubmenuFile(GJCType *menu, FILE *smF)
{
    char *record, *id, *cId, *name, *prices[3], *desc;
    int len = ID_LEN + MAX_NAME_LEN + MAX_DESC_LEN + 3;    

    record = NULL;

    fgets(record, len, smF);
    while(record != NULL) /* read each record */
    {
        id = strtok(record, "|");
        cId = strtok(NULL, "|");
        name = strtok(NULL, "|");
        prices[0] = strtok(NULL, "|");
        prices[1] = strtok(NULL, "|");
        prices[2] = strtok(NULL, "|");
        desc = strtok(NULL, "|");

        if(insertItem(menu, id, cId, name, prices, desc) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

/* Create & insert new CategoryType using the given parameters. */
int insertCategory(GJCType *menu, char *id, char *type, char *name, char *desc)
{
    CategoryType *ct, *cur, *prev; /*new, current, & previous*/
        
    /* check ID*/
    if(validateBasic(id, ID_LEN)==FAILURE || (id[0]<'A' || id[0]>'Z'))
    {
        /* MENU_ERROR_MSG(); */
        return FAILURE;
    }

    /* Parse category type */
    if(validateBasic(type, 1)==FAILURE || (type[0]!='H' && type[0]!='C'))
    {
        return FAILURE;
    }

    /* Parse category name */
    if(validateBasic(name, MAX_NAME_LEN) == FAILURE)
    {
        return FAILURE;
    }

    /* Parse category description */
    if(validateBasic(desc, MAX_DESC_LEN) == FAILURE) 
    {
        return FAILURE;
    }

    ct = (CategoryType *)malloc(sizeof(CategoryType));
    strcpy(ct->categoryID, id);
    ct->categoryType = *type;
    strcpy(ct->categoryName, name);
    strcpy(ct->categoryDescription, desc);

    ct->headItem = NULL;
    ct->numItems = 0;

    cur = menu->headCategory;
    prev = NULL;

    /* Find suitable position for the new category */
    while(cur!=NULL && strcmp(name, cur->categoryName)>0)
    {
        prev = cur;
        cur = cur->nextCategory;
    }

    /* Insert the new CategoryType */
    ct->nextCategory = cur;

    if(prev == NULL)
    {        
        menu->headCategory = ct;
    }
    else
    {
        prev->nextCategory = ct;
    }

    return SUCCESS;
}

/* Create & insert new ItemType using the given parameters. */
int insertItem(GJCType *menu, char *id, char *cId, char *name, 
                              char *prices[3], char *desc)
{
    ItemType *it, *cur, *prev; /*new, current, & previous*/
    CategoryType *ct; /* The category of this submenu */
    int dollar[3], cent[3], i;
    
    /* check ID */
    if(validateBasic(id, ID_LEN)==FAILURE || (id[0]<'A' || id[0]>'Z'))
    {
        /* MENU_ERROR_MSG(); */
        return FAILURE;
    }    

    /* Parse item ID */
    if(validateBasic(cId, 1)==FAILURE || (cId[0]!='H' && cId[0]!='C'))
    {
        return FAILURE;
    }

    /* Parse item name */
    if(validateBasic(name, MAX_NAME_LEN) == FAILURE)
    {
        return FAILURE;
    }

    /* Parse item description */
    if(validateBasic(desc, MAX_DESC_LEN) == FAILURE) 
    {
        return FAILURE;
    }

    ct = findCategoryById(menu, id);
    if(ct == NULL)
    {
        return FAILURE;
    }

    for(i=0; i<3; i++)
    {
        if(strToPrice(prices[i], &dollar[i], &cent[i]) == FAILURE)
        {
            return FAILURE;
        }
    }

    it = (ItemType *)malloc(sizeof(ItemType));
    strcpy(it->itemID, id);
    strcpy(it->itemName, name);
    strcpy(it->itemDescription, desc);    
    it->nextItem = NULL;
    
    for(i=0; i<3; i++)
    {
        it->prices[i].dollars = dollar[i];
        it->prices[i].cents = cent[i];
    }

    cur = ct->headItem;
    prev = NULL;

    /* Find suitable position for the new category */
    while(cur!=NULL && strcmp(name, cur->itemName)>0)
    {
        prev = cur;
        cur = cur->nextItem;
    }

    /* Insert new item */
    it->nextItem = cur;

    if(prev == NULL)
    {        
        ct->headItem = it;
    }
    else
    {
        prev->nextItem = it;
    }

    return SUCCESS;
}

int strToPrice(char *price, int *dollar, int *cent)
{
    float num; /*The price in float*/

    if(sscanf(price, "%f", &num) == EOF)
    {
        return FAILURE;
    }

    *dollar = (int)num;
    num -= *dollar;
    *cent = (int)(num * 100);

    printf("Dollar %d - Cent %d\n", *dollar, *cent);

    return SUCCESS;
}

int validateBasic(char *field, int maxLen)
{
    if(field==NULL || strlen(field)<1 || strlen(field)>maxLen)
    {
        return FAILURE;
    }
    return SUCCESS;
}

/****************************************************************************
* Deallocates memory used in the program.
****************************************************************************/
void systemFree(GJCType *menu)
{
    /* free(menu);*/
}

void exitByError(char *message)
{
    printf("%s \nProgram abort\n", message);
    exit(0);
}

/* Find category by ID */
CategoryType *findCategoryById(GJCType *menu, char *id)
{
    CategoryType *curr;
    curr = menu->headCategory;

    while(curr != NULL)
    {
        if(strcmp(curr->categoryID, id) == 0)
        {
            return curr;
        }

        curr = curr->nextCategory;
    }

    return NULL;
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
