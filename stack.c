#include "stack.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUGON
#define DEBUG(message) printf("DEBUG: %s\n", message);
#else
#define DEBUG(message)
#endif

stackTop createStack()
{

    return NULL;
}

bool isEmptyStack(stackTop stack)
{

    if (stack == NULL)
    {

        return true;
    }
    else
    {
        return false;
    }
}

void push(stackTop *top, dataStruct data)
{
    DEBUG("In push-function");

    stack *ny;
    ny = malloc(sizeof(stack));
    ny->data = data;

    if (*top == NULL)
    {
        DEBUG("stack is empty, adding element to first position");

        *top = ny;
        ny->next = NULL;
    }
    else
    {
        DEBUG("stack is not empty, adding element");
        ny->next = *top;
        *top = ny;
    }
}

void printStackData(dataStruct data)
{

    print_fi_standard(data.date);
    printf(" Code: %d\n", data.kod);
}

void printStack(stackTop stackPrint)
{
    DEBUG("In printStack-function");

    stack *currentPosition;
    currentPosition = stackPrint;

    printf("Printed history\n");
    int counter = 0;

    while (currentPosition != NULL)
    {
        DEBUG("In loop printStack-function");
        printf("Element %d : ", counter);
        printStackData(currentPosition->data);
        counter++;
        currentPosition = currentPosition->next;
    }
}

dataStruct pop(stackTop *top)
{
    dataStruct dataToDelete;
    DEBUG("In pop function");

    stack *currentPosition;
    currentPosition = *top;
    dataToDelete = currentPosition->data;

    if (currentPosition == NULL)
    {

        printf("The stack is empty, nothing to remove\n");
    }
    else
    {
        DEBUG("Deleting last added element");
        *top = currentPosition->next;
        free(currentPosition);
        currentPosition = *top;
    }

    return dataToDelete;
}

void stackDelete(stackTop *top)
{
    DEBUG("in stack delete function");

    stack *currentPosition;
    currentPosition = *top;

    while (currentPosition != NULL)
    {
        DEBUG("in loop, stack is not empty");

        pop(top);
        currentPosition = *top;
    }
    DEBUG("outside loop delete");

    *top = NULL;
}

date peekTop(stackTop *top)
{
    stack *currentPosition;
    currentPosition = *top;

    if (currentPosition == NULL)
    {
        printf("The stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return currentPosition->data.date;
    }
}

dataStruct peekStackTop(stackTop *top)
{
    stack *currentPosition;
    currentPosition = *top;

    if (currentPosition == NULL)
    {
        printf("The stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return currentPosition->data;
    }
}

void sortedInsert(stackTop *top, dataStruct data)
{
    DEBUG("In sorted insert funktion");

    if (isEmptyStack(*top))
    {
        DEBUG("BASE CASE: stack is empty, first element");
        push(top, data);
        return;
    }
    date dateTop = peekTop(top);
    DEBUG("sparat datumet pa toppen av stacken");

    if (!is_before(dateTop, data.date))
    {
        DEBUG("element to be added is BEFORE the top element of the stack");
        dataStruct delete = pop(top);
        DEBUG("deleting last added element, and saving that element");
        sortedInsert(top, data);
        DEBUG("adding element with recursion");

        push(top, delete);
        DEBUG("adding the deleted element");
    }
    else
    {
        DEBUG("element to be added is AFTER the last element of the stack/ date to be added is older");

        push(top, data);
        DEBUG("element pushed on top of the stack");
    }

    // https://www.geeksforgeeks.org/sort-a-stack-using-recursion/
}

void sortStack(stackTop *top)
{
    DEBUG("In sortStack funktion");
    dataStruct data;

    if (!isEmptyStack(*top))
    {
        DEBUG("stack is not empty");

        data = pop(top);
        DEBUG("removing top");

        sortStack(top);
        DEBUG("sorting");

        sortedInsert(top, data);
        DEBUG("adding removed top");
    }
}

bool exponerad(int idkod, stackTop top)
{

    DEBUG("In while loop of exponerad function");
    stack *currentPosition;
    currentPosition = top;

    date today;
    date previous;
    set_to_today(&today);
    previous = get_n_days_previous(today, 21);

    while (currentPosition != NULL)
    {
        DEBUG("In while loop of exponerad function");

        if (currentPosition->data.kod == idkod)
        {

            DEBUG("currentNode->data.kod == smittkod");
            if (!is_before(currentPosition->data.date, previous))
            {
                DEBUG("exponerad: checking if date is valid");

                return true;
            }
            else
            {

                return false;
            }
        }
        else
        {
            DEBUG("exponerad: going forward in list");

            currentPosition = currentPosition->next;
        }
    }

    DEBUG("smittkod not in list");

    return false;
}

void printExposed(bool result)
{

    if (result == true)
    {

        printf("You have been exposed to Covid-19. Please get tested.\n");
    }
    else
    {

        printf("You have not been exposed to Covid-19.\n");
    }
}

int countElementsInStack(stackTop top)
{
    DEBUG("In loop count elements in stack");

    stack *currentPosition;
    currentPosition = top;

    int counter = 0;

    while (currentPosition != NULL)
    {
        DEBUG("In loop count elements in stack");
        counter++;
        currentPosition = currentPosition->next;
    }

    return counter;
}

void printToFile(dataStruct data, FILE *fileptr)
{
    fwrite(&data, sizeof(dataStruct), 1, fileptr);
}

void stackWriteToFile(FILE *fileptr, stackTop top)
{
    date today;
    date dateEarlier;
    set_to_today(&today);
    dateEarlier = get_n_days_previous(today, 21);

    DEBUG("in function list write to file");

    stack *currentPosition;
    currentPosition = top;

    while (currentPosition != NULL)
    {
        if (!is_before(currentPosition->data.date, dateEarlier))
        {
            DEBUG("in loop list write to file");

            printToFile(currentPosition->data, fileptr);
        }

        currentPosition = currentPosition->next;
    }
}

stackTop stackReadFromFile(FILE *fileptr, stackTop top)
{
    date today;
    date daysEarlier;
    set_to_today(&today);
    daysEarlier = get_n_days_previous(today, 21);

    DEBUG("in function list read from file");
    dataStruct data;
    int readFields = 0;

    do
    {
        DEBUG("in loop list read from file");

        readFields = fread(&data, sizeof(dataStruct), 1, fileptr);

        if (readFields == 1)
        {
            if (!is_before(data.date, daysEarlier))
            {
                DEBUG("list read from file inserting to list");

                sortedInsert(&top, data);
            }
        }

    } while (readFields == 1);

    return top;
}

void deleteOlderThan(stackTop *top)
{

    // https://www.tutorialcup.com/interview/stack/delete-middle-element-of-a-stack.htm
    DEBUG("in delete older than function");

    date today;
    date previous;
    set_to_today(&today);
    previous = get_n_days_previous(today, 21);

    if (isEmptyStack(*top))
    {
        DEBUG("stack is empty or nothing to be deleted");
        return;
    }

    date dateAtTop = peekTop(top);
    DEBUG("date at top saved");

    dataStruct infoToSave = peekStackTop(top);
    DEBUG("top element saved in variable");

    pop(top);
    DEBUG("removing top element");

    deleteOlderThan(top);
    DEBUG("recursion");

    if (!is_before(dateAtTop, previous))
    {
        DEBUG("checking if date is correct");
        push(top, infoToSave);
        DEBUG("pushing top element back to the stack");
    }
}