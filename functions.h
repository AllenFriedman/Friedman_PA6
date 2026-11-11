#include <stdbool.h>
#include <stdio.h>

//  Size constants
#define BOARD_SIZE 10
#define MAX_SHIPS 5
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Enums
// Defines the type of ship
typedef enum {
    CARRIER, 
    BATTLESHIP, 
    CRUISER, 
    SUBMARINE, 
    DESTROYER
} ship_t;
// CPU logic state machine
typedef enum{
    SEARCHING,
    FOUND_SHIP,
    DETERMINING_DIRECTION,
    FOLLOW_DIRECTION,
    REVERSE_FROM_ORIGIN,
    RESET
} cpu_logic_t;

// Ship definition
typedef struct ship{
    ship_t ship_type;
    int size;
    int hits;
    int row;
    int column;
    char symbol;
} Ship;

typedef struct ships{
    Ship ships[MAX_SHIPS];
} Ships;

// Board definition (Imagine two grids stacked, one visible and the other is used for logic)
typedef struct board{
    char visible_grid[BOARD_SIZE][BOARD_SIZE];
    char hidden_grid[BOARD_SIZE][BOARD_SIZE];
    Ships ships;
} Board;

// Player definition
typedef struct player{
    Board board;
    char name[20];
    bool has_won;

} Player;

// CPU definition
typedef struct cpu{
    Board board;
    cpu_logic_t cpu_logic;
    bool has_won;
} CPU;
Ship init_carrier(void);
Ship init_battleship(void);
Ship init_cruiser(void);
Ship init_submarine(void);
Ship init_destroyer(void);
Ships init_ships(void);
Board init_board(void);
Player init_player(const char name[20]);
CPU init_cpu(void);
void random_place_ship(char hidden_grid[BOARD_SIZE][BOARD_SIZE], Ship* ship);
bool is_won(void);
void set_board(char grid[BOARD_SIZE][BOARD_SIZE]);
void display_board(char grid[BOARD_SIZE][BOARD_SIZE]);
void attack_board(char visible_grid[BOARD_SIZE][BOARD_SIZE], char hidden_grid[BOARD_SIZE][BOARD_SIZE]);
void random_attack_board(char grid[BOARD_SIZE][BOARD_SIZE]);
int decode_character(char character);
void clear_screen(void);
void print_menu_choices(void);
void print_table(void);
int get_user_int(void);
char get_user_char(void);
int menu_choice(void);

void play_turn(Player* player, int round);
void run(void);



#endif
