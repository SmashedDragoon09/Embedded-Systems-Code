#include "Assignment1functions.h"


int main(int argc, char *argv []) { 
    //promts the user input what they want to do
    char *fileName = argv[1];

    StartMenu();
    GameStart(fileName);
    return 0;
}
