#include <stdio.h>
#include "stack.h"
#include "date.h"
#include <stdlib.h>
#include <string.h>

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

void printMenu()
{

    printf("\n---Coronablinker---\n");
    printf("Choose from the following\n");
    printf("If infected, choose 1 \n");
    printf("To enter identitycode, choose 2 \n");
    printf("To check status (smittalarm), choose 3\n");
    printf("To print the current history, choose 4\n");
    printf("To exit, choose 5\n");
}

void printHelp()
{
    printf("\n---Coronablinker---\n");
    printf("Choose from the following commands\n");
    printf("SICK <opening code>, if infected\n");
    printf("ADD dd.mm.yyyy <device id> , to enter identitycode\n");
    printf("CHECK <device id>, for status\n");
    printf("DEBUG, for current history\n");
    printf("HELP, for menu\n");
}

int main(int argc, char *argv[])
{
    stackTop stack;
    stack = createStack();
    dataStruct data;
    int codeParam;
    int infected;
    int ifinfected;
    int day, month, year;
    char *dayParam, *monthParam, *yearParam;
    char *delimeters = "./-";
    date dateParam;

    char *filename = "corona.bin";
    FILE *fileptr;
    fileptr = fopen(filename, "rb");

    if (fileptr != NULL)
    {

        stack = stackReadFromFile(fileptr, stack);
        fclose(fileptr);
    }
    else
    {

        printf("Could not open file %s for reading. Starting with empty history\n", filename);
    }

    if (argc > 1)
    {

        if (strcmp(argv[1], "add") == 0)
        {
            if (argc != 4)
            {
                printf("Wrong number of parameters! Exiting..\n");
                return EXIT_FAILURE;
            }

            dayParam = strtok(argv[2], delimeters);
            monthParam = strtok(NULL, delimeters);
            yearParam = strtok(NULL, delimeters);
            codeParam = atoi(argv[3]);

            if (dayParam == NULL || monthParam == NULL || yearParam == NULL)
            {
                printf("Invalid date!\n");
                return EXIT_FAILURE;
            }

            if (codeParam == 0)
            {

                printf("Invalid code!\n");
                return EXIT_FAILURE;
            }

            day = atoi(dayParam);
            month = atoi(monthParam);
            year = atoi(yearParam);

            if (set_date(&dateParam, day, month, year) == true)
            {
                data.date = dateParam;
                data.kod = codeParam;
                sortedInsert(&stack, data);

                printStack(stack);

                fileptr = fopen(filename, "wb");

                if (fileptr != NULL)
                {

                    stackWriteToFile(fileptr, stack);
                    fclose(fileptr);
                }
                else
                {

                    printf("Could not open file %s for writing. New info not saved.\n", filename);
                }
            }
            else
            {
                printf("Invalid date! Exiting.. \n");
                return EXIT_FAILURE;
            }

            stackDelete(&stack);
            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[1], "sick") == 0)
        {
            if (argc != 3)
            {
                printf("Wrong number of parameters! Exiting..\n");
                return EXIT_FAILURE;
            }

            infected = atoi(argv[2]);
            if (infected == 0)
            {
                printf("Invalid code! Exiting.. \n");
                return EXIT_FAILURE;
            }
            else
            {
                printf("Sending code and ID to the server. Please follow the instructions given by the hospital.\n");
            }

            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[1], "check") == 0)
        {
            if (argc != 3)
            {
                printf("Wrong number of parameters! Exiting..\n");
                return EXIT_FAILURE;
            }

            ifinfected = atoi(argv[2]);

            if (ifinfected != 0)
            {
                bool result = exponerad(ifinfected, stack);
                printExposed(result);
                return EXIT_SUCCESS;
            }
            else
            {
                printf("Invalid code! Exiting.. \n");
                return EXIT_FAILURE;
            }
        }
        else if (strcmp(argv[1], "debug") == 0)
        {
            deleteOlderThan(&stack);
            sortStack(&stack);
            printStack(stack);
            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[1], "help") == 0)
        {
            printHelp();
            return EXIT_SUCCESS;
        }
        else
        {
            printf("Not a valid alternative!\n");
            return EXIT_FAILURE;
        }
    }

    else
    {
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

                deleteOlderThan(&stack);
                sortStack(&stack);
                printStack(stack);
            }
            else if (choice == 2)
            {
                int kod = enterIdentity();
                date dateP;
                dateP = dateWhenPositive();
                data.date = dateP;
                data.kod = kod;

                sortedInsert(&stack, data);
            }
            else if (choice == 3)
            {
                int otherIDCode = enterOtherId();
                bool result = exponerad(otherIDCode, stack);
                printExposed(result);
            }
            else if (choice == 4)
            {
                deleteOlderThan(&stack);
                sortStack(&stack);
                printStack(stack);
            }
            else if (choice == 5)
            {

                fileptr = fopen(filename, "wb");

                if (fileptr != NULL)
                {

                    stackWriteToFile(fileptr, stack);
                    fclose(fileptr);
                }
                else
                {

                    printf("Could not open file %s for writing. New info not saved.\n", filename);
                }

                stackDelete(&stack);
                printf("Goodbye\n");
                exit(EXIT_SUCCESS);
            }
        }
    }

    return 0;
}