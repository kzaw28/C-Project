#define _CRT_SECURE_NO_WARNINGS

/**************************** SYSTEM LIBRARIES *****************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>


/************************* USER-DEFINED LIBRARIES **************************/

#include "core.h"
#include "cosewic.h"

/*************************** FUNCTION DEFINITION ***************************/

///////////////////////
// DISPLAY FUNCTIONS //
///////////////////////

// Display's the table header according to format
void displayHeader(int fmt)
{
    switch (fmt)
    {
    // Province and Taxon
    case 0:
        printf("EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("------- ---------- ---------- ---------- ------- ---------\n");
        break;
    // Year
    case 1:
        printf("YEAR EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("---- ------- ---------- ---------- ---------- ------- ---------\n");
        break;
    // Province
    case 2:
        printf("PROVINCE             EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("-------------------- ------- ---------- ---------- ---------- ------- ---------\n");
        break;
    // Taxon
    case 3:
        printf("TAXON           EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("--------------- ------- ---------- ---------- ---------- ------- ---------\n");
        break;
    }

    return;
}

// Displays a single data record according to format
void displayData(struct FileData* data, struct Totals* total, int fmt, int numRecords)
{
    int i = 0;

    switch (fmt)
    {
    // Province and Taxon
    case 0:
        break;
        
    // Year
    case 1:
        sortAscend(data, numRecords, fmt);
        calculateTotals(data, total, numRecords, fmt);
        break;
    // Province
    case 2:

        break;
    // Taxon
    case 3:
        sortAscend(data, numRecords, fmt);
        calculateTotals(data, total, numRecords, fmt);
        
        for (i = 0; i < numRecords; i++)
        {
            printf("%d,%s,%s,%d,%s\n", data[i].year, data[i].taxon, data[i].status,
                   data[i].count, data[i].province);
        }
        
        break;
    }
}

/////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS //
/////////////////////////////////////

// Entry point to application logic
int mainLogic(struct FileData data[], int numRecords)
{
    int selection;
    struct Totals total[numRecords];

    do
    {
        printf("=======================================================\n");
        printf("         Canada Species at Risk Analysis\n");
        printf("            (Data Years: 2010 - 2019)\n");
        printf("1. View by year (sorted ASCENDING by year)\n");
        printf("2. View by province (sorted DESCENDING by totals)\n");
        printf("3. View by taxon (sorted ASCENDING by totals)\n");
        printf("4. View by province and taxon\n");
        printf("=======================================================\n");
        printf("0. Exit\n");
        printf("=======================================================\n");
        printf("Selection: ");

        selection = inputIntRange(0, 4);
        
        switch (selection)
        {
        case 1:
            printf("\n");
            ViewByYear(data, total, numRecords);
            break;
        case 2:
            printf("\n");
            ViewByProvince(data, total, numRecords);
            break;
        case 3:
            printf("\n");
            ViewByTaxon(data, total, numRecords);
            break;
        case 4:
            printf("\n");
            ViewByProvinceAndTaxon(data, total, numRecords);
            break;
        }
        
    } while (selection);

    printf("\nApplication Terminated!\n");

    return 0;
}


// View by year (sorted ASCENDING by year)
void ViewByYear(struct FileData data[], struct Totals total[], int numRecords)
{
    displayHeader(FMT_YEAR);
    displayData(data, total, FMT_YEAR, numRecords);
    return;
}

// View by province (sorted DESCENDING by totals)
void ViewByProvince(struct FileData data[], struct Totals total[], int numRecords)
{
    displayHeader(FMT_PROVINCE);
    displayData(data, total, FMT_PROVINCE, numRecords);
    return;
}

// View by taxon (sorted ASCENDING by totals)
void ViewByTaxon(struct FileData data[], struct Totals total[], int numRecords)
{
    displayHeader(FMT_TAXON);
    displayData(data, total, FMT_TAXON, numRecords);
    return;
}

// View by province and taxon
void ViewByProvinceAndTaxon(struct FileData data[], struct Totals total[], int numRecords)
{
    displayHeader(FMT_PROVINCE_TAXON);
    displayData(data, total, FMT_PROVINCE_TAXON, numRecords);
    return;
}

///////////////////////
// UTILITY FUNCTIONS //
///////////////////////

// Sort the data in ascending order by year, or by totals
void sortAscend(struct FileData data[], int numRecords, int selection)
{
    int i, sorted;
    int swapComplete = 0;
    struct FileData temp[6500] = { {0} };

    while (swapComplete == 0)
    {
        sorted = 0;
        for (i = 0; i < numRecords - 1; i++)
        {
            if (selection == FMT_YEAR)
            {
                if (data[i].year > data[i + 1].year)
                {
                    temp[i] = data[i];
                    data[i] = data[i + 1];
                    data[i + 1] = temp[i];

                    sorted = 1;
                }
            }
            else if (selection == FMT_TAXON)
            {
                if (strcmp(data[i].taxon, data[i+1].taxon) > 0)
                {
                    temp[i] = data[i];
                    data[i] = data[i + 1];
                    data[i + 1] = temp[i];

                    sorted = 1;
                }
            }
        }

        if (sorted == 0)
        {
            swapComplete = 1;
        }
    }

    return;
}

// Calculate the totals of each status according to user selection
void calculateTotals(struct FileData data[], struct Totals total[], int numRecords, int selection)
{
    int i = 0, j;
    int year;

    if (selection == FMT_YEAR)
    {
        j = 0;
        year = data[j].year;

        for (i = 0; i < numRecords; i++)
        {
                if (strcmp(data[i].status, "EXTINCT") == 0)
                {
                    total[j].extinct += data[i].count;
                }
                else if (strcmp(data[i].status, "EXTIRPATED") == 0)
                {
                    total[j].extirpated += data[i].count;
                }
                else if (strcmp(data[i].status, "ENDANGERED") == 0)
                {
                    total[j].endangered += data[i].count;
                }
                else if (strcmp(data[i].status, "THREATENED") == 0)
                {
                    total[j].threatened += data[i].count;
                }
                else if (strcmp(data[i].status, "SPECIAL CONCERN") == 0)
                {
                    total[j].concern += data[i].count;
                }

                total[j].total += data[i].count;
            
            if (data[i].year != data[i + 1].year)
            {
                printf("%d%8d%11d%11d%11d%8d%10d\n", year, total[j].extinct, total[j].extirpated, total[j].endangered, total[j].threatened, total[j].concern, total[j].total);
                year += 1;
                j++;
            }
        }
    }
    else if (selection == FMT_TAXON)
    {
    }

    return;
}

// Sort the data in descending order by totals
void sortDescend(struct FileData data[], int numRecords)
{
    
    return;
}

// Find lowest total
int findLowestNum(struct FileData data[], int numRecords)
{

        return 0;
}

// Find highest total or year
int findHighestNum(struct FileData data[], int numRecords, int selection)
{

    return 0;
}

////////////////////
// FILE FUNCTIONS //
////////////////////

// Import data from file into a data array (returns # of records read)
int loadData(const char* datafile, struct FileData data[], int numRecords)
{
    FILE* fp = NULL;

    int rc = 0, i = 0;
    char firstLine[FIRST_LINE_LENGTH + 1];

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        fscanf(fp, "%[^\n]", firstLine);

        do
        {
            rc = fscanf(fp, "%d,%[^,],%[^,],%d,%[^\n]\n", &data[i].year, data[i].taxon, data[i].status,
                                                          &data[i].count, data[i].province);
            if (rc > 0)
            {
                i++;
            }
        } while (rc > 0 && i < numRecords);

        fclose(fp);
    }

    return i;
}
