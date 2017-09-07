#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char name[4] = { 97, 98, 99 };
    int numbers[4] =  { 'a', 'b', 'c' };

    // char arr as int arr
    printf("%d %d %d %d\n",
            name[0], name[1], name[2], name[3]);

    // int arr as char arr
    printf("%c %c %c %c\n",
            numbers[0], numbers[1], numbers[2], numbers[3]);
    
    int strAsNumber;
    memcpy(&strAsNumber, name, sizeof(int));

    // convert string to int
    printf("string %s as number: %d\n",
            name, strAsNumber);

    name[0] = 'Z';

    printf("modified char arr: %s\n", name);

    char * readOnlyName = "abc";
    // this will cause SIGSEGV
    //readOnlyName[0] = 'Z';
    
    printf("modified read-only char arr: %s\n", readOnlyName);
    
    return 0;
}
