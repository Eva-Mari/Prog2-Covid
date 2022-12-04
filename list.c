#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUGON
#define DEBUG(message) printf("DEBUG: %s\n", message);
#else
#define DEBUG(message)
#endif

dataList listCreate()
{

    return NULL;
}

bool listIsEmpty(dataList list)
{

    if (list == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void listInsert(dataList *headptr, dataDateId data)
{

    dataListNode *newNode;
    newNode = malloc(sizeof(dataListNode));
    newNode->data = data;

    if (*headptr == NULL)
    {
        DEBUG("listInsert: Empty list/first element");

        *headptr = newNode;
        newNode->next = NULL;
    }
    else
    {
        DEBUG("listInsert: Not empty list");
        newNode->next = *headptr;
        *headptr = newNode;
    }
}

void printListData(dataDateId data)
{

    print_fi_standard(data.date);
    printf(" Code: %d\n", data.kod);
}

void listPrint(dataList lista)
{

    dataListNode *currentNode;
    currentNode = lista;

    printf("---Printed history---\n");

    while (currentNode != NULL)
    {
        printListData(currentNode->data);
        currentNode = currentNode->next;
    }
}

void removeOlderThan(dataList *listptr)
{

    date today;
    date daysEarlier;
    set_to_today(&today);
    daysEarlier = get_n_days_previous(today, 21);

    dataListNode *currentNode;
    dataListNode *previousNode;

    currentNode = *listptr;
    previousNode = NULL;

    while (currentNode != NULL)
    {

        if (is_before(currentNode->data.date, daysEarlier))
        {

            if (previousNode == NULL)
            {
                DEBUG("RemoveOlderThan: First node to be deleted");
                *listptr = currentNode->next;
                free(currentNode);
                currentNode = *listptr;
            }
            else
            {
                DEBUG("RemoveOlderThan: Not the first node to be deleted");
                previousNode->next = currentNode->next;
                free(currentNode);
                currentNode = previousNode->next;
            }
        }
        else
        {
            DEBUG("RemoveOlderThan: This node should not be deleted, going forward in the list");
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    }
}

void listDelete(dataList *list)
{

    dataListNode *current;
    dataListNode *delete;

    current = *list;

    while (current != NULL)
    {
        DEBUG("ListDelete: Deleting element in list");

        delete = current;

        current = current->next;

        free(delete);
        delete = NULL;
    }

    *list = NULL;
}

void printToFile(dataDateId data, FILE *fileptr)
{

    fprintf(fileptr, "Date: %d.%d.%d, Code: %d\n", data.date.day, data.date.month, data.date.year, data.kod);
}

void listWriteToFile(FILE *fileptr, dataList list)
{
    date today;
    date dateEarlier;
    set_to_today(&today);
    dateEarlier = get_n_days_previous(today, 21);

    DEBUG("in function list write to file");

    dataListNode *currentNode;
    currentNode = list;

    while (currentNode != NULL)
    {
        if (!is_before(currentNode->data.date, dateEarlier))
        {
            DEBUG("in loop list write to file");
            printToFile(currentNode->data, fileptr);
        }

        currentNode = currentNode->next;
    }
}

dataList listReadFromFile(FILE *fileptr, dataList list)
{
    date today;
    date daysEarlier;
    set_to_today(&today);
    daysEarlier = get_n_days_previous(today, 21);

    DEBUG("in function list read from file");
    dataDateId data;
    int readFields = 0;

    do
    {
        DEBUG("in loop list read from file");

        readFields = fscanf(fileptr, "Date: %d.%d.%d, Code: %d\n", &data.date.day, &data.date.month, &data.date.year, &data.kod);

        if (readFields == 4)
        {
            if (!is_before(data.date, daysEarlier))
            {
                DEBUG("list read from file inserting to list");
                listInsert(&list, data);
            }
        }

    } while (readFields == 4);

    return list;
}

bool exponerad(int smittkod, dataList headptr)
{
    DEBUG("In beginning of exponerad function");

    dataListNode *currentNode;
    currentNode = headptr;

    date today;
    date previous;
    set_to_today(&today);
    previous = get_n_days_previous(today, 21);

    while (currentNode != NULL)
    {
        DEBUG("In while loop of exponerad function");

        if (currentNode->data.kod == smittkod)
        {

            DEBUG("currentNode->data.kod == smittkod");

            if (!is_before(currentNode->data.date, previous))
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

            currentNode = currentNode->next;
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