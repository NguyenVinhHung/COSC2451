/****************************************************************************
* COSC2541 - Programming Techniques
* Semester 3 2012 Assignment #2
* Full Name        : Nguyen Vinh Hung
* Student Number   : s3342128
* Start up code provided by Christopher Hoobin, Xiaodong Li and Quang Tran
****************************************************************************/

#include <string.h>
#include <stdio.h>
#include "gjc.h"
#include "gjc_options.h"
#include "gjc_utility.h"

/****************************************************************************
* Menu option #1: Display Summary
* Allows the user to display a summary of all hot or cold drink categories
* and items.
****************************************************************************/
void displaySummary(GJCType *menu, char categoryType)
{
    CategoryTypePtr curr = menu->headCategory;

    if(categoryType == 'H')
    {
        printf("\nHot ");
    }
    else if(categoryType == 'C')
    {
        printf("\nCold ");
    }

    printf("Drinks Summary\n");
    printf("-------------------\n");

    while(curr != NULL)
    {
        if(curr->categoryType == categoryType)
        {
            displayCategory(curr);
        }

        curr = curr->nextCategory;
    }
}


/****************************************************************************
* Menu option #2: Category Report
* Allows the user to make a new report file for a chosen category.
****************************************************************************/
void categoryReport(GJCType *menu)
{
    CategoryTypePtr category;
    char categoryID[ID_LEN + EXTRA_SPACES], *cId;

    while(1)
    {
        printf("\nDetailed Menu Report\n");
        printf("--------------------\n");
        printf("Enter category id (5 characters): ");

        fgets(categoryID, ID_LEN + EXTRA_SPACES, stdin);

        /* Check if there's an error in the input */
        if(validateInput(categoryID) == FAILURE)
        {
            printf("A category ID must have 5 character. Please try again.\n");
            continue;
        }

        /* Back to menu if the input is only Enter */
        BACK_TO_MENU(categoryID);
	
        cId = strtok(categoryID, "\n");
        category = findCategoryById(menu, cId);
        if(category == NULL)
        {
            printf("This category ID does not exist. Please try again.\n");
            continue;
        }

        writeMenuReport(category);

        return;
    }
}


/****************************************************************************
* Menu option #3: Add Category
* Allows the user to add a new category record to the linked list.
****************************************************************************/
void addCategory(GJCType *menu)
{
    char name[MAX_NAME_LEN + EXTRA_SPACES], type[1 + EXTRA_SPACES];
    char desc[MAX_DESC_LEN + EXTRA_SPACES], id[ID_LEN + 1];

    snprintf(id, ID_LEN + 1, "C%04d", menu->numCategories+1);

    printf("\nAdd Menu Category\n");
    printf("-----------------\n");
    printf("New category ID is %s\n", id);

    while(1)
    {
        /* Input category name & validate it */
        while(1)
        {
            printf("Category Name (1-25 characters): ");
            fgets(name, MAX_NAME_LEN + EXTRA_SPACES, stdin);

            /* Check if there's an error in the input */
            if(validateInput(name) == FAILURE)
            {
                printf("A category name must have 1 - 25 characters.\n");
                printf("Please try again.\n");
                continue;
            }

            /* Back to menu if the input is only Enter */
            BACK_TO_MENU(name);
            break;
        }

        /* Input category type & validate it */
        while(1)
        {
            printf("(H)ot or (C)old drink?: ");
            fgets(type, 1 + EXTRA_SPACES, stdin);

            /* Check if there's an error in the input */
            if(validateInput(type) == FAILURE)
            {
                printf("A category type must be (H)ot or (C)old.\n");
                printf("Please try again.\n");
                continue;
            }

            /* Back to menu if the input is only Enter */
            BACK_TO_MENU(type);

            if(*type!='H' && *type!='C')
            {
                printf("A category type must be (H)ot or (C)old.\n");
                printf("Please try again.\n");
                continue;
            }
            break;
        }

        /* Input category description & validate it */
        while(1)
        {
            printf("Description (1-250 characters): ");
            fgets(desc, MAX_DESC_LEN + EXTRA_SPACES, stdin);

            /* Check if there's an error in the input */
            if(validateInput(desc) == FAILURE)
            {
                printf("A category description must have 1 - 250 characters.\n");
                printf("Please try again.\n");
                continue;
            }

            /* Back to menu if the input is only Enter */
            BACK_TO_MENU(desc);
            break;
        }

        strcpy(type, strtok(type, "\n"));
        strcpy(name, strtok(name, "\n"));
        strcpy(desc, strtok(desc, "\n"));
        if(insertCategory(menu, id, type, name, desc) == FAILURE)
        {
            printf("Invalid input.\n");
            printf("Please try again.\n");
            continue;
        }

        printf("Adding new Category successful\n\n");
        break;
    }
}


/****************************************************************************
* Menu option #4: Delete Category
* Deletes a category and all corresponding items.
****************************************************************************/
void deleteCategory(GJCType *menu)
{
    CategoryTypePtr prev, curr;
    char categoryID[ID_LEN + EXTRA_SPACES], *cId;

    printf("\nDelete Menu Category\n");
    printf("--------------------\n");
    printf("Warning: All menu item data for a menu category will be\n");
    printf("deleted if you proceed.\n");

    while(1)
    {
        printf("Menu category ID: ");

        fgets(categoryID, ID_LEN + EXTRA_SPACES, stdin);

        /* Check if there's an error in the input */
        if(validateInput(categoryID) == FAILURE)
        {
            printf("A category ID must have 5 character. Please try again.\n");
            continue;
        }

        /* Back to menu if the input is only Enter */
        BACK_TO_MENU(categoryID);
	
        cId = strtok(categoryID, "\n");        
        curr = menu->headCategory;
        prev = NULL;

        while(curr != NULL)
        {
            if(strcmp(curr->categoryID, cId) == 0)
            {
                break;
            }
            prev = curr;
            curr = curr->nextCategory;
        }

        if(curr == NULL)
        {
            printf("This category ID does not exist. Please try again.\n");
            continue;
        }
        else if(prev == NULL) 
        {
            menu->headCategory = curr->nextCategory;
        }
        else if(curr->nextCategory != NULL) 
        {
            prev->nextCategory = curr->nextCategory;
        }
        else
        {
            prev->nextCategory = NULL;
        }

        break;
    }

    printf("Category “%s – %s” deleted from the system.\n", 
                                                      cId, curr->categoryName);
    freeCatagory(curr);
}


/****************************************************************************
* Menu option #5: Add Item
* Allows the user to add a new item to an existing category. An error
* message is given if the category doesn't exist.
****************************************************************************/
void addItem(GJCType *menu)
{
}


/****************************************************************************
* Menu option #6: Delete Item
* Deletes a single item from a particular category.
****************************************************************************/
void deleteItem(GJCType *menu)
{
}


/****************************************************************************
* Menu option #7: Save and Exit
* Saves all system data back to the original files. This function does not
* terminate the program - this is left to the main() function instead.
****************************************************************************/
void saveData(GJCType *menu, char *menuFile, char *submenuFile)
{
}
