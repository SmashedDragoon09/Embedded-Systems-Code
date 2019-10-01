#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int StartMenu();
void GameStart(char *fileName);
void LoadMap(char *fileName);
int numOfLines(FILE *filename);
void printCurrentLocation(); //TODO implement a method to print current location in a 3x3 matrix