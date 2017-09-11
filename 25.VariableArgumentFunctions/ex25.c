#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100


int readString(char **outString, int maxBuffer)
{
    *outString = calloc(1, maxBuffer + 1);
    check_mem(outString);

    char *result = fgets(*outString, maxBuffer, stdin);
    check(result != NULL, "Input error.");

    return 0;

error:
    return -1;
}

int readInt(int *outInt)
{
    char *input;
    int rc = readString(&input, MAX_DATA);
    check(rc == 0, "Failed to read number.");

    *outInt = atoi(input);

    free(input);
    return 0;

error:
    return -1;
}

int printStr(const char *fmt, ...)
{
    char str[MAX_DATA];

    va_list argp;
    va_start(argp, fmt);

    for (int i = 0; fmt[i] != '\0'; ++i)
    {
        if (fmt[i] != '%')
        {
            fputc(fmt[i], stdout);
        }
        else
        {
            ++i;
            switch (fmt[i])
            {
                case '\0':
                {
                    sentinel("Invalid format, you ended with %%.");
                    break;
                }
                case 'd':
                {
                    int digit = va_arg(argp, int);
                    sprintf(str, "%d", digit);

                    fputs(str, stdout);
                    
                    break;
                }
                case 'c':
                {
                    char ch = va_arg(argp, int);
                    fputc(ch, stdout);
                    
                    break;
                }
                case 's':
                {
                    char *str = va_arg(argp, char *);
                    fputs(str, stdout);
                    
                    break;
                }
                default:
                {
                    sentinel("Invalid format");
                }
            }
        }
    
        check(!feof(stdout) && !ferror(stdout), "Output error.");
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

int readScan(const char *fmt, ...)
{
    int rc;

    va_list argp;
    va_start(argp, fmt);

    for (int i = 0; fmt[i] != '\0'; ++i)
    {
        if (fmt[i] != '%')
        {
            fgetc(stdin);
        }
        else
        {
            ++i;
            switch (fmt[i])
            {
                case '\0':
                {
                    sentinel("Invalid format, you ended with %%.");
                    break;
                }
                case 'd':
                {
                    int *digit = va_arg(argp, int *);
                    rc = readInt(digit);
                    check(rc == 0, "invalid digit.");

                    break;
                }
                case 'c':
                {
                    char *ch = va_arg(argp, char *);
                    *ch = fgetc(stdin); 
                    
                    break;
                }
                case 's':
                {
                    int maxBuffer = va_arg(argp, int);
                    char **str = va_arg(argp, char **);
                    rc = readString(str, maxBuffer); 
                    check(rc == 0, "Failed to read string.");

                    break;
                }
                default:
                {
                    sentinel("Invalid format");
                }
            }
        }
    
        check(!feof(stdin) && !ferror(stdin), "Input error.");
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

int main(int argc, char *argv[])
{
    char *firstName = NULL;
    char initial = ' ';
    char *lastName = NULL;
    int age = 0;
    int rc = 0;

    printStr("What's your first name? ");
    rc = readScan("%s", MAX_DATA, &firstName);
    check(rc == 0, "Failed first name.");
    
    printStr("What's your initial? ");
    rc = readScan("%c\n", &initial);
    check(rc == 0, "Failed initial.");
    
    printStr("What's your last name? ");
    rc = readScan("%s", MAX_DATA, &lastName);
    check(rc == 0, "Failed last name.");
    
    printStr("How old are you? ");
    rc = readScan("%d", &age);
    check(rc == 0, "Failed age.");

    printStr("---- RESULTS ----\n");
    printStr("First name: %s", firstName);
    printStr("Initial: '%c'\n", initial);
    printStr("Last Name: %s", lastName);
    printStr("Age: %d\n", age);

    free(firstName);
    free(lastName);
    
    return 0;

error:
    if (firstName) free(firstName);
    if (lastName) free(lastName);
    return -1;
}


