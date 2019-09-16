#include <stdio.h>
#include "lab2functions.h"


void printArray(void* array, int length, int(*ptr)(void *)) {
    for(int i = 0; i<length; i++){
    printf("%d: ", i);
    array  += (*ptr)(array);
    }
}

int printInt(void* element){
    printf("%d\n", *(int*) element);
    return sizeof(int);
}

int printChar(void* element){
    printf("%c\n", *(char*) element);
    return sizeof(char);
}

int printFloat(void* element){
   printf("%3.3f\n", *(float*) element);
   return sizeof(float);
}
