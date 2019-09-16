#include <stdio.h>
#include <ctype.h> //cointains a function to check for a alphanumeric number

char FindFunction(unsigned char Array[]);
int main(){
unsigned char array[50]; //initialize an array with no values
char i;
//printf("Array Size is%lu\n", sizeof(array));
array[10] = 'A';
array[11] = 'C';
       // for(i = 0; i<50; i++){
       // printf("%d\n",array[i]);
       // }
       //printf("Hello, World\n");


FindFunction(array);
return 0;
}

char FindFunction(unsigned char Array[]){
char i;
char a;
//printf("Array Size is%lu\n", sizeof(Array[]));
//for loop to go through entire array
        for(i = 0; i<50; i++){
               //finds the first alphanumeric number
                if(isalnum(Array[i])){
                        //printf("Index %d:  %c\n", i, Array[i]); //%d refers to int, %c refers to character
                        for(a = 0; a<50; a++){
                                //makes every element in the array a letter going up to the first alphanumeric number
                                if(a<i){
                                        Array[a] = 'a' + a; 
                                }
                                //printf("%d : %c\n", a, Array[a]);
                        }
                        //printf("%s\n", Array);
                        break;
                }
        //printf("%d\n",Array[i]);
        }
        printf("%s\n", Array); //prints the array until the first null element
return 0;
}
