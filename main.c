/*
Allen Friedman
PA6
10/31/2026
CPTS 121
Lab 9
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <strings.h>
#include "functions.h"



int main(void) {
    srand((unsigned int)time(NULL)); //makes random work
    printf("Enter your name: ");
    char name[20] = "";

    if (fgets(name, sizeof(name), stdin) == NULL) {
        return 1;
    }

    name[strcspn(name, "\n")] = '\0';
    clear_screen();
    Player user = init_player(name);
    char (*hidden_grid)[BOARD_SIZE] = user.board.hidden_grid;    
    char (*visible_grid)[BOARD_SIZE] = user.board.visible_grid;
    

    display_board(visible_grid);
    attack_board(visible_grid, hidden_grid);
    clear_screen();
    display_board(visible_grid);
    
    return 0;
}