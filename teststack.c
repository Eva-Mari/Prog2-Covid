#include <stdio.h>
#include "stack.h"

#define TEST(namn) printf("Test: %s\n", namn);
#define VERIFY(condition, message)        \
    if (condition)                        \
    {                                     \
        printf("Success: %s\n", message); \
    }                                     \
    else                                  \
    {                                     \
        printf("Fail: %s\n", message);    \
    }

int main(void)
{
    stackTop stack;
    stack = createStack();

    dataStruct data;

    data.date.day = 22;
    data.date.month = 2;
    data.date.year = 2022;
    data.kod = 50;

    TEST("Testing if stack is empty");
    VERIFY(isEmptyStack(stack) == true, "Stack is empty, expecting success");

    TEST("Testing push-funktion");
    push(&stack, data);
    VERIFY(isEmptyStack(stack) == false, "Stack is empty, expecting success");
    VERIFY(isEmptyStack(stack) != true, "Stack is empty, expecting success");

    TEST("Testing print stack function");

    data.date.day = 20;
    data.date.month = 1;
    data.date.year = 2022;
    data.kod = 30;

    push(&stack, data);

    data.date.day = 3;
    data.date.month = 3;
    data.date.year = 2022;
    data.kod = 400;

    push(&stack, data);

    data.date.day = 12;
    data.date.month = 12;
    data.date.year = 2022;
    data.kod = 78;

    push(&stack, data);

    printStack(stack);

    TEST("Testing peektop function");
    date temp;
    temp = peekTop(&stack);
    printf("top position is: %d.%d.%d", temp.day, temp.month, temp.year);
    pop(&stack);
    printStack(stack);
    dataStruct delete;
    delete = pop(&stack);
    printf("deleted element is: %d.%d.%d and %d\n", delete.date.day, delete.date.month, delete.date.year, delete.kod);
    printStack(stack);
    temp = peekTop(&stack);
    printf("top position is: %d.%d.%d\n", temp.day, temp.month, temp.year);

    printf("\n\n\n");

    data.date.day = 20;
    data.date.month = 1;
    data.date.year = 2022;
    data.kod = 30;

    push(&stack, data);

    data.date.day = 3;
    data.date.month = 3;
    data.date.year = 2022;
    data.kod = 400;

    push(&stack, data);

    data.date.day = 12;
    data.date.month = 12;
    data.date.year = 2022;
    data.kod = 78;

    push(&stack, data);

    TEST("testing exponerad function");
    VERIFY(exponerad(78, stack) == true, "id code 78 is in stack, expecting success");
    VERIFY(exponerad(30, stack) != true, "code 30 is in list but date older than 21 days expecting success");
    VERIFY(exponerad(500, stack) != true, "code 500 not in stack, expecting success");

    TEST("Testing count elements");
    printStack(stack);
    int elements = countElementsInStack(stack);
    printf("amount of elements in stack: %d", elements);

    printf("\n\n\n");
    printf("before delete stack");
    printStack(stack);
    TEST("Testing delete stack function");
    stackDelete(&stack);
    VERIFY(isEmptyStack(stack) == true, "stack is empty, expecting success");
    printStack(stack);

    TEST("Testing sorted insert function");
    data.date.day = 20;
    data.date.month = 10;
    data.date.year = 2021;
    data.kod = 30;

    sortedInsert(&stack, data);

    data.date.day = 1;
    data.date.month = 5;
    data.date.year = 2022;
    data.kod = 400;

    sortedInsert(&stack, data);

    data.date.day = 12;
    data.date.month = 12;
    data.date.year = 2021;
    data.kod = 78;

    sortedInsert(&stack, data);
    data.date.day = 6;
    data.date.month = 7;
    data.date.year = 2022;
    data.kod = 370;

    sortedInsert(&stack, data);
    data.date.day = 28;
    data.date.month = 2;
    data.date.year = 2022;
    data.kod = 600;

    sortedInsert(&stack, data);
    printStack(stack);

    printf("----------List should be sorted\n\n");
    printStack(stack);
    printf("\n\n");

    TEST("Testing delete older than function");
    deleteOlderThan(&stack);
    printStack(stack);

    printf("\n\n");
    stackDelete(&stack);
    printStack(stack);
    TEST("Testing sorting insert function");
    data.date.day = 7;
    data.date.month = 7;
    data.date.year = 2022;
    data.kod = 430;

    sortedInsert(&stack, data);

    data.date.day = 1;
    data.date.month = 3;
    data.date.year = 2022;
    data.kod = 450;

    sortedInsert(&stack, data);

    data.date.day = 1;
    data.date.month = 5;
    data.date.year = 2022;
    data.kod = 780;

    sortedInsert(&stack, data);

    data.date.day = 17;
    data.date.month = 2;
    data.date.year = 2022;
    data.kod = 430;

    sortedInsert(&stack, data);

    data.date.day = 15;
    data.date.month = 4;
    data.date.year = 2022;
    data.kod = 450;

    sortedInsert(&stack, data);

    data.date.day = 28;
    data.date.month = 2;
    data.date.year = 2022;
    data.kod = 780;

    sortedInsert(&stack, data);

    data.date.day = 1;
    data.date.month = 4;
    data.date.year = 2022;
    data.kod = 780;

    sortedInsert(&stack, data);
    printf("\n\n");

    printf("------------------------\n");

    TEST("Testing sort function");
    data.date.day = 2;
    data.date.month = 4;
    data.date.year = 2022;
    data.kod = 780;

    push(&stack, data);

    data.date.day = 10;
    data.date.month = 4;
    data.date.year = 2022;
    data.kod = 780;

    push(&stack, data);

    data.date.day = 6;
    data.date.month = 5;
    data.date.year = 2022;
    data.kod = 780;

    push(&stack, data);

    data.date.day = 13;
    data.date.month = 3;
    data.date.year = 2022;
    data.kod = 780;

    printf("list sorted, not yet printed, inserting element with sorted insert\n");

    push(&stack, data);

    data.date.day = 1;
    data.date.month = 2;
    data.date.year = 2022;
    data.kod = 780;

    push(&stack, data);
    printf("\n\n--------------------------\n");
    printf("Before sorting:\n");
    printStack(stack);

    printf("After sorting:\n");
    sortStack(&stack);
    printStack(stack);
    return 0;
}