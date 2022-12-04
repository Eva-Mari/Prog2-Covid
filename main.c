#include <stdio.h>
#include "date.h"
#include "list.h"
#include <stdlib.h>

int enterInfectedCode(void)
{
    printf("Please enter your code (startkod): ");
    int code;
    while (!scanf("%d", &code))
    {

        printf("Invalid input!\n");
        printf("Enter your code:\n");
        clearBuffer();
    }

    printf("Sending code and ID to the server. Please follow the instructions given by the hospital.\n");

    return code;
}

int enterOtherId(void)
{

    printf("Please enter the ID-code: ");
    int otherID;
    while (!scanf("%d", &otherID))
    {

        printf("Invalid input!\n");
        printf("Enter the ID-code: ");
        clearBuffer();
    }

    return otherID;
}

int enterIdentity(void)
{

    printf("Please enter your identity code: ");
    int indetity;

    while (!scanf("%d", &indetity))
    {

        printf("Invalid input!\n");
        printf("Enter your code: ");
        clearBuffer();
    }

    return indetity;
}

void printMenu(void)
{

    printf("\n---Coronablinker---\n");
    printf("Choose from the following\n");
    printf("If infected, choose 1 \n");
    printf("To enter identitycode, choose 2 \n");
    printf("To check status (smittalarm), choose 3\n");
    printf("To print the current history, choose 4\n");
    printf("To exit, choose 5\n");
}

void handleChoise(void)
{
    dataList listan;
    dataDateId datan;
    char *filename = "history.txt";
    FILE *filePTR;
    listan = listCreate();

    filePTR = fopen(filename, "r");

    if (filePTR != NULL)
    {

        listan = listReadFromFile(filePTR, listan);
        fclose(filePTR);
    }
    else
    {

        printf("Could not open file %s for reading. Starting with empty history\n", filename);
    }

    while (1)
    {
        printMenu();

        int choice;
        printf("Your choice? ");
        scanf("%d", &choice);
        clearBuffer();
        while (choice < 1 || choice > 5)
        {

            printf("Invalid input! Try again: ");
            scanf("%d", &choice);
            clearBuffer();
        }

        if (choice == 1)
        {
            enterInfectedCode();
            printf("\n");

            removeOlderThan(&listan);
            listPrint(listan);
        }
        else if (choice == 2)
        {
            int kod = enterIdentity();
            date dateP;
            dateP = dateWhenPositive();

            datan.date = dateP;
            datan.kod = kod;

            listInsert(&listan, datan);
        }
        else if (choice == 3)
        {
            int otherIDCode = enterOtherId();
            bool result = exponerad(otherIDCode, listan);
            printExposed(result);
        }
        else if (choice == 4)
        {

            removeOlderThan(&listan);
            listPrint(listan);
        }
        else if (choice == 5)
        {

            filePTR = fopen(filename, "w");

            if (filePTR != NULL)
            {

                listWriteToFile(filePTR, listan);
                fclose(filePTR);
            }
            else
            {

                printf("Could not open file %s for writing. New info not saved.\n", filename);
            }

            listDelete(&listan);
            printf("Goodbye\n");
            exit(EXIT_SUCCESS);
        }
    }
}

int main(void)
{
    handleChoise();

    return 0;
}