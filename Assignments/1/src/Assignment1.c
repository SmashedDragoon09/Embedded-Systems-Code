#include "Assignment1functions.h"


int main() { 
    //promts the user input what they want to do
    int mode = StartMenu();
    if(mode == 1) {
        //call stat of game function
        GameStart();
    }
    else if(mode == 2) {
        //call instruction method
        
    }
    else if(mode == 3) {
        //end game

        return 0;
    }
    return 0;
}
