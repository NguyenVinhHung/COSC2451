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
void writeDesc(FILE *, char *);
int strToPrice(char *, int *, int *);
int idToInt(char *);
int validateBasic(char *, int);
void exitByError(char *);


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

    /* Abort program if at least one file can't be opened*/
    if(mF==NULL || smF==NULL)
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

    /* fgets(record, len, mF); */

    printf("\nStart parsing menu file\n\n");

    while(fgets(record, len, mF) != NULL) /* read each record */
    {
        id = strtok(record, "|");
        type = strtok(NULL, "|");
        name = strtok(NULL, "|");
        desc = strtok(NULL, "|");

        if(insertCategory(menu, id, type, name, desc) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

/* Parse the text from submenu file */
int parseSubmenuFile(GJCType *menu, FILE *smF)
{
    int len = ID_LEN + MAX_NAME_LEN + MAX_DESC_LEN + 3;    
    char record[500], *id, *cId, *name, *prices[NUM_PRICES], *desc;
    
    while(fgets(record, len, smF) != NULL) /* read each record */
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
    CategoryTypePtr ct, cur, prev; /*new, current, & previous*/
        
    /* check ID*/
    if(validateBasic(id, ID_LEN)==FAILURE || id[0]!='C')
    {
        /* MENU_ERROR_MSG(); */
printf("1");
        return FAILURE;
    }

    /* Parse category type */
    if(validateBasic(type, 1)==FAILURE || (type[0]!='H' && type[0]!='C'))
    {
printf("2");
        return FAILURE;
    }

    /* Parse category name */
    if(validateBasic(name, MAX_NAME_LEN) == FAILURE)
    {
printf("3");
        return FAILURE;
    }

    /* Parse category description */
    if(validateBasic(desc, MAX_DESC_LEN) == FAILURE) 
    {
printf("4");
        return FAILURE;
    }

    ct = (CategoryTypePtr)malloc(sizeof(CategoryType));
    strcpy(ct->categoryID, id);
    ct->categoryType = *type;
    strcpy(ct->categoryName, name);
    strcpy(ct->categoryDescription, strtok(desc, "\n"));

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

/* printf("%s - %s - %c - %s\n", ct->categoryID, ct->categoryName, 
				ct->categoryType, ct->categoryDescription); */
    menu->numCategories = menu->numCategories + 1;
    return SUCCESS;
}

/* Create & insert new ItemType using the given parameters. */
int insertItem(GJCType *menu, char *id, char *cId, char *name, 
                              char *prices[NUM_PRICES], char *desc)
{
    ItemTypePtr it, cur, prev; /*new, current, & previous*/
    CategoryTypePtr ct; /* The category of this submenu */
    int dollar[NUM_PRICES], cent[NUM_PRICES], i;
    
    /* check ID */
    if(validateBasic(id, ID_LEN)==FAILURE || id[0]!='I')
    {
        /* MENU_ERROR_MSG(); */
printf("1\n");
        return FAILURE;
    }    

    /* Parse category ID */
    if(validateBasic(cId, ID_LEN)==FAILURE || (cId[0]!='H' && cId[0]!='C'))
    {
printf("2\n");
        return FAILURE;
    }

    /* Parse item name */
    if(validateBasic(name, MAX_NAME_LEN) == FAILURE)
    {
printf("3\n");
        return FAILURE;
    }

    /* Parse item description */
    if(validateBasic(desc, MAX_DESC_LEN) == FAILURE) 
    {
printf("4\n");
        return FAILURE;
    }

    ct = findCategoryById(menu, cId);
    if(ct == NULL)
    {
printf("5\n");
        return FAILURE;
    }

    for(i=0; i<NUM_PRICES; i++)
    {
        if(strToPrice(prices[i], &dollar[i], &cent[i]) == FAILURE)
        {
printf("6\n");
            return FAILURE;
        }
    }

    it = (ItemType *)malloc(sizeof(ItemType));
    strcpy(it->itemID, id);
    strcpy(it->itemName, name);
    strcpy(it->itemDescription, strtok(desc, "\n"));
    it->nextItem = NULL;
    
    for(i=0; i<NUM_PRICES; i++)
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

/* printf("%s + %s + %s + %d + %d + %d + %s\n", it->itemID, it->itemName, cId,
	     it->prices[0].dollars, it->prices[1].dollars, 
		it->prices[2].dollars, it->itemDescription); */
    ct->numItems = ct->numItems + 1;
    return SUCCESS;
}

/* Convert a price as a string into an integer */
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

/* printf("Dollar %d - Cent %d\n", *dollar, *cent); */

    return SUCCESS;
}

/* Convert the 4 digits of an ID into an integer */
int idToInt(char *id)
{
    int i, j;
    char num[5];

    for(i=1; i<5; i++)
    {
        if(*(id+i) != '0')
        {
            break;
        }
        if(i == 4)
        {
            return 0;
        }
    }

    for(j=0; i<5; i++, j++)
    {
        num[j] = *(id+i);
    }

    num[j] = '\n';

    return atoi(num);
}

/* Generate new category ID */
void generateCategoryId(GJCType *menu, char id[ID_LEN + 1])
{
    CategoryTypePtr c = menu->headCategory;    
    int i, j;

    i = 0;
    while(c != NULL)
    {
        j = idToInt(c->categoryID);
        printf("C%04d\n", j);

        if(i < j)
        {
            i = j;
        }
        c = c->nextCategory;
    }

    i++;
    snprintf(id, ID_LEN + 1, "C%04d", i);
}

/* Generate new item ID */
void generateItemId(GJCType *menu, ItemTypePtr  item, char id[ID_LEN + 1])
{
    int i, j;

    i = 0;
    while(item != NULL)
    {
        j = idToInt(item->itemID);
        printf("I%04d\n", j);

        if(i < j)
        {
            i = j;
        }
        item = item->nextItem;
    }

    i++;
    snprintf(id, ID_LEN + 1, "I%04d", i);
}

/* Write detailed menu report to file */
void writeMenuReport(CategoryTypePtr category)
{
    char *fileName = malloc(sizeof(char) * 13);
    FILE *file;
    ItemTypePtr curr;
    int i;

    curr = category->headItem;
    
    strcpy(fileName, category->categoryID);
    strcat(fileName, ".report"); /*File name's format is <category ID>.report*/
    file = fopen(fileName, "w");

    fprintf(file, "Category %s – %s – Detailed Report\n", 
                category->categoryID, category->categoryName);
    fprintf(file, 
            "-------------------------------------------------------------\n");

    /* Write data of each item to file */
    while(curr != NULL)
    {
        fprintf(file, "Item ID  : %s\n", curr->itemID);
        fprintf(file, "Item Name: %s\n", curr->itemName);
        fprintf(file, "Prices   :");

        for(i=0; i<NUM_PRICES; i++)
        {
            fprintf(file, " $%d.%d", 
                          curr->prices[i].dollars, curr->prices[i].cents);
        }
        fprintf(file, "\n");

        writeDesc(file, curr->itemDescription);

        fprintf(file, "\n\n");
        curr = curr->nextItem;
    }

    fclose(file);
    printf("File %s has been created.\n\n", fileName);

    free(fileName);
}

/* Write item description to file */
void writeDesc(FILE *file, char *desc)
{
    char *word, data[MAX_DESC_LEN + 1];
    int lineLen;

    lineLen = 14;
    strcpy(data, desc);
    word = strtok(data, " ");
    fprintf(file, "Description : ");

    /* Print each word to the file. If the length of current line reach 78,
       move to next line. */
    while(word != NULL)
    {
        lineLen += strlen(word) + 1;

        if(lineLen >= MAX_LEN_LINE)
        {
            fprintf(file, "\n");
            lineLen = 0;
        }

        fprintf(file, "%s ", word);
        
        word = strtok(NULL, " ");
    }
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
    CategoryTypePtr curr, prev;

    curr = menu->headCategory;

    while(curr != NULL)
    {
        prev = curr;
        curr = curr->nextCategory;
        freeCatagory(prev);
    }
}

void freeCatagory(CategoryTypePtr c)
{
    ItemTypePtr prev, curr;
    curr = c->headItem;

    while(curr != NULL)
    {
        prev = curr;
        curr = curr->nextItem;
        free(prev);
    }

    free(c);
}

int freeItem(CategoryTypePtr c, char *itemId)
{    
    ItemTypePtr prev, curr;
    
    curr = c->headItem;
    prev = NULL;

    while(curr != NULL)
    {
        if(strcmp(itemId, curr->itemID) == 0)
        {
            break;
        }
        prev = curr;
        curr = curr->nextItem;        
    }

    if(curr == NULL)
    {
        return FAILURE;
    }
    else if(prev == NULL) 
    {
        c->headItem = curr->nextItem;
    }
    else
    {
        prev->nextItem = curr->nextItem;
    }

    printf("Menu item “%s – %s” deleted from system.\n", 
                                              curr->itemID, curr->itemName);
    free(curr);    
    return SUCCESS;
}

void exitByError(char *message)
{
    printf("%s \nProgram abort\n", message);
    exit(0);
}

/* Find category by ID */
CategoryTypePtr findCategoryById(GJCType *menu, char *id)
{
    CategoryTypePtr curr;
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

void displayCategory(CategoryTypePtr ct)
{
    ItemTypePtr curr = ct->headItem;
    float prices[3];
    int i;

    printf("\n%s - %s (%d items)\n", 
                             ct->categoryID, ct->categoryName, ct->numItems);
    printf("-------------------------------------------------\n");
    printf("ID    Name                      Small Med   Large\n");
    printf("----- ------------------------- ----- ----- -----\n");

    while(curr != NULL)
    {
        for(i=0; i<3; i++)
        {
            prices[i] = (float)(curr->prices[i].dollars);
            prices[i] += ((float)(curr->prices[i].cents)) / 100;
        }

        /* printf("%s %-25s $%d.%-2d $%d.%-2d $%d.%-2d\n", 
                curr->itemID, curr->itemName,
	        curr->prices[0].dollars, curr->prices[0].cents, 
                curr->prices[1].dollars, curr->prices[1].cents, 
		curr->prices[2].dollars, curr->prices[2].cents); */
        printf("%s %-25s $%-4.2f $%-4.2f $%-4.2f\n", 
                curr->itemID, curr->itemName, prices[0], prices[1], prices[2]);
        curr = curr->nextItem;
    }
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

/*Check if the user want to go back to the menu.
  TRUE if the input is only Enter.
*/
int isBackToMenu(char *str)
{
    if(*str == '\n')
    {
        return SUCCESS;
    }
    return FAILURE;
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
