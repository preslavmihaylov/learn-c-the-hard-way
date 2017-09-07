#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int CanPrintIt(char ch);
void PrintLetters(char arg[], int length);

void PrintArguments(int argc, char *argv[])
{
    int i = 0;
    int strLength;

    for (i = 0; i < argc; ++i)
    {
        strLength = strlen(argv[i]);
        PrintLetters(argv[i], strLength);
    }
}

void PrintLetters(char arg[], int length)
{
    int i = 0;

    for (i = 0; i < length; ++i)
    {
        char ch = arg[i];

        if (CanPrintIt(ch)) 
        {
            printf("'%c' == %d", ch, ch);
        }
    }

    printf("\n");
}

int CanPrintIt(char ch)
{
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
    PrintArguments(argc, argv);
    return 0;
}
