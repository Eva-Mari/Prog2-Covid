#include "date.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef STACKH
#define STACKH

typedef struct dataStruct
{

    date date;
    int kod;
} dataStruct;

typedef struct stack
{
    dataStruct data;
    struct stack *next;
} stack;

typedef stack *stackTop;

stackTop createStack();

bool isEmptyStack(stackTop stack);

void push(stackTop *top, dataStruct data);

void printStack(stackTop stack);

dataStruct pop(stackTop *top);

void stackDelete(stackTop *top);

date peekTop(stackTop *top);

dataStruct peekStackTop(stackTop *top);

/**
 *
 *
 * Inspiration: https://www.geeksforgeeks.org/sort-a-stack-using-recursion/
 */

void sortedInsert(stackTop *top, dataStruct data);

void sortStack(stackTop *top);

bool exponerad(int idkod, stackTop top);

void printExposed(bool result);

/**
 *
 * inspiration: https://www.tutorialcup.com/interview/stack/delete-middle-element-of-a-stack.htm
 *
 */

void deleteOlderThan(stackTop *top);

void printToFile(dataStruct data, FILE *fileptr);

void stackWriteToFile(FILE *fileptr, stackTop top);

stackTop stackReadFromFile(FILE *fileptr, stackTop top);

int countElementsInStack(stackTop top);

#endif