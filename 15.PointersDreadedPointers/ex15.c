#include <stdio.h>

static void printCmdLineArgs(int argc, char *argv[]);
static void printNormal(char **names, int *ages, int count);
static void printPointers(char **names, int *ages, int count);
static void printPointersAsArrays(char **names, int * ages, int count);
static void printComplex(char ** names, int * ages, int count);

int main(int argc, char *argv[])
{
    printCmdLineArgs(argc, argv);
    
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = 
    {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages)/sizeof(int);

    printNormal(names, ages, count);
    printf("---\n");
    printPointers(names, ages, count);
    printf("---\n");
    printPointersAsArrays(names, ages, count);
    printf("---\n");
    printComplex(names, ages, count);

    return 0;
}

static void printCmdLineArgs(int argc, char *argv[])
{
    char ** curr_arg = argv;
    for (int i = 0; i < argc; ++i)
    {
        printf("Arg %d: %s\n", i, *(curr_arg+i));
    }

    printf("---\n");
}

static void printNormal(char **names, int *ages, int count)
{
    // first way using indexing
    for (int i = count-1; i >= 0; --i)
    {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
}


static void printPointers(char **names, int *ages, int count)
{
    char **cur_name = names;
    int *cur_age = ages;

    // second way using pointers
    for (int i = count-1; i >= 0; --i) 
    {
        printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
    }
}


static void printPointersAsArrays(char **names, int * ages, int count)
{
    char ** cur_name = names;
    int * cur_age = ages;

    // third way, pointers are just arrays
    for (int i = count-1; i >= 0; --i)
    {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }
}


static void printComplex(char ** names, int * ages, int count)
{
    char ** cur_name;
    int * cur_age;
    
    // fourth way with pointers in a stupid complex way
    for (cur_name = names+count-1, cur_age = ages+count-1; 
         cur_age >= ages;
         cur_name--, cur_age--)
    {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
}
