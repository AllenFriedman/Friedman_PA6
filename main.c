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
    clear_screen();
    
    CPU cpu = init_cpu();
    Player player = init_player("Allen");
    char (*hidden_grid)[BOARD_SIZE] = cpu.board.hidden_grid;    
    char (*visible_grid)[BOARD_SIZE] = cpu.board.visible_grid;
    

    display_board(hidden_grid);
    display_board(visible_grid);
    for(int i = 0; i < 4; i++){
        printf("(%d, %d), ", (cpu).board.ships.ship[1].rows[i], cpu.board.ships.ship[1].columns[i]);
    }
    printf("\n");
    while(!cpu.has_won){
        attack_board(&cpu.board);
        clear_screen();
        display_board(hidden_grid);
        display_board(visible_grid);
        update_winner(&cpu,&player);
    }
    
    return 0;
}