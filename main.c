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
#include "functions.h"



int main(void) {
    srand((unsigned int)time(NULL)); //makes random work
    char game_board[9][9];
    char logic_board[9][9];
    Ship carrier = init_carrier();
    
    set_board(game_board);
    set_board(logic_board);

    display_board(game_board);
    
    random_place_ship(logic_board, &carrier);
    printf("%d %d\n", carrier.row, (carrier.column));
    while(true){
        attack_board(game_board,logic_board);
        display_board(game_board);
    }

    return 0;
}