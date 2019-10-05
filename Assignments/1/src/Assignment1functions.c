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
static NODE_t *head;

void GameStart(char *fileName)
{
    printf("Loading Map.....\n");
    //getting file pointer
    FILE* MapData = LoadMap(fileName);

    //getting size to allocate
    size = lineSize(MapData);

    //grbbing the value of health by skipping the 
    //first string and intaking the int after it
    fscanf(MapData, "%*s %d", &health);

    //allocate memory for array of array
    NODE_t **array = (NODE_t **)calloc(size * size, sizeof(NODE_t *));
    array = ParseFile(MapData, array);


    CHOICE_e choice;
    head = calloc(1, 1 * sizeof head);
    //NODE_t *map = create_map(map)
    // printf("created array\n");
    // NODE_t *map;
    // int i,j;
    // printf("creating map 1\n");
    // map = create_map(array);
    // print_map(map);

    // while(head->XLocation != finish->XLocation && head->YLocation != finish->YLocation) {
    //     //print_viewport(viewport);
    //     choice = pick_direction();
    //     //check_node(choice, map, viewport);
    //     //confirm_choice(threat_type, threat)
    // }
}

// Function for finding the matrixSize
int lineSize(FILE *mapData)
{
    int c, count;
    count = 0;
    for (;;)
    {
        c = fgetc(mapData);
        if (c == EOF)
            break; // enf of file => we quit

        if (c == '\n')
            ++count; // end of line => increment line counter
    }
    rewind(mapData);

    return count;
}

void print_map(NODE_t* node) {
    int i,j;
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++) {
            printf("\nX: %d", i);
            printf("\nY: %d", j);
            node = find_node(i, j);
            print_node(node);
        }
    }
}

void print_node(NODE_t* node) {
    printf("\nNode X: %d", node->XLocation);
    printf("\nNode Y: %d", node->YLocation);
}

void free_map(NODE_t *node) {
    free(node);
}

NODE_t* create_map(NODE_t **map)
{
    printf("creating map");
    NODE_t *node = calloc(1, 1 + sizeof(node));
    int i, j;
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++) {
            node = map[size*j+i];
            // Assign UP
            if (j != 0) {
                node->up = map[(j - 1) * size + i];
            }
            else {
                node->up = NULL;
            }

            // Assign DOWN
            if (j != size-1) {
                node->down = map[(j + 1) * size + i];
            }
            else {
                node->down = NULL;
            }

            // Assign LEFT
            if (i != 0) {
                node->left = map[(i - 1) * size + j];
            }
            else {
                node->left = NULL;
            }

            // Assign right
            if (j != size-1) {
                node->right = map[(j + 1) * size + j];
            }
            else {
                node->right = NULL;
            }

            // Move to the right
            if (node->right != NULL) {
                node = node->right;
            }
            else if (node->down != NULL) {
                node = find_node(0, j + 1);
            }
        }
    }
    free(map);
    node = find_node(0, 0);
    printf("map created");
    return node;
}

NODE_t *create_node(char display_char, int x, int y)
{

    NODE_t *node;
    node = calloc(1, 1 * sizeof(node));

    //NODE_t **array = (NODE_t **)calloc(size * size, sizeof(NODE_t *));

    // printf("\nNode type: ");
    //a few if statements to change node type and threat
    if (display_char == 'E' || display_char == 'H' || display_char == 'B' || display_char == 'G')
    {
        node->type = ANIMAL;
        node->threat.animal = make_animal(display_char);
        // printf("display_char: ");
        // printf("%c", node->threat.animal.display_char);
    }
    else if (display_char == 'D' || display_char == 'C' || display_char == 'F')
    {
        node->type = DISEASE;
        node->threat.disease = make_disease(display_char);
        // printf("display_char: ");
        // printf("%c", node->threat.disease.display_char);
    }
    else if (display_char == 'R')
    {
    //     printf("display_char: ");
    //     printf("%c", display_char);
        node->type = RIVER;
    }
    else if (x == size - 1 && y == size - 1)
    {
        // printf("display_char: ");
        // printf("%c", display_char);
        node->type = PLAYER;
    }
    else if (y == 0 && x == 0)
    {
        // printf("display_char: ");
        // printf("%c", display_char);
        node->type = GOAL;
    }
    else if (display_char == 'N')
    {
        // printf("display_char: ");
        // printf("%c", display_char);
        node->type = NOTHING;
    }
    else if (x > size || y > size)
    {
        // printf("display_char: ");
        // printf("%c", '=');
        node->type = OCEAN;
    }

    //assigning the node's x and y location
    node->XLocation = x;
    node->YLocation = y;
    node->discovered = 0;
    printf("%d", node->XLocation);
    printf("%d", node->YLocation);
    printf("\n");
    // node->right  = NULL;
    // node->left   = NULL;
    // node->up     = NULL;
    // node->down   = NULL;
    if (x == 0 & y == 0)
    {
        printf("setting head = to the first node");
        head = node;
        printf("\nhead x loc: %d", head->XLocation);
        printf("\nhead y loc: %d", head->YLocation);
    }
    return node;
}

NODE_t *find_node(int x, int y)
{
    NODE_t *temp = head;
    // printf("\ntemp x loc: %d", temp->XLocation);
    // printf("\ntemp y loc: %d", temp->YLocation);

    int i, j;
    for (i = 0; i < x; i++)
    {
        temp = temp->right;
    }
    for (j = 0; j < y; j++)
    {
        temp = temp->down;
    }

    return temp;
}

// void move_up(NODE_t *map, NODE_t** viewport) {}
// void move_down(NODE_t *map, NODE_t** viewport) {}
// void move_left(NODE_t *map, NODE_t** viewport) {}
// void move_right(NODE_t *map, NODE_t** viewport) {}

//change a node's type to animals
ANIMAL_t make_animal(char display_char)
{
    ANIMAL_t animal;
    switch (display_char)
    {
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

//change a node's type to disease
DISEASE_t make_disease(char display_char)
{
    DISEASE_t disease;
    switch (display_char)
    {
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

FILE* LoadMap(char *fileName) {
    FILE *MapData = fopen(fileName, "r");
    if (MapData == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    return MapData;
}

NODE_t** ParseFile(FILE* MapData, NODE_t** array) {
    int x, y;
    char ch;
    for (y = 0; y < size; y++) {
        for (x = 0; x < size; x++) 
        {
            ch = fgetc(MapData);
            if (ch == '\n' && (x == size || y == size))
            { //telling it to skip end line
                continue;
            }
            // printf("\nCreating Node:");
            array[size * y + x] = create_node(ch, x, y);
            printf("printing array x: %d\n", array[size * y + x]->XLocation);
            printf("printing array y: %d\n", array[size * y + x]->YLocation);
        }
    }
    return array;
    fclose(MapData); //closing the file
}

// void print_viewport(NODE_t *viewport) {
//     printf("viewport print");
// }

void Instructions()
{
    printf("\n\nThe game you are about to play is called Oregon Trail!");
    printf("\nYou move using the keys\n'U'(UP)\n'D'(DOWN)\n'L'(LEFT)\n'R'(RIGHT)");
    printf("\nYou will have to move through the map and discover what awaits!");
    printf("\nThere are a few different tiles that you can land on!");
    StartMenu();
}

//Gives user a basic start menu and prompts for an input
int StartMenu()
{

    int input = 0;

    printf("Welcome to Oregon Trail!");
    printf("\nTo start the game    Press '1'");
    printf("\nTo view instructions Press '2'");
    printf("\nTo exit the game     Press '3'.\n");

    scanf("%d", &input);
    //printf("%d", input);

    //switch statement to determine the input user provided
    switch (input)
    {
    case 1:
        //start game
        printf("Thank you for choosing to play Oregon Trail,"
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

CHOICE_e pick_direction()
{
    char input;
    scanf("%c", &input);

    switch (input)
    {
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