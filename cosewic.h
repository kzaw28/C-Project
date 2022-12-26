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

/******************************* SAFE GUARD ********************************/

#ifndef COSEWIC_H
#define COSEWIC_H

/*************************** MACRO DECLARATIONS ****************************/

// Display formatting options
#define FMT_PROVINCE_TAXON 0
#define FMT_YEAR 1
#define FMT_PROVINCE 2
#define FMT_TAXON 3


// C Strings: array sizes
#define FIRST_LINE_LENGTH 32
#define MAX_CHAR 100
#define MAX_PROVINCE_CHAR 2

// Additional macro's
/*replace*/

/************************** STRUCTURE DECLARATION **************************/

// Data type: Totals
struct Totals
{
    int extinct;
    int extirpated;
    int endangered;
    int threatened;
    int concern;
    int total;
};

// Data type: FileData
struct FileData
{
    int year;
    char taxon[MAX_CHAR];
    char status[MAX_CHAR];
    int count;
    char province[MAX_PROVINCE_CHAR];
};

/************************** FUNCTION DECLARATION ***************************/

///////////////////////
// DISPLAY FUNCTIONS //
///////////////////////

// Display's the table header according to format
void displayHeader(int fmt);

// Displays a single data record according to format
void displayData(struct FileData* data, struct Totals* total, int fmt, int numRecords);

/////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS //
/////////////////////////////////////

// Entry point to application logic
int mainLogic(struct FileData data[], int numRecords);

// View by year (sorted ASCENDING by year)
void ViewByYear(struct FileData data[], struct Totals total[], int numRecords);

// View by province (sorted DESCENDING by totals)
void ViewByProvince(struct FileData data[], struct Totals total[], int numRecords);

// View by taxon (sorted ASCENDING by totals)
void ViewByTaxon(struct FileData data[], struct Totals total[], int numRecords);

// View by province and taxon
void ViewByProvinceAndTaxon(struct FileData data[], struct Totals total[], int numRecords);

///////////////////////
// UTILITY FUNCTIONS //
///////////////////////

// Sort the data in ascending order by year, or by totals
void sortAscend(struct FileData data[], int numRecords, int selection);

// Calculate the totals of each status according to user selection
void calculateTotals(struct FileData data[], struct Totals total[], int numRecords, int selection);

// Sort the data in descending order by totals
void sortDescend(struct FileData data[], int numRecords);

// Find lowest total
int findLowestNum(struct FileData data[], int numRecords);

// Find highest total or year
int findHighestNum(struct FileData data[], int numRecords, int selection);

////////////////////
// FILE FUNCTIONS //
////////////////////

// Import data from file into a data array (returns # of records read)
int loadData(const char* datafile, struct FileData data[], int numRecords);

#endif // !COSEWIC_H