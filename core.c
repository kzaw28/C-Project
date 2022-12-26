#define _CRT_SECURE_NO_WARNINGS

/**************************** SYSTEM LIBRARIES *****************************/

#include <stdio.h>
#include <ctype.h>

/************************* USER-DEFINED LIBRARIES **************************/

#include "core.h"

/*************************** FUNCTION DEFINITION ***************************/

//////////////////////////////
// USER INTERFACE FUNCTIONS //
//////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

//////////////////////////
// USER INPUT FUNCTIONS //
//////////////////////////

// Get an integer input within given range
int inputIntRange(int lowerBound, int upperBound)
{
    int selection, rc;
    char after;

    // Check if input is read
    rc = scanf("%d%c", &selection, &after);

    // Display error and clear buffer if no input is read, or input is not followed by a new line
    if (rc == 0 || after != '\n')
    {
        printf("\nInvalid menu selection!\n");
        clearInputBuffer();
    }
    // Display error if input is read, and is followed by a new line, but is out of given range
    else if (selection < lowerBound || selection > upperBound)
    {
        printf("\nInvalid menu selection!\n\n");
    }

    // Return the integer within range entered by the user
    return selection;
}

///////////////////////
// UTILITY FUNCTIONS //
///////////////////////

/*replace*/
