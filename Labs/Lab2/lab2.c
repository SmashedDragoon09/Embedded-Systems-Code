#include <stdio.h>
#include <ctype.h> //cointains a function to check for a alphanumeric number
#include "lab2functions.h"

void printArray(void* array, int length, int((*ptr)(void *)));
int printInt(void* element);
int printChar(void* element);
int printFloat(void* element);

int main(){
    void* iptr = &printInt;
    void* cptr = &printChar;
    void* fptr = &printFloat;
    const int size = 50;
    char Array[size] = {0};
    void* ptr = &Array[0];
    printArray(ptr, size, cptr);
    return 0;
}

