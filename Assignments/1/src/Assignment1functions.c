#include <stdio.h>
#include <ctype.h>
#include "Assignment1functions.h"
int StartMenu() {

    int input = 0;

    printf("Welcome to Oregon Trail!");
    printf("\nTo start the game    Press '1'");
    printf("\nTo view instructions Press '2'");
    printf("\nTo exit the game     Press '3'.\n");

    scanf("%d", &input);
    //printf("%d", input);

    switch(input) {

        case 1:
            //start game
            printf ("Thank you for choosing to play Oregon Trail,"
                    "\nhave fun and be prepared!\n"
                    "\nStarting Game.....\n");
            return 1;
            break;
        case 2:
            printf("\nInstructions\n");
            return 2;
            break;
        case 3:
            printf("\nEnd Game\n");
            return 3;
            break;
        default:
            printf("\nThat's not a valid input, sorry you never learned how to read!\n\n\n");
            return 3;
            break;
            
    }
    return 0;
}