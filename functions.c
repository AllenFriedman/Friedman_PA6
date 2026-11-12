#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>   
#include <stdlib.h>
#include "functions.h"
#include <string.h>

// Defines Syntax Tools
#define RED   "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define GRAY  "\033[90m"
#define BOLD  "\033[1m"
#define RESET "\033[0m"

// Defines ship sizes
#define CARRIER_SIZE 5;
#define BATTLESHIP_SIZE 4;
#define CRUISER_SIZE 3;
#define SUBMARINE_SIZE 3;
#define DESTROYER_SIZE 2;

// Initializes carrier ship
Ship init_carrier(void){
    Ship carrier = {0};
    carrier.ship_type = CARRIER;
    carrier.size = CARRIER_SIZE;
    carrier.hits = 0;
    carrier.row = -1;
    carrier.column = -1;
    carrier.symbol = 'C';
    return carrier;

}

Ship init_battleship(void){
    Ship battleship = {0};
    battleship.ship_type = BATTLESHIP;
    battleship.size = BATTLESHIP_SIZE;
    battleship.hits = 0;
    battleship.row = -1;
    battleship.column = -1;
    battleship.symbol = 'B';
    return battleship;

}

Ship init_cruiser(void){
    Ship cruiser = {0};
    cruiser.ship_type = CRUISER;
    cruiser.size = CRUISER_SIZE;
    cruiser.hits = 0;
    cruiser.row = -1;
    cruiser.column = -1;
    cruiser.symbol = 'c';
    return cruiser;

}

Ship init_submarine(void){
    Ship submarine = {0};
    submarine.ship_type = SUBMARINE;
    submarine.size = SUBMARINE_SIZE;
    submarine.hits = 0;
    submarine.row = -1;
    submarine.column = -1;
    submarine.symbol = 's';
    return submarine;

}
Ship init_destroyer(void){
    Ship destroyer = {0};
    destroyer.ship_type = DESTROYER;
    destroyer.size = DESTROYER_SIZE;
    destroyer.hits = 0;
    destroyer.row = -1;
    destroyer.column = -1;
    destroyer.symbol = 'd';
    return destroyer;

}
// Inits all ships for a board
Ships init_ships(void){
    Ships ships = {0};
    ships.ship[0] = init_carrier();
    ships.ship[1] = init_battleship();
    ships.ship[2] = init_cruiser();
    ships.ship[3] = init_submarine();
    ships.ship[4] = init_destroyer();
    return ships;

}
 Board init_board(void){
    Board board = {0};
    set_board(board.visible_grid);
    set_board(board.hidden_grid);
    board.ships = init_ships();
    return board;
 }
Player init_player(const char* name){
    Player player = {0};
    player.board = init_board();
    strcpy(player.name, name);
    player.has_won = false;
    return player;
}
CPU init_cpu(void){
    CPU cpu = {0};
    cpu.board = init_board();
    random_place_ships(&cpu.board);
    cpu.cpu_logic = SEARCHING;
    cpu.has_won = false;
    return cpu;
}
void get_name(char* name){
    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        return;
    }

    name[strcspn(name, "\n")] = '\0';
}
bool is_won(void);
void set_board(char grid[BOARD_SIZE][BOARD_SIZE]){
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            grid[i][j] = '~';
        }
    }
    
}
int decode_character(char character){
    character = (character > 'Z') ? character - 32 : character;
    switch (character)
    {
    case 'A': // Row A
        return 0;
    case 'B': // Row B
        return 1;
    case 'C': // Row C
        return 2;
    case 'D': // Row D
        return 3;
    case 'E': // Row E
        return 4;
    case 'F': // Row F
        return 5;
    case 'G': // Row G
        return 6;
    case 'H': // Row H
        return 7;
    case 'I': // Row I
        return 8;
    case 'J': // Row J
        return 9;
    
    default:
        return -1;
    }
}
void attack_board(char visible_grid[BOARD_SIZE][BOARD_SIZE], char hidden_grid[BOARD_SIZE][BOARD_SIZE]){
    int row = 0, result = 0, ch;
    bool is_valid_choice = false, is_row_valid = false, is_column_valid = false, is_repeated_attack = false;
    char column = '\0';
    char buffer[100] = "";
    printf("Attack your opponent by choosing a cell to attack (enter row then column; for example 4A): ");

    do{
        if(fgets(buffer, sizeof(buffer),stdin) == NULL){
            return;
        }
        char extra = '\0';
        if(sscanf(buffer,"%d %c %c", &row, &column, &extra) != 2){
                printf("Invalid cell, enter the coordinates in the proper format: ");
                continue;
            }
        is_row_valid =  (row > 0 && row <= BOARD_SIZE);
        is_column_valid = (column >= 'A' && column <= 'J') || (column >= 'a' && column <= 'j');
        if(!(is_column_valid && is_row_valid)){
            printf("Invalid cell, enter an apropiate number and letter: ");
            continue;
        }
        is_repeated_attack = visible_grid[row - 1][decode_character(column)] != '~';
        is_valid_choice = is_row_valid &&  is_column_valid && !is_repeated_attack;
        if(!is_valid_choice){
            printf("You already attacked this cell, enter a different one: ");
            continue;
        }
        clear_screen();
        
    }while(!is_valid_choice);
    visible_grid[row - 1][decode_character(column)] = hidden_grid[row - 1][decode_character(column)] == 'X' ? 'X': 'O';
}
void display_board(char grid[BOARD_SIZE][BOARD_SIZE]){
    printf(BOLD"    A  B  C  D  E  F  G  H  I  J \n"RESET);
    for(int i = 0; i < BOARD_SIZE; i++){
        if(i + 1 < 10){
            printf(BOLD" %d "RESET, i + 1);

        }
        else{
            printf(BOLD"%d "RESET, i + 1);
        }
        for(int j = 0; j < BOARD_SIZE; j++){
            switch(grid[i][j]){
            case '~':
            printf(BLUE" %c "RESET, grid[i][j]);
            break;
            case 'X':
            printf(RED" %c "RESET, grid[i][j]);
            break;
            case 'O':
            printf(GRAY" %c "RESET, grid[i][j]);
            break;
            default:
            printf(RED " %c "RESET, grid[i][j]);

        }
        }
        printf("\n");
    }
}
void random_attack_board(char grid[BOARD_SIZE][BOARD_SIZE]){

    int row = 0, column = 0;

        do{
            row = rand() % BOARD_SIZE;
            column = rand() % BOARD_SIZE;

        } while(grid[row][column] != '~' && grid[row][column] != 'O');

        
        grid[row][column] = 'O';
}
void random_place_ship(char hidden_grid[BOARD_SIZE][BOARD_SIZE], Ship* ship) {
    int row = 0, column = 0, direction = 0;
    bool ship_placed = false;
    bool collision = false;

    do {
        row = rand() % BOARD_SIZE;
        column = rand() % BOARD_SIZE;
        direction = (rand() % 4) + 1;

        collision = false;  

        switch(direction) {

            // right
            case 1:
                if(column + (*ship).size <= BOARD_SIZE) {

                    for(int i = 0; i < (*ship).size; i++) {
                        if(hidden_grid[row][column + i] != '~') {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row][column + i] = (*ship).symbol;
                        }
                        ship_placed = true;
                    }
                }
                break;

            // down
            case 2:
                if(row + (*ship).size <= BOARD_SIZE) {

                    for(int i = 0; i < (*ship).size; i++) {
                        if(hidden_grid[row + i][column] != '~') {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row + i][column] = (*ship).symbol;
                        }
                        ship_placed = true;
                    }
                }
                break;

            // left
            case 3:
                if(column - ((*ship).size - 1) >= 0) {

                    for(int i = 0; i < (*ship).size; i++) {
                        if(hidden_grid[row][column - i] != '~') {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row][column - i] = (*ship).symbol;
                        }
                        ship_placed = true;
                    }
                }
                break;

            // right
            case 4:
                if(row - ((*ship).size - 1) >= 0) {

                    for(int i = 0; i < (*ship).size; i++) {
                        if(hidden_grid[row - i][column] != '~') {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row - i][column] = (*ship).symbol;
                        }
                        ship_placed = true;
                    }
                }
                break;

            default:
                break;
        }

    } while(!ship_placed);
    (*ship).row = row + 1;
    (*ship).column = column + 1;
}
void random_place_ships(Board* board){
    for(int i = 0; i < MAX_SHIPS; i++){
        random_place_ship((*board).hidden_grid,&(*board).ships.ship[i]);
    }

}
//simpler get int
int get_user_int(void) {
    int number;

    scanf("%d", &number);
    return number;
        
    
}
//simpler get char
char get_user_char(void) {
    char letter;
    if (scanf(" %c", &letter) != 1) {
        exit(0);
    }
    return letter;
}
//clears screen
void clear_screen(void) {
    printf("\033[2J\033[H");
}



