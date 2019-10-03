#ifndef A1DEFS_H
#define A1DEFS_H

#include <stdio.h>

typedef struct animal_t{
    char display_char;
    int health_mod;
} ANIMAL_t;

typedef struct disease_t {
    char display_char;
    int health_mod;
} DISEASE_t;

typedef union threat {
    DISEASE_t disease;
    ANIMAL_t animal;
} THREAT_t;

typedef enum threat_type {
    PLAYER,
    GOAL,
    DISEASE,
    ANIMAL,
    NOTHING,
    RIVER,
    OCEAN
} THREAT_TYPE_e;

typedef struct node {
    THREAT_t threat;
    THREAT_TYPE_e type;
    int XLocation, YLocation;
    char discovered;
    struct node *up;
    struct node *down;
    struct node *right; 
    struct node *left;
} NODE_t;

typedef enum choice {
    UP, 
    LEFT, 
    DOWN, 
    RIGHT, 
    NO, 
    YES
} CHOICE_e;

#endif