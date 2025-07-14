#include <stdio.h>
#include <string.h>

void pointer() {
    
    int arr[3] = {10, 30, 200}; //array

    int *p; //ptr to int

    int(*ptr)[3]; //ptr to array of 3 ints

    p = arr; //ptr to 0th elmnt array

    ptr = &arr; //ptr to whole array


    int i; //for the loop
    for(i = 0; i < 3; i++) { //prints each elmnt of arr + addrs undr
        printf("%d\n ", (*ptr)[i]); //print elements of array
        printf("%p\n", (ptr)[i]); //print address of array elements
    }

}

void ptr2() { 
    char str1[]= "meow";  //str1
    char *ptr1 = str1; //ptr1

    char str2[]= "woof"; //str2
    char *ptr2 = str2; //ptr2

    if (strlen(ptr1) != strlen(ptr2)){ // checks IF ptr1 & ptr2 r same length
        printf("False\n");             // != (NOT equal), prints false
    }

    else {
        printf("True\n");              //else, print true
    }
}

void sumTxt() {
    FILE *fptr; 
    int numberArr[5]; // array
    int i;
    int sum = 0; //sum variable

    fptr = fopen("foo.txt", "r"); //open file in read mode

    for (i = 0; i < 5; i++) { //read num into array
        fscanf(fptr, "%d", &numberArr[i]);
    }

    for( i = 0; i < 5; i++) {
        sum = sum + numberArr[i]; //sum array
    }

    printf("Sum numbers = %d\n", sum);

}

void swap() {
    int a = 3, b = 0, temp;
    printf("a = %d, b = %d\n", a, b);
    
    temp = a;
    a = b;
    b = temp;
    printf("a = %d, b = %d\n", a, b);

}

void print_array() {
    int arr[2][3] = { {1,2,3}, {4,5,6} }; //array //2 rows, 3 collums

    int (*ptr)[2][3] = &arr; //ptr to array 3w, 3h

    int i, j;//for the loop
    for(i = 0; i < 2; i++) { //prints each elmnt of arr for 1d
        for ( j = 0; j < 3; j++) { //prints each elmnt of arr 2d
            printf("%d\n", (*ptr)[i][j]); //prints array
        }
    }
}



int main(void) {
    int n = 0; //var n
    int ptr = n+1; //pointer to var n

    for(ptr = 0; ptr < 4; ptr++){ //prints n till >3 (loops int ptr)
        printf("%d\n", ptr);
    }
    
    pointer();

    ptr2();

    sumTxt();

    swap();

    print_array();

    return 0;
}