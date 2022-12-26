/*
*****************************************************************************
                        Final Assessment
Full Name  : Kaung Khant Zaw
Student ID#: 157467218
Email      : kzaw@myseneca.ca
Section    : NGG

Full Name  : Matt Hyland
Student ID#: 035286046
Email      : mhyland@myseneca.ca
Section    : NGG

Full Name  : Sang Hyon Jeon
Student ID#: 113552194
Email      : shjeon5@myseneca.ca
Section    : NGG

Authenticity Declaration:
We declare this submission is the result of our own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of our own creation.
*****************************************************************************
*/

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