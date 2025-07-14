#include <stdio.h>

int main() {
    int arr[3] = {10, 30, 2000};

    int *p;

    int(*ptr)[3];

    p = arr;

    ptr = &arr;

    printf("p = %p\n",p);
    printf("*ptr = %p\n\n", *ptr);

    return 0;
}