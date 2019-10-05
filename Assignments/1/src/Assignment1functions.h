#ifndef A1FUNCS_h
#define A1FUNCS_h
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "a1_defs.h"

int StartMenu();
int lineSize(FILE* mapData);
void Instructions();
void GameStart(char *fileName);
FILE* LoadMap(char *fileName);
int numOfLines(FILE *filename);
NODE_t** ParseFile(FILE* MapData, NODE_t** array);
void viewPort(); //TODO implement a method to print current location in a 3x3 matrix

//code from instructor
ANIMAL_t make_animal(char display_char);
DISEASE_t make_disease(char display_char);
NODE_t* create_node(char display_char, int x, int y);
NODE_t* find_node(int x, int y);
NODE_t* create_map(NODE_t **array);
void free_map(NODE_t *head);
void print_node(NODE_t* node);
void print_map(NODE_t* head);


NODE_t* create_viewport(NODE_t *map_head);
NODE_t* copy_node(NODE_t *node);
void print_viewport(NODE_t *viewport);
void move_up(NODE_t *map, NODE_t** viewport);
void move_down(NODE_t *map, NODE_t** viewport);
void move_left(NODE_t *map, NODE_t** viewport);
void move_right(NODE_t *map, NODE_t** viewport);

void print_viewport_row(NODE_t *row);
void free_node(NODE_t *map, NODE_t* node);
void add_node_to_viewport(NODE_t* node, NODE_t* viewport);

void check_node(CHOICE_e choice, NODE_t *map, NODE_t** viewport);
int confirm_choice(THREAT_TYPE_e threat_type, THREAT_t threat);
CHOICE_e pick_direction();

#endif