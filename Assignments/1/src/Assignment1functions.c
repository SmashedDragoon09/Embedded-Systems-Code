#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Assignment1functions.h"

// Function for finding the array length
int numOfLines(FILE *mapData) {  
  int c, count;
  count = 0;
  for (;; ) {
    c = fgetc(mapData);
    if (c == EOF)
      break;          // enf of file => we quit

    if (c == '\n')
      ++count;        // end of line => increment line counter
  }
  rewind(mapData);

  return count;
}

void LoadMap(int num) {
    char Filename[10] = {};
    if(num == 1) {
        strcpy(Filename, "map1.txt"); //abort trap:6 which means out of bound
    }
    else {
        strcpy(Filename, "map2.txt");
    }
    
    //printf("%s", Filename);

    FILE *MapData;
    MapData = fopen(Filename, "r" );
    if (MapData == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    // Reading text file into 2D array
    int i,j;
    int health = 0;
    int matrixSize = numOfLines(MapData) + 1;
    char map [matrixSize][matrixSize];

    printf("%d\n", health);

    for(i = 0;i < matrixSize; i++){
            for(j = 0; j < matrixSize; j++){
                fscanf(MapData, "%c", &map[i][j]);
            }
    }

    for(i = 0; i < matrixSize; i++){
        for(j = 0; j < matrixSize; j++){
            printf("%c", map[i][j]);
        }
    }

    //printf("%c", map[matrixSize][matrixSize - 1]);

    fclose(MapData);

}

void GameStart() {
    printf("\nChoose which map you wish you wish to choose\n"
            "To choose Map 1 Press '1'\n"
            "To choose Map 2 Press '2'\n");
    int input = 0;
    scanf("%d", &input);
    //printf("%d", input);

    //switch statement to determine the input user provided
    switch(input) {
        case 1:
            //start game
            printf ("You have chosen Map '1'"
                    "\n Loading......\n");
                    LoadMap(1);
            break;
        case 2:
            //chose instructions
            printf ("You have chosen Map '2'"
                    "\n Loading......\n");
                    LoadMap(2);
            break;
        default:
            printf("\nThat's not a valid input, sorry you never learned how to read!\n\n\n");
            break;
    }
}

//Gives user a basic start menu and prompts for an input
int StartMenu() {

    int input = 0;

    printf("Welcome to Oregon Trail!");
    printf("\nTo start the game    Press '1'");
    printf("\nTo view instructions Press '2'");
    printf("\nTo exit the game     Press '3'.\n");

    scanf("%d", &input);
    //printf("%d", input);

    //switch statement to determine the input user provided
    switch(input) {

        case 1:
            //start game
            printf ("Thank you for choosing to play Oregon Trail,"
                    "\nhave fun and be prepared!\n"
                    "\nStarting Game.....\n");
            return 1;
            break;
        case 2:
            //chose instructions
            printf("\nInstructions\n");
            return 2;
            break;
        case 3:
            //end the game
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
