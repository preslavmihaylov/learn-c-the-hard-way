#include <stdio.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor 
{
    BLUE_EYES, GREEN_EYES, BROWN_EYES, BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = 
{
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person
{
    int age;
    char firstName[MAX_DATA];
    char lastName[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

void trimEndWhitespace(char *str)
{
    while (isspace((unsigned char)*str)) ++str;
    while (!isspace((unsigned char)*str)) ++str;

    *str = '\0';
}

int main(int argc, char *argv[])
{
    Person you = { .age = 0 };
    int i = 0;
    char *in = NULL;

    printf("What's your First Name? ");
    in = fgets(you.firstName, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read first name.");
    trimEndWhitespace(you.firstName);

    printf("What's your Last Name? ");
    in = fgets(you.lastName, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read last name.");
    trimEndWhitespace(you.lastName);

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; ++i)
    {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }

    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0,
            "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");
    printf("First Name: %s\n", you.firstName);
    printf("Last Name: %s\n", you.lastName);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;

error:
    return -1;
}
