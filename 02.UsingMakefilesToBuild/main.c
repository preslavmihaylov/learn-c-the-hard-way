#include <stdio.h>

#define incr5(x) (x + 5)

int main(int argc, char* argv[])
{
    int distance = 100;

    printf("You are %d miles away.\n", incr5(distance));
    return 0;
}
