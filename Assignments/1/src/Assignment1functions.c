#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Assignment1functions.h"


typedef struct location {
    char data;
    int x_pos;
    int y_pos;
    bool is_threat;
    bool is_discorveed;
    //struct Node *up, *down, *left, *right;


} node_type;

// struct node of linked list 
// struct Node { 
//     int data; 
//     *right;
//     *down;
//     *left;
//     *up; 
// }; 


//TODO: helper functions
//AddNode
//FreeNode

struct LinkedList{
    int data;

    struct LinkedList *next;
    struct LinkedList *start;   //need a pointer pointing toward the start node
    struct LinkedList *end;     //need a pointer pointing toward the end node

 };

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

void LoadMap(char *fileName) {
    
    //printf("%s", Filename);

    FILE* MapData = fopen(fileName, "r" );
    if (MapData == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    int i,j;
    int health = 0;
    int matrixSize = lineSize(MapData); //grabbing the size to allocate memory
    printf("%d", matrixSize);
    char *map;
    map = malloc(matrixSize * sizeof(char) + 17); //dynamically allocating memory for the map 

    printf("%s\n", map);
    fscanf(MapData, "%s %d", map, &health); //grbbing the value of health
    printf("Health: ");
    printf("%d\n", health);





    fclose(MapData); //closing the file
}

void printCurrentLocation() {

}

void GameStart(char *fileName) {
    printf("Loading Map.....\n");
    LoadMap(fileName);
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
