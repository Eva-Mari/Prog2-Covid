#include "date.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef LISTH
#define LISTH

/**
 * Struct for saving a date and id
 *
 */

typedef struct dataDateIdStruct
{

    date date;
    int kod;
} dataDateId;

typedef struct datastruct
{

    dataDateId data;
    struct datastruct *next;
} dataListNode;

typedef dataListNode *dataList;

dataList listCreate();

bool listIsEmpty(dataList list);

void listInsert(dataList *listptr, dataDateId data);

void listPrint(dataList lista);

void removeOlderThan(dataList *listptr);

void listDelete(dataList *list);

void listWriteToFile(FILE *fileptr, dataList list);

dataList listReadFromFile(FILE *fileptr, dataList list);

bool exponerad(int smittkod, dataList list);

void printExposed(bool result);

#endif