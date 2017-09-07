#include <stdio.h>

char ToLower(char letter);

int main(int argc, char * argv[])
{
    if (argc != 2) 
    {
        printf("ERROR: you need one argument");
        return 1;
    }

    char letter = ToLower(argv[1][0]);
    for (int i = 0; argv[1][i] != '\0'; ++i, letter = ToLower(argv[1][i]))
    {
        switch (letter)
        {
            case 'a':
                printf("%d: 'A'\n", i);
                break;
            case 'e':
                printf("%d: 'E'\n", i);
                break;
            case 'i':
                printf("%d: 'I'\n", i);
                break;
            case 'o':
                printf("%d: 'O'\n", i);
                break;
            case 'u':
                printf("%d: 'U'\n", i);
                break;
            case 'y':
                if (i > 2)
                {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                }
                break;
            default:
                printf("%d %c is not a vowel\n", i, letter);
        }
    }

    return 0;
}

char ToLower(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        letter = (letter - 'A') + 'a';
    }

    return letter;
}
