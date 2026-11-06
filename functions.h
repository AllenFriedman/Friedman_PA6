#include <stdbool.h>
#include <stdio.h>
#define BOARD_SIZE 9
#define MAX_SHIPS 5
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
// Defines the type of ship
typedef enum {
    CARRIER, 
    BATTLESHIP, 
    CRUISER, 
    SUBMARINE, 
    DESTROYER
} ship_t;
typedef enum{
    SEARCHING,
    FOUND_SHIP,
    DETERMINING_DIRECTION,
    FOLLOW_DIRECTION,
    REVERSE_FROM_ORIGIN,
    RESET
} cpu_logic_t;
typedef struct ship{
    ship_t ship_type;
    int size;
    int hits;
    int row;
    int column;
    char symbol;
} Ship;
typedef struct board{
    char visible_grid[BOARD_SIZE][BOARD_SIZE];
    char hidden_grid[BOARD_SIZE][BOARD_SIZE];
    Ship ships[MAX_SHIPS];
} Board;
typedef struct player{
    Board board;
    char name[20];
    bool has_won;

} Player;
typedef struct cpu{
    Board board;
    cpu_logic_t cpu_logic;
    bool has_won;
} CPU;
Ship init_carrier(void);
void random_place_ship(char hidden_grid[9][9], Ship* ship);
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

void add_players(int amount_of_players, Player players[]);
int get_score(Player* player, int category);
void set_score(Player* player, int category, int score);
int calculate_score(int dice[], int category);
void play_turn(Player* player, int round);
void run(void);



#endif
