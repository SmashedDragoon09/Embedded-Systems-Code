#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Assignment1functions.h"
//TODO: helper functions
//AddNode
//FreeNode
static int health = 0;
static int size = 0;
static NODE_t *begin;
static NODE_t *finish;
static NODE_t *head;
static NODE_t **array;

void GameStart(char *fileName) {
    printf("Loading Map.....\n");
    CHOICE_e choice;

    char *map;
    //NODE_t *map = create_map(map)
    LoadMap(fileName);
    printf("%d", head->right);
    //print_viewport(*viewport);

    // while(head->XLocation != finish->XLocation && head->YLocation != finish->YLocation) {
    //     //print_viewport(viewport);
    //     choice = pick_direction();
    //     //check_node(choice, map, viewport);
    //     //confirm_choice(threat_type, threat)
    // }
}


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

    NODE_t *node;
    head = calloc(1,1 * sizeof head);

    node = calloc(1, 1 * sizeof node);

    //NODE_t **array = (NODE_t **)calloc(size * size, sizeof(NODE_t *));

    printf("\nNode type: ");
    //a few if statements to change node type and threat 
    if(display_char == 'E' || display_char == 'H' || display_char == 'B' || display_char == 'G'){
        node->type = ANIMAL;
        node->threat.animal = make_animal(display_char);
        printf("display_char: ");
        printf("%c", node->threat.animal.display_char);
    }
    else if(display_char == 'D' || display_char == 'C' || display_char == 'F') {
        node->type = DISEASE;
        node->threat.disease = make_disease(display_char);
        printf("display_char: ");
        printf("%c", node->threat.disease.display_char);
    }
    else if (display_char == 'R') {
        printf("display_char: ");
        printf("%c", display_char);
        node->type = RIVER;
    }
    else if (x == 0 && y == 0){
        printf("display_char: ");
        printf("%c", display_char);
        node->type = PLAYER;
    }
    else if (y == size-1 && x == size-1) {
        printf("display_char: ");
        printf("%c", display_char);
        node->type = GOAL;
    }
    else if (display_char == 'N') {
        printf("display_char: ");
        printf("%c", display_char);
        node->type = NOTHING;
    }
    else if (x > size || y > size) {
        printf("display_char: ");
        printf("%c", '=');
        node->type = OCEAN;
    }

    //assigning the node's x and y location
    node->XLocation = x;
    node->YLocation = y;
    node->discovered = 0;
    // node->display_char =
    printf("%d", node->XLocation);
    printf("%d", node->YLocation);
    printf("\n");
    // node->right  = NULL;
    // node->left   = NULL;
    // node->up     = NULL;
    // node->down   = NULL;
    if(x == 0 & y == 0) {
        head->right = node;
    }
    return node;
}

NODE_t* find_node(NODE_t* head, int x, int y) {
    printf("find node");
}

NODE_t* create_map(char *map) {
    printf("Create Node Map");
    NODE_t *head;

}

void free_map(NODE_t *head) {
    printf("print map");
}

// void print_node(NODE_t* node) {
//     int i, j;
//     for(i = 0; i < size; i++) {
//         for(j = 0; j < size; j++) {
//             if(head->type == PLAYER) {
//                 printf("%c", "X");
//             }
//         }
//     }
// }

void print_map(NODE_t* head) {
    printf("print map");
}

NODE_t* create_viewport(NODE_t *map_head) {
    
}
// void move_up(NODE_t *map, NODE_t** viewport) {}
// void move_down(NODE_t *map, NODE_t** viewport) {}
// void move_left(NODE_t *map, NODE_t** viewport) {}
// void move_right(NODE_t *map, NODE_t** viewport) {}

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
}

DISEASE_t make_disease(char display_char) {
    DISEASE_t disease;
    switch(display_char) {
        case 'D':
            disease.display_char = 'D';
            disease.health_mod = -15;
            break;
        case 'F':
            disease.display_char = 'F';
            disease.health_mod = -10;
            break;
        case 'C':
            disease.display_char = 'C';
            disease.health_mod = -10;
            break;
        default:
            disease.display_char = 'U';
            disease.health_mod = 0;
            break;
    }
    return disease;
}

void LoadMap(char *fileName) {
    FILE* MapData = fopen(fileName, "r" );
    if (MapData == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    size = lineSize(MapData); //grabbing the size to allocate memory
    printf("%d\n", size);
    //char *map;
    //map = calloc(1, size * sizeof(char)); //dynamically allocating memory for the map 


    //grbbing the value of health by skipping the first string and intaking the int after it
    fscanf(MapData, "%*s %d", &health); //grbbing the value of health by skipping the first string and intaking the int after it
    printf("Health: ");
    printf("%d\n", health);

    int x, y;
    char ch;

    NODE_t **array = (NODE_t **)calloc(size * size, sizeof(NODE_t *));

    for (x = 0; x < size; x++) {
        for (y = 0; y < size + 1; y++) {
            ch = fgetc(MapData); 
            if(ch == '\n') { //telling it to skip end line 
                continue;
            }
            //printf("%c", ch);
            //map[x][y] = ch;
            //printf("%c", map[x][y]);
            printf("\nCreating Node:");
            // if(x == 0 && y == 0) {
            //     head = create_node(ch, x, y);
            // }
            // else {
            //     create_node(ch, x, y); //creating the nodes one at a time
            // }
            *array = create_node(ch, x, y - 1);
        }
        printf("\n");
    }

    fclose(MapData); //closing the file
    //return map;  //returning array of chars
}

// void print_viewport(NODE_t *viewport) {
//     printf("viewport print");
// }

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

CHOICE_e pick_direction() {
    char input;
    scanf("%c", &input);

    switch(input) {
        case 'u':
            //go up
            return UP;
            break;
        case 'l':
            //go left
            return LEFT;
            break;
        case 'r':
            //go right
            return RIGHT;
            break;
        case 'd':
            //go down
            return DOWN;
            break;
        case 'y':
            //yes
            return YES;
            break;
        case 'n':
            //no
            return NO;
            break;
        default:
            return NO;
            break;
    }
}