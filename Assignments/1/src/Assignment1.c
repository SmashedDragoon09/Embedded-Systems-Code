#include <stdio.h>
#include <ctype.h>

int main() {

    int input = 0;

    printf("Welcome to Oregon Trail!");
    printf("\nTo start the game    Press '1'");
    printf("\nTo view instructions Press '2'");
    printf("\nTo exit the game     Press '3'.\n");

    scanf("%d", &input);
    //printf("%d", input);

    switch(input) {

        case 1:
            printf("\nStart Game\n");
            return 0;
            break;
        case 2:
            printf("\nInstructions\n");
            return 0;
            break;
        case 3:
            printf("\nEnd Game\n");
            return 0;
            break;
    }

    
    return 0;
}