#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Assignment1functions.h"
//TODO: helper functions
//AddNode
//FreeNode


// Function for finding the matrixSize 
int lineSize(FILE *mapData) {  
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

NODE_t* create_node(char display_char, int x, int y) {
    NODE_t node;
    node.XLocation = x;
    node.YLocation = y;
    node.discovered = '0';
    printf("%d", node.XLocation);
    printf("%d", node.YLocation);
    printf("\n");
    // node.right  = x+1;
    // node.left   = x-1;
    // node.up     = y+1;
    // node.down   = y-1;
}

NODE_t* find_node(NODE_t* head, int x, int y) {
    ;
}

NODE_t* create_map(char *map, int n) {
    
}

void free_map(NODE_t *head) {
    
}

void print_node(NODE_t* node) {
    
}

void print_map(NODE_t* head) {
    
}

NODE_t* create_viewport(NODE_t *map_head) {
    
}

ANIMAL_t make_animal(char display_char) {
    ANIMAL_t animal;
    switch(display_char) {
        case 'G':
            animal.display_char = 'G';
            animal.health_mod = -10;
            break;
        case 'B':
            animal.display_char = 'B';
            animal.health_mod = -5;
            break;
        case 'H':
            animal.display_char = 'H';
            animal.health_mod = 5;
            break;
        case 'E':
            animal.display_char = 'E';
            animal.health_mod = 10;
            break;

        default:
            animal.display_char = 'U';
            animal.health_mod = 0;
            break;
    }

    return animal;
    ;
}

void LoadMap(char *fileName) {
    
    //printf("%s", Filename);

    FILE* MapData = fopen(fileName, "r" );
    if (MapData == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    int health = 0;
    int matrixSize = lineSize(MapData); //grabbing the size to allocate memory
    printf("%d\n", matrixSize);
    char map[matrixSize][matrixSize];
    //map = malloc(matrixSize * sizeof(char) + 17); //dynamically allocating memory for the map 

    //printf("%s\n", map);
    fscanf(MapData, "%*s %d", &health); //grbbing the value of health by skipping the first string and intaking the int after it
    printf("Health: ");
    printf("%d\n", health);

    int x, y;
    char ch;

    for (x = 0; x < matrixSize; x++) {
        for (y = 0; y < matrixSize + 1; y++) {
            ch = fgetc(MapData); 
            if(ch == '\n') { //} || (i == matrixSize && j == matrixSize - 1)) {
                continue;
            }
            //printf("%c", ch);
            map[x][y] = ch;
            printf("%c", map[x][y]);
            create_node(ch, x, y - 1); //creating the nodes one at a time
        }
        printf("\n");
    }
    // printf("\n");

    // for (i = 0; i < matrixSize; i++) {
    //     for (j = 0; j <= matrixSize; j++) {
    //                     if(ch == '\n' || (i == matrixSize && j == matrixSize - 1)) {
    //             continue;
    //         }
    //         printf("%c", map[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    fclose(MapData); //closing the file

}

void printCurrentLocation() {

}

void GameStart(char *fileName) {
    printf("Loading Map.....\n");
    LoadMap(fileName);

    CHOICE_e pick_direction();
}

void Instructions() {
    printf("\n\nThe game you are about to play is called Oregon Trail!");
    printf("\nYou move using the keys\n'U'(UP)\n'D'(DOWN)\n'L'(LEFT)\n'R'(RIGHT)");
    printf("\nYou will have to move through the map and discover what awaits!");
    printf("\nThere are a few different tiles that you can land on!");
    printf("");
    StartMenu();
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
                    "\nStarting Game.....");
            return 1;
            break;
        case 2:
            //chose instructions
            printf("\nInstructions\n");
            Instructions();
            break;
        case 3:
            //end the game
            printf("\nEnd Game\n");
            exit(1);
            break;
        default:
            printf("\nThat's not a valid input, sorry you never learned how to read!\n\n\n");
            exit(1);
            break;
    }
    return 0;
}
