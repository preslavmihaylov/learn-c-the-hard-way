#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if (errno)
        perror(message);
    else
        printf("ERROR: %s\n", message);

    exit(1);
}

typedef int (*compare_cb)(int a, int b);
typedef int *(*sort_func)(int *numbers, int count, compare_cb cmp);

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

int *insertion_sort(int *numbers, int count, compare_cb cmp)
{
    int *target = malloc(count * sizeof(int));
    if (!target)
        die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for (int i = 0; i < count; ++i)
        for (int j = i; j > 0; --j)
            if (cmp(target[j], target[j - 1]) < 0)
                swap(&target[j], &target[j - 1]);

    return target;
}

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int *target = malloc(count * sizeof(int));

    if (!target)
        die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for (int i = 0; i < count; ++i)
        for (int j = 0; j < count - 1 - i; ++j)
            if (cmp(target[j], target[j + 1]) > 0)
                swap(&target[j], &target[j + 1]);
    
    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if ((a == 0) || (b == 0))
        return 0;
    else
        return a % b;
}

void print_with_msg(const char *msg, int *numbers, int count)
{
    printf("%s", msg);
    for (int i = 0; i < count; ++i)
        printf("%d ", numbers[i]);
    printf("\n");
}

void test_sorting(sort_func sortf, int *numbers, int count, compare_cb cmp, const char *msg)
{
    int *sorted = sortf(numbers, count, cmp);

    if (!sorted)
        die("Failed to sort as requested");

    print_with_msg(msg, sorted, count);
    free(sorted);
}

void dump(compare_cb cmp)
{
    unsigned char *data = (unsigned char *)cmp;

    for (int i = 0; i < 25; ++i)
        printf("%02x:", data[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int *numbers = malloc((argc-1) * sizeof(int));
    int count = argc - 1;
    
    char **inputs = argv+1;
    for (int i = 0; i < count; ++i)
    {
        numbers[i] = atoi(inputs[i]);
    }

    printf("BUBBLE_SORT:\n");
    test_sorting(bubble_sort, numbers, count, sorted_order, "SORTED: ");
    test_sorting(bubble_sort, numbers, count, reverse_order, "REVERSED: ");
    test_sorting(bubble_sort, numbers, count, strange_order, "STRANGE: ");
    printf("\n");

    printf("INSERTION_SORT:\n");
    test_sorting(insertion_sort, numbers, count, sorted_order, "SORTED: ");
    test_sorting(insertion_sort, numbers, count, reverse_order, "REVERSED: ");
    test_sorting(insertion_sort, numbers, count, strange_order, "STRANGE: ");

    free(numbers);

    return 0;
}
