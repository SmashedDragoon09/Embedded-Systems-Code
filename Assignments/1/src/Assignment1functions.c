#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Assignment1functions.h"


typedef struct Node{ //defining the linked list
    char tile;
    int x_pos, y_pos;
    enum type_threat { //enumerating all of the possible threat types
        ANIMAL,
        DISEASE,
        RIVER,
        NOTHING,
        OCEAN
    } type_threat;

    // union threat { //creating a union called threat of animals and disease
    //     ANIMAL,
    //     DISEASE;
    // };

    bool Discovered;
    //pointers to all of the surroundingnodes
    struct LinkedList *right;
    struct LinkedList *left;
    struct LinkedList *up;
    struct LinkedList *down;
 } *node; //Define node as pointer of data type struct Node

//typedef struct Node *node; //Define node as pointer of data type struct Node

node createNode(){
    node temp; // declare a node
    temp = (node)malloc(sizeof(struct Node)); // allocate memory using malloc()
    temp->right = NULL;// make next point to NULL
    temp->left  = NULL;
    temp->up    = NULL;
    temp->down  = NULL;
    return temp;//return the new node
}

node addNode(node head, char value){
    node temp, p;// declare two nodes temp and p
    temp = createNode();//createNode will return a new node with data = value and next pointing to NULL.
    temp->tile = value; // add element's value to data part of node
    if(head == NULL){
        head = temp;     //when linked list is empty set the first node as head
    }
    else{
        p  = head; //assign head to p 
        while(p->right != NULL){
            p = p->right;//traverse the list until p is the last node.The last node always points to NULL.
        }
        p->right = temp;//Point the previous last node to the new node created.
        temp->left = p;
    }
    return head;
}

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

    int ch, i, j;

    for (i = 0; i < matrixSize; i++) {
        for (j = 0; j < matrixSize + 1; j++) {
            ch = fgetc(MapData); 
            if(ch == '\n') { //} || (i == matrixSize && j == matrixSize - 1)) {
                continue;
            }
            //printf("%c", ch);
            map[i][j] = ch;
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (i = 0; i < matrixSize; i++) {
        for (j = 0; j <= matrixSize; j++) {
                        if(ch == '\n' || (i == matrixSize && j == matrixSize - 1)) {
                continue;
            }
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");



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
