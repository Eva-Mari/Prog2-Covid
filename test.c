#include "list.h"
#include "date.h"
#include <stdio.h>

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
    dataList listan;
    dataDateId datan;
    listan = listCreate();

    char *filename = "test.txt";
    FILE *filePTR;

    TEST("Testing list write to file function");

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
    printf("List after start:\n");
    listPrint(listan);

    datan.date.day = 27;
    datan.date.month = 1;
    datan.date.year = 2022;
    datan.kod = 3;

    listInsert(&listan, datan);

    datan.date.day = 30;
    datan.date.month = 3;
    datan.date.year = 2022;
    datan.kod = 56;

    listInsert(&listan, datan);

    datan.date.day = 1;
    datan.date.month = 1;
    datan.date.year = 2022;
    datan.kod = 90;

    listInsert(&listan, datan);

    datan.date.day = 31;
    datan.date.month = 12;
    datan.date.year = 2021;
    datan.kod = 130;

    listInsert(&listan, datan);

    datan.date.day = 25;
    datan.date.month = 1;
    datan.date.year = 2022;
    datan.kod = 890;

    listInsert(&listan, datan);

    listPrint(listan);

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

    TEST("Testing if list is empty\n");
    VERIFY(listIsEmpty(listan), "List is empty");

    datan.date.day = 27;
    datan.date.month = 1;
    datan.date.year = 2022;
    datan.kod = 130;

    listInsert(&listan, datan);

    datan.date.day = 30;
    datan.date.month = 3;
    datan.date.year = 2022;
    datan.kod = 1;

    listInsert(&listan, datan);

    datan.date.day = 1;
    datan.date.month = 1;
    datan.date.year = 2022;
    datan.kod = 10;

    listInsert(&listan, datan);

    datan.date.day = 31;
    datan.date.month = 12;
    datan.date.year = 2021;
    datan.kod = 60;

    listInsert(&listan, datan);

    datan.date.day = 20;
    datan.date.month = 1;
    datan.date.year = 2022;
    datan.kod = 78;

    listInsert(&listan, datan);

    listPrint(listan);

    TEST("Testing if list is empty\n");
    VERIFY(listIsEmpty(listan), "List is not empty");

    TEST("Testing set_date");
    date dateTest;
    date dateTest2;
    date dateTest3;
    date dateTest4;

    VERIFY(set_date(&dateTest, 31, 1, 2022), "Correct date");
    VERIFY(!set_date(&dateTest, 32, 1, 2022), "Incorrect date");
    VERIFY(!set_date(&dateTest, 29, 2, 2022), "Incorrect date");
    VERIFY(!set_date(&dateTest, 1, 15, 2022), "Incorrect date");
    VERIFY(set_date(&dateTest, 29, 2, 2020), "Correct date");

    TEST("Testing dates are equal");
    set_date(&dateTest, 31, 1, 2022);
    set_date(&dateTest2, 31, 1, 2022);
    VERIFY(dates_equal(dateTest, dateTest2), "Dates are equal");
    set_date(&dateTest3, 31, 1, 2022);
    set_date(&dateTest4, 2, 1, 2022);
    VERIFY(!dates_equal(dateTest3, dateTest4), "Dates are not equal");

    printf("\n");

    TEST("Testing if a date is before another");
    set_date(&dateTest, 31, 1, 2022);
    set_date(&dateTest2, 1, 5, 2022);
    VERIFY(is_before(dateTest, dateTest2), "DateTest is before dateTest2");
    set_date(&dateTest3, 20, 1, 2023);
    set_date(&dateTest4, 20, 1, 2022);
    VERIFY(!is_before(dateTest3, dateTest4), "Datetest3 is not before datetest4");

    printf("\n");

    TEST("Testing what the date is before a given date");
    set_date(&dateTest, 1, 3, 2020);
    dateTest2 = get_previous_day(dateTest);
    printf("(should be before) dateTest2 = ");
    print_fi_standard(dateTest2);
    printf("\ndateTest = ");
    print_fi_standard(dateTest);

    printf("\n");

    TEST("Testing what the date is after a given date");
    set_date(&dateTest, 31, 12, 2020);
    dateTest2 = get_day_after(dateTest);
    printf("(should be after) dateTest2 = ");
    print_fi_standard(dateTest2);
    printf("\ndateTest = ");
    print_fi_standard(dateTest);

    printf("\n");

    TEST("Testing what the date is after a given date");
    set_date(&dateTest, 15, 1, 2022);
    dateTest2 = get_n_days_previous(dateTest, 5);
    print_fi_standard(dateTest);
    printf("\ndays before is: ");
    print_fi_standard(dateTest2);

    printf("\n");

    listPrint(listan);

    TEST("Testar exponerad funktion");

    int kod;

    kod = 1;
    exponerad(kod, listan);

    VERIFY(exponerad(kod, listan) == true, "checking if kod is in list");

    kod = 15;
    exponerad(kod, listan);

    VERIFY(exponerad(kod, listan) != true, "checking if kod (15) is NOT in list, expecting fail");

    kod = 60;
    exponerad(kod, listan);

    VERIFY(exponerad(kod, listan) != true, "kod (60) is in list, date older than 21 days, expecting fail");

    printf("\n");

    listPrint(listan);

    return 0;
}