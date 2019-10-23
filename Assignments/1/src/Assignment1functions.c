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
static char finish = 0;
static NODE_t *head;
static NODE_t *map_head;
static NODE_t *viewport;
// static NODE_t *viewport_c;

//main logic of the game starts and ends in this function
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
    // printf("Health: %d\n", health);
    
    //allocating memory for array of array
    //going through the map file and creating the nodes
    NODE_t **array = MakeNodes(MapData);
    // printf("created array\n");

    //creating the map
    // printf("creating map 1\n");
    NODE_t *map = create_map(array, size);
    // print_map(map);

    //printing viewport
    viewport = create_viewport(map_head);

    while(health > 0 && !finish) {
        print_viewport(viewport);
        pick_direction();
    }
    if(health <= 0){
        printf("You have died....sorry!\n");
    }
    else
        printf("PLease play again!\n");
    
    // free(map_head);
    // free(viewport);
    // free(map);
    exit(1);
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

//printing the entire map of nodes
void print_map(NODE_t* node) {
    
    int i,j;
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++) {
            // printf("\nX: %d", i);
            // printf("\nY: %d", j);
            node = find_node(i, j);
            print_node(node);
        }
        printf("\n");
    }
}

//printing a specific node
void print_node(NODE_t* node) { 

    // printf("\n%d",   node->XLocation);
    // printf("%d\n",   node->YLocation);
    if(node == viewport) {
        printf("|%c|", 'X');  
        return;          
    }
    switch(node->type){
            case(PLAYER):
                printf("|%c|", 'X');            
                break;
            case(GOAL):
                printf("|%c|", 'Z');
                break;
            case(RIVER):
                printf("|%c|", 'R');
                break;
            case(OCEAN):
                printf("|%c|", 'O');
                break;
            case(NOTHING):
                printf("|%c|", 'N');
                break;
            default:
                if((node->type != RIVER || node->type != PLAYER || node->type != GOAL) && node->discovered == 0) {  
                    printf("|%c|", 'U');
                }
                else {
                    switch(node->type){
                        case(ANIMAL):
                            printf("|%c|", node->threat.animal.display_char);
                            break;
                        case(DISEASE):
                            printf("|%c|", node->threat.disease.display_char);
                            break;
                    }
                }
    }
}

//freeing the map when called
void free_map(NODE_t *map) {
    free(map);
}

//links the array of nodes together into a map
NODE_t* create_map(NODE_t **map, int n)
{
    // printf("creating map\n");
    NODE_t *node = head;
    int x, y;

    for (y = 0; y < n; y++) {
        for (x = 0; x < n; x++) {
            // node->up    = y == 0          ? NULL : map[(y-1) * n + x];
            // node->down  = y == (n - 1) ? NULL : map[(y+1) * n + x];
            // node->left  = x == 0          ? NULL : map[y * n + (x - 1)];
            // node->right = x == (n - 1) ? NULL : map[y * n + (x + 1)];

            // Assign UP
            if (y != 0) {
                //printf("Assigning up\n");
                node->up = map[(y - 1) * n + x];
                //printf("Node up x: %d", node->up->XLocation);
            }
            else {
                node->up = NULL;
            }

            // Assign DOWN
            if (y != n-1) {
                //printf("Assigning down\n");
                node->down = map[(y + 1) * n + x];
            }
            else {
                node->down = NULL;
            }

            // Assign LEFT
            if (x != 0) {
                //printf("Assigning left\n");
                node->left = map[(y * n + (x-1))];
            }
            else {
                node->left = NULL;
            }

            // Assign right
            if (x != n-1) {
                //printf("Assigning right\n");
                node->right = map[(y * n + (x+1))];
                //printf("node right :%d\n", node->right->XLocation);

            }
            else {
                node->right = NULL;
            }

            // Move to the right
            if (node->right != NULL) {
                // printf("moving to the right\n");
                // printf("\nnode right :%p", node->right);
                node = node->right;
                //print_node(node);
            }
            else if (node->down != NULL) {
                // printf("\nmoving to the down");
                node = find_node(0, y + 1);
                //print_node(node);
            }
        }
    }
    // printf("\nmap created");
    node = find_node(0, 0);
    // printf("\n");
    return node;
}

//creating a single node
NODE_t *create_node(char display_char, int x, int y)
{

    NODE_t *node;
    node = calloc(1, 1 * sizeof(NODE_t));

    //assigning the node's x and y location
    node->XLocation = x;
    node->YLocation = y;
    node->discovered = 0;
    // printf("\nY: %d \nX: %d", node->YLocation, node->XLocation);
    // printf("\nPrinting the X and Y of node");
    // printf("\n");

    // printf("setting display_char");
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
        node->type = RIVER;
        node->discovered = 1;
        // printf("display_char: ");
        // printf("%c", display_char);
    }
    else if (x == size - 1 && y == size - 1)
    {
        // printf("display_char: ");
        // printf("%c", display_char);
        node->type = PLAYER;
        map_head = node;
    }
    else if (y == 0 && x == 0)
    {
        // printf("display_char: ");
        // printf("%c", display_char);
        node->type = GOAL;
        node->discovered = 1;
        head = node;
    }
    else if (display_char == 'N')
    {
        // printf("display_char: ");
        // printf("%c", display_char);
        node->type = NOTHING;
    }
    else
    {
        // printf("display_char: ");
        // printf("%c", 'O');
        node->type = OCEAN;
    }
    // printf("returning node");
    return node;
}

//finding a node and used when creating the map
NODE_t *find_node(int x, int y)
{
    NODE_t *temp = head;
    // printf("\ntemp x loc: %d", temp->XLocation);
    // printf("\ntemp y loc: %d", temp->YLocation);
    // printf("\nfinding x loc: %d", x);
    // printf("\nfinding y loc: %d", y);
    int i, j;
    for (i = 0; i < x; i++)
    {
        // printf("\ntemp location x : %d", temp->XLocation);
            temp = temp->right;
        // printf("\nnew temp location x : %d", temp->XLocation);
    }
    for (j = 0; j < y; j++)
    {
        // printf("\ntemp location y : %d", temp->YLocation);
            temp = temp->down;
        // printf("\nnew temp location y : %d", temp->YLocation);
    }


    // printf("\ntemp x loc moved to: %d", temp->XLocation);
    // printf("\ntemp y loc moved to: %d", temp->YLocation);
    return temp;
}

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

//loading the map into a file pointer
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

//creating a 2d array of nodes to be later linked
NODE_t** MakeNodes(FILE* MapData) {
    int x, y;
    char ch;
    NODE_t** array = (NODE_t **)calloc(size * size, sizeof(NODE_t *));
    for (y = 0; y < size; y++) {
        for (x = 0; x < size; x++) 
        {
            ch = fgetc(MapData);
            if (ch == '\n' || (x == size && y == size - 1)) { //telling it to skip end line
                //ch = fgetc(MapData);
                // printf("\nCharacter in: %c", ch);
                if(x = 0)
                {
                    x = -1;
                }
                else
                    x = x-1;
                continue;
            }
            else {
            // printf("\nCharacter in: %c", ch);
            // printf("\nCreating Node:");
            // printf("printing array x: %d\n", array[size * y + x]->XLocation);
            // printf("printing array y: %d\n", array[size * y + x]->YLocation);
            //printf("%d\n", size);
            array[(size * y) + x] = create_node(ch, x, y);
            }
        }
    }
    fclose(MapData); //closing the file
    return array;
}

//free a specific node
void free_node(NODE_t *node) {
    free(node);
}

/*
logic to create viewport
since we know that we always start with oceans to the bottom and to the right of the player
we can hard-code the creation of the viewport
*/
NODE_t* create_viewport(NODE_t *map_head) {
    NODE_t* map_Node = map_head->up->left;

    NODE_t **a = (NODE_t**)calloc(9, sizeof(NODE_t*));
    int i, j;

    for(j = 0; j < 3; j++) {
        for(i = 0; i < 3; i++) {

            switch(j * 3 + i) {
                case 0:
                    a[0] = copy_node(map_Node);
                    map_Node = map_Node->right;
                    break;
                case 1:
                    a[1] = copy_node(map_Node);
                    map_Node = map_Node->left;
                    map_Node = map_Node->down;
                    break;
                case 2:
                    a[2] = create_node(' ', 2, 0);
                    break;
                case 3:
                    a[3] = copy_node(map_Node);
                    map_Node = map_Node->right;
                    break;
                case 4:
                    a[4] = copy_node(map_Node);
                    break;
                case 5:
                    a[5] = create_node('O', 2, 1);
                    break;
                default:
                    a[j * 3 + i] = create_node('O', 2, 1);
                    break;

            }
        }
    }

    NODE_t *vp_head = create_map(a, 3);
    free(a);

    return vp_head->down->right;
}

//copying the nodes from map into viewport
NODE_t* copy_node(NODE_t *node) {
    NODE_t *temp = malloc(sizeof(NODE_t));
    // printf("\ncopy_node");
    *temp = *node;
    temp->right = NULL;
    temp->left = NULL;
    temp->up = NULL;
    temp->down = NULL;
    return temp;
}

//printing the viewport
void print_viewport(NODE_t *viewport) {
    // printf("viewport print\n");
    NODE_t* temp = viewport;

    printf("Health: %d\n", health);
    printf("\n");
    printf("\n---------\n");
    print_viewport_row(temp->up);
    print_viewport_row(temp);
    print_viewport_row(temp->down);
    printf("\n");
}

//printing the individual rows of the viewport
void print_viewport_row(NODE_t *row) {

    NODE_t *node = row;

    if(row->left == NULL) {
        printf("|%c|",'O');    
    }
    else {
        print_node(row->left);
    }

    print_node(row);

    if(row->right == NULL) {
        printf("|%c|",'O');
    }
    else {
        print_node(row->right);
    }
    printf("\n---------\n");
    
}

//promting the user to pick a direction
void pick_direction()
{
    char input = ' ';
    printf("Which direction would you like to go?\n");
    scanf(" %c", &input);

    switch (input)
    {
        case 'u':
            move_up();
            break;
        case 'd':
            move_down();
            break;
        case 'l':
            move_left();
            break;
        case 'r':
            move_right();
            break;
        default:
            printf("That was not a direction! Try again\n");
            pick_direction();
            break;
    }
}

/*
checking eacbh node and determining what to do
whether to add health, take health, if it's the goal etc...
*/
int check_node(NODE_t *node) {
    switch(node->type) {
        case OCEAN:
            printf("You cannot traverse the Ocean, try a different Direction\n");
            return 0;
        case RIVER:
            printf("You have encountered a River!\n");
            if(confirm_choice(node->type) == 1) {
                printf("You take %d points of damage\n", 20);
                health = health - 20;
                return 1;
            }
            else
                return 0;
            break;
        case DISEASE:
            switch(node->threat.disease.display_char) {
                case 'D':
                    printf("You have Dissentary! You take %d points of damage\n", node->threat.disease.health_mod);
                    health = health + node->threat.disease.health_mod;
                    return 1;
                    break;
                case 'F':
                    printf("You have the Flu! You take %d points of damage\n", node->threat.disease.health_mod);
                    health = health + node->threat.disease.health_mod;
                    return 1;
                    break;
                case 'C':
                    printf("You have a Cold! You take %d points of damage\n", node->threat.disease.health_mod);
                    health = health + node->threat.disease.health_mod;
                    return 1;
                    break;
                default:
                    printf("You have encountered a Disease! You take %d points of damage\n", node->threat.disease.health_mod);
                    health = health + node->threat.disease.health_mod;
                    return 1;
            }
            break;
        case ANIMAL:
            printf("You have encountered an Animal\n");
            switch(node->threat.animal.display_char){
                case 'E':
                    printf("Its an Elk!\n");
                    if(confirm_choice(node->type) == 1) {
                        printf("You get %d points of health!\n", node->threat.animal.health_mod);
                        health = health + node->threat.animal.health_mod;
                        node->type == NOTHING;
                        return 1;
                    }
                    else
                        return 0;
                    break;
                case 'H':
                    printf("It's a Hare!\n");
                    if(confirm_choice(node->type) == 1) {
                        printf("You get %d points of health!\n", node->threat.animal.health_mod);
                        health = health + node->threat.animal.health_mod;
                        node->type == NOTHING;
                        return 1;
                    }
                    else
                        return 0;
                    break;
                case 'G':
                    printf("Its an Grizzlty Bear!\n");
                    if(confirm_choice(node->type) == 1) {
                        printf("You take %d points of damage\n", node->threat.animal.health_mod);
                        health = health + node->threat.animal.health_mod;
                        node->type == NOTHING;
                        return 1;
                    }
                    else
                        return 0;
                    break;
                case 'B':
                    printf("Its a Boar!\n");
                    if(confirm_choice(node->type) == 1) {
                        printf("You take %d points of damage\n", node->threat.animal.health_mod);
                        health = health + node->threat.animal.health_mod;
                        node->type = NOTHING;
                        return 1;
                    }
                    else
                        return 0;
                    break;
                default:
                    return 0;
                    break;
            }
            break;
        case NOTHING:
            printf("This was a nice empty field, you take no damage\n");
            return 1;
            break;
        case GOAL:
            finish = 1;
            printf("\n\nYou've made it to the goal! congradulations! You didn't die~!\n");
            return 1;
            break;
        default:
            return 0;
            break;
    }
    return 0;
}

//confirming the players choice if it is a river or an animal
int confirm_choice(THREAT_TYPE_e threat_type) {
    char input = ' ';
    if(threat_type == RIVER){
        printf("Will you cross the river? y/n\n");
        scanf(" %c", &input);
        if(input == 'y') {
            printf("Crossing the river......\n");
            return 1;
        }
        else {
            printf("Returning to previous spot......\n");
            return 0;
        }
    }
    else if(threat_type == ANIMAL){
        printf("Will you hunt the animal? y/n\n");
        scanf(" %c", &input);
        if(input == 'y') {
            printf("Hunting the animal.....\n");
            return 1;
        }
        else {
            printf("Returning to previous spot.....\n");
            return 0;
        }
    }
}

//updating the nodes
void update(NODE_t *node, NODE_t *VP) {
    // printf("updating...\n");
    node->type = VP->type;
    // printf("updating...\n");
    node->discovered = VP->discovered;
        // printf("updated...\n");

}


//logic for dynamically adding and linking each new node to the viewport
void add_node_to_viewport(NODE_t* node, NODE_t* VP, CHOICE_e choice){
    switch(choice) {
        case UP:
            //move the pointers up
            viewport = viewport->up;
            map_head = map_head->up;

            //move temp pointers up
            VP = VP->up;
            node = node->up;
            //creating all of the nodes above 
            //if the node above does exist, check the surrounding nodes if they're oceans
            if(node->up) {
                // printf("adding nodes to viewport");
                VP->up = node->up ? copy_node(node->up) : create_node('O', VP->XLocation, VP->YLocation - 1);
                VP->up->left = node->up->left ? copy_node(node->up->left) : create_node('O', VP->XLocation - 1, VP->YLocation - 1);
                VP->up->right = node->up->right ? copy_node(node->up->right) : create_node('O', VP->XLocation + 1, VP->YLocation - 1);
                
            }
            //creating the ocean cieling if the above node is an ocean
            else {
                // printf("creating ocean nodes\n");
                VP->up = create_node('O', VP->XLocation, VP->YLocation + 1);
                VP->up->left = create_node('O', VP->XLocation - 1, VP->YLocation + 1);
                VP->up->right = create_node('O', VP->XLocation + 1, VP->YLocation + 1);

            }
                //creating links between new nodes
                VP->up->up = NULL;
                VP->up->down = VP;

                VP->up->left->left = NULL;
                VP->up->left->up = NULL;
                VP->up->left->right = VP->up;
                VP->up->left->down = VP->left;
                
                //creating links between new nodes
                VP->up->right->left = VP->up;
                VP->up->right->up = NULL;
                VP->up->right->right = NULL;
                VP->up->right->down = VP->right;

                //creating links between existing nodes and new nodes
                VP->left->up = VP->up->left;
                VP->right->up = VP->up->right;
            break;

        /* 
        cases LEFT, RIGHT, and DOWN are all very similar to UP, except with the correct orientation
        to link the nodes together
        */
        case LEFT:
            //move left one
            viewport = viewport->left;
            map_head = map_head->left;
            // printf("adding nodes to viewport");

            //move left one
            VP = VP->left;
            node = node->left;

            if(node->left) {
                // printf("adding nodes to viewport left");
                VP->left = node->left ? copy_node(node->left) : create_node('O', VP->XLocation - 1, VP->YLocation);
                VP->left->up = node->left->up ? copy_node(node->left->up) : create_node('O', VP->XLocation - 1, VP->YLocation - 1);
                VP->left->down = node->left->down ? copy_node(node->left->down) : create_node('O', VP->XLocation - 1, VP->YLocation + 1);       
            }
            else {
                // printf("creating ocean nodes\n");
                VP->left = create_node('O', VP->XLocation - 1, VP->YLocation);
                VP->left->up = create_node('O', VP->XLocation - 1, VP->YLocation - 1);
                VP->left->down = create_node('O', VP->XLocation - 1, VP->YLocation + 1);

            }

                VP->left->left = NULL;
                VP->left->right = VP;
                //creating links between new nodes
                VP->left->up->left = NULL;
                VP->left->up->up = NULL;
                VP->left->up->right = VP->up;
                VP->left->up->down = VP->left;
                
                //creating links between new nodes
                VP->left->down->right = VP->down;
                VP->left->down->left = NULL;
                VP->left->down->down = NULL;
                VP->left->down->up = VP->left;

                //creating links between existing nodes and new nodes
                VP->down->left = VP->left->down;
                VP->up->left = VP->left->up;
            break;

        case RIGHT:
            //move right one
            viewport = viewport->right;
            map_head = map_head->right;
            // printf("adding nodes to viewport");

            //move right one
            VP = VP->right;
            node = node->right;

            if(node->right) {
                // printf("adding nodes to viewport right");
                VP->right = node->right ? copy_node(node->right) : create_node('O', VP->XLocation + 1, VP->YLocation);
                VP->right->up = node->right->up ? copy_node(node->right->up) : create_node('O', VP->XLocation + 1, VP->YLocation - 1);
                VP->right->down = node->right->down ? copy_node(node->right->down) : create_node('O', VP->XLocation + 1, VP->YLocation + 1);       
            }
            else {
                // printf("creating ocean nodes\n");
                VP->right = create_node('O', VP->XLocation + 1, VP->YLocation);
                VP->right->up = create_node('O', VP->XLocation + 1, VP->YLocation - 1);
                VP->right->down = create_node('O', VP->XLocation + 1, VP->YLocation + 1);

            }

                VP->right->right = NULL;
                VP->right->left = VP;
                //creating links between new nodes
                VP->right->up->right = NULL;
                VP->right->up->up = NULL;
                VP->right->up->right = VP->up;
                VP->right->up->down = VP->right;
                
                //creating links between new nodes
                VP->right->down->left = VP->down;
                VP->right->down->right = NULL;
                VP->right->down->down = NULL;
                VP->right->down->up = VP->right;

                //creating links between existing nodes and new nodes
                VP->down->right = VP->right->down;
                VP->up->right = VP->right->up;
            break;

        case DOWN:            
            //move up one
            viewport = viewport->down;
            map_head = map_head->down;

            //move down one
            VP = VP->down;
            node = node->down;
            // printf("exist\n");
            //creating all of the nodes above 
            if(node->down) {
                // printf("adding nodes to viewport");
                VP->down = node->down ? copy_node(node->down) : create_node('O', VP->XLocation, VP->YLocation + 1);
                VP->down->left = node->down->left ? copy_node(node->down->left) : create_node('O', VP->XLocation - 1, VP->YLocation + 1);
                VP->down->right = node->down->right ? copy_node(node->down->right) : create_node('O', VP->XLocation + 1, VP->YLocation + 1);
                
            }
            //creating the ocean floor
            else {
                // printf("creating ocean nodes\n");
                VP->down = create_node('O', VP->XLocation, VP->YLocation + 1);
                VP->down->left = create_node('O', VP->XLocation - 1, VP->YLocation + 1);
                VP->down->right = create_node('O', VP->XLocation + 1, VP->YLocation + 1);

            }
                //creating links between new nodes
                VP->down->down = NULL;
                VP->down->up = VP;

                VP->down->left->left = NULL;
                VP->down->left->down = NULL;
                VP->down->left->right = VP->down;
                VP->down->left->up = VP->left;
                
                //creating links between new nodes
                VP->down->right->left = VP->down;
                VP->down->right->down = NULL;
                VP->down->right->right = NULL;
                VP->down->right->up = VP->right;

                //creating links between existing nodes and new nodes
                VP->left->up = VP->up->left;
                VP->right->up = VP->up->right;
            break;
    }
}

//logic for moving up
void move_up() {
    //if the above node is not an ocean
    if(viewport->up->type != OCEAN) {
        //saying you have discovered the node
        viewport->up->discovered = 1;

        //if this function returns a 1, that means the user is moving to the node above
        if(check_node(viewport->up) == 1) {
            // printf("checked node\n");

            //update current node to show nothing
            if(viewport->type == PLAYER) {
                viewport->type = NOTHING;
            }
            //changes the animals tile to nothing after the animal is hunted
            else if(viewport->type == ANIMAL) {
                viewport->type = NOTHING;
            }
            //free row of ocean tiles
            if(viewport->down->type == OCEAN) {
                // printf("down type = ocean");
                free_node(viewport->down->left);
                free_node(viewport->down->right);
                free_node(viewport->down);
            }
            //else going to update the map and check/free the important nodes
            else {
                // printf("updating the map and freeing important nodes");
                if(viewport->down->right->type == OCEAN) {
                    free_node(viewport->down->right);
                }
                else {
                    update(map_head->down->right, viewport->down->right);
                    free_node(viewport->down->right);
                }

                if(viewport->down->left->type == OCEAN) {
                    free_node(viewport->down->left);
                }
                else {
                    update(map_head->down->left, viewport->down->left);
                    free_node(viewport->down->left);
                }
            }

            //setting the pointers to null
            viewport->left->down = NULL;
            viewport->right->down = NULL;
            viewport->down = NULL;
            add_node_to_viewport(map_head, viewport, UP);  
        }
    }
    //if the above node is an ocean you should not move and repromt user for direction
    else{
        printf("You can not traverse the water");
    }

}

/*
MOVE DOWN, LEFT, RIGHT are all basically the same 
as move up except with the different orientation
*/
void move_down() {
    if(viewport->down->type != OCEAN) {
        //you have discovered the node
        viewport->down->discovered = 1;
        if(check_node(viewport->down) == 1) {
            // printf("checked node\n");

            //update current node to show nothing
            if(viewport->type == PLAYER) {
                viewport->type = NOTHING;
            }
            else if(viewport->type == ANIMAL) {
                viewport->type = NOTHING;
            }

            //free row of ocean tiles
            if(viewport->up->type == OCEAN) {
                // printf("up type = ocean");
                free_node(viewport->up->left);
                free_node(viewport->up->right);
                free_node(viewport->up);
            }
            //else going to update the map and free the important nodes
            else {
                // printf("updating the map and freeing important nodes");
                if(viewport->up->right->type == OCEAN) {
                    free_node(viewport->up->right);
                }
                else {
                    update(map_head->up->right, viewport->up->right);
                    free_node(viewport->up->right);
                }

                if(viewport->up->left->type == OCEAN) {
                    free_node(viewport->up->left);
                }
                else {
                    update(map_head->up->left, viewport->up->left);
                    free_node(viewport->up->left);
                }
            }
            viewport->left->up = NULL;
            viewport->right->up = NULL;
            viewport->up = NULL;
            add_node_to_viewport(map_head, viewport, DOWN);  
        }
    }

    else{
        printf("You can not traverse the water\n");
    }

}

void move_left() {
    if(viewport->left->type != OCEAN) {
        viewport->left->discovered = 1;
        if(check_node(viewport->left) == 1) {
            if(viewport->type == PLAYER) {
                viewport->type = NOTHING;
            }
            else if(viewport->type == ANIMAL) {
                viewport->type = NOTHING;
            }

            //freeing the column of ocean
            if(viewport->right->type == OCEAN) {
                free_node(viewport->right->up);
                free_node(viewport->right->down);
                free_node(viewport->right);
            }
            else {
                if(viewport->right->up->type == OCEAN) {
                    free_node(viewport->right->up);
                }
                else {
                    update(map_head->right->up, viewport->right->up);
                    free(viewport->right->up);
                }

                if(viewport->right->down->type == OCEAN) {
                    free_node(viewport->right->down);
                }
                else {
                    update(map_head->right->down, viewport->right->down);
                    free(viewport->right->down);
                }
            }
        viewport->right->up = NULL;
        viewport->right->down = NULL;
        viewport->right = NULL; 
        add_node_to_viewport(map_head, viewport, LEFT);  
        }
    }
    else{
        printf("You can't walk on water\n");
    }
}

void move_right() {
    if(viewport->right->type != OCEAN) {
        viewport->right->discovered = 1;
        if(check_node(viewport->right) == 1) {
            if(viewport->type == PLAYER) {
                viewport->type = NOTHING;
            }
            else if(viewport->type == ANIMAL) {
                viewport->type = NOTHING;
            }

            //freeing the column of ocean
            if(viewport->left->type == OCEAN) {
                free_node(viewport->left->up);
                free_node(viewport->left->down);
                free_node(viewport->left);
            }
            else {
                if(viewport->left->up->type == OCEAN) {
                    free_node(viewport->left->up);
                }
                else {
                    update(map_head->left->up, viewport->left->up);
                    free(viewport->left->up);
                }

                if(viewport->left->down->type == OCEAN) {
                    free_node(viewport->left->down);
                }
                else {
                    update(map_head->left->down, viewport->left->down);
                    free(viewport->left->down);
                }
            }
        viewport->left->up = NULL;
        viewport->left->down = NULL;
        viewport->left = NULL; 
        add_node_to_viewport(map_head, viewport, RIGHT);  
        }
    }
    else{
        printf("You can't walk on water\n");
    }
}

//gives the player instructions on the game rules and how to play
void Instructions()
{
    printf("\n\nThe game you are about to play is called Oregon Trail!");
    printf("\nYou move using the keys\n'U'(UP)\n'D'(DOWN)\n'L'(LEFT)\n'R'(RIGHT)");
    printf("\nYou will have to move through the map and discover what awaits!");
    printf("\nThere are a few different tiles that you can land on!");
    printf("\nOne type of tile is Animals where you will encounter a few different aninals.");
    printf("\nIf you encounter an animal you will be prompted to either hunt or not.");
    printf("\nBe careful, some of the animals can hurt your health.");
    printf("\nYou may encounter different kinds of diseases as you travel,");
    printf("\nbe weary of your health and don't let it get too low!");
    printf("\nRivers may be passed.....at a price...will you risk it?");
    printf("\nNow go forth and travel across the great Oregon Trail!\n\n\n");
    StartMenu();
}

//Gives the player a basic start menu and prompts for an input
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



/*
This was how I was going to create my viewport but it kept segment faulting on me and after
5 hours of debugging I gave up and asked a classmate on insight on how to create the viewport
*/

//creating the viewport
// NODE_t** create_viewport(NODE_t *map_head) {
    
//     NODE_t **viewport = (NODE_t **)calloc(9, sizeof(NODE_t *));

//     //trying to create the viewport by checking the 
//     //necessary node locations and creating if it's out of bounds
//     int x, y;
//     x = map_head->XLocation;
//     y = map_head->YLocation;
    
//     if(map_head->up->left) {
//         viewport[0] = copy_node(map_head->up->left);
//     }
//     else {
//         viewport[0] = NULL;//create_node('O', x - 1, y - 1);
//     }

//     if(map_head->up) {
//         viewport[1] = copy_node(map_head->up);
//     }
//     else {
//         viewport[1] = NULL;//create_node(map_head->up);
//     }

//     if(map_head->up->right) {
//         viewport[2] = copy_node(map_head->up->right);
//     }
//     else {
//         viewport[2]= NULL;//reate_node('O', x + 1, y - 1);
//     }

//     if(map_head->left) {
//         viewport[3] = copy_node(map_head->left);
//     }
//     else {
//         viewport[3] = NULL;// create_node('O', x - 1, y);
//     }

//     viewport[4] = copy_node(map_head);

//     if(map_head->right) {
//         printf("%p", map_head->right);
//         viewport[5] = copy_node(map_head->right);
//     }
//     else {
//         viewport[5] = NULL;//create_node('O', x + 1, y);
//     }

//     if(map_head->down->left) {
//         viewport[6] = copy_node(map_head->down->left);
//     }
//     else {
//         viewport[6] = NULL;//('O', x - 1, y + 1);
//     }

//     if(map_head->down) {
//         viewport[7] = copy_node(map_head->down);
//     }
//     else {
//         viewport[7] = NULL;//create_node('O', x, y + 1);
//     }

//     if(map_head->down->right) {
//         viewport[8] = copy_node(map_head->down->right);
//     }
//     else {
//         viewport[8] = NULL;//create_node('O', map_head->XLocation + 1, y + 1);
//     }

//     return viewport;
// }