#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

// Size constants
#define BOARD_SIZE 10
#define MAX_SHIPS 5

// Board Characters
#define WATER_CHARACTER '-'
#define UNKNOWN_HIT_CHARACTER 'X'
#define MISS_CHARACTER 'O'


// Defines Syntax Tools
#define RED   "\033[31m" // Red color
#define GREEN "\033[32m" // Green color
#define BLUE "\033[34m" // Blue color
#define GRAY  "\033[90m" // Gray color
#define BOLD  "\033[1m" // Bold font
#define RESET "\033[0m" // Used to reset adjustments to the print syntax

// Defines ship sizes
#define CARRIER_SIZE 5;
#define BATTLESHIP_SIZE 4;
#define CRUISER_SIZE 3;
#define SUBMARINE_SIZE 3;
#define DESTROYER_SIZE 2;

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
    REVERSE_FROM_ORIGIN
} cpu_logic_t;

// Ship definition
typedef struct ship{
    ship_t ship_type;
    int size;
    int hits;
    int rows[5];
    int columns[5];
    char symbol;
    bool sunk;
} Ship;

typedef struct ships{
    Ship ship[MAX_SHIPS]; // went against traditonal array naming conventions to simplify access --> Board/Ships/Ship
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
    char name[50];
    bool has_won;

} Player;

// CPU definition
typedef struct cpu{
    Board board;
    cpu_logic_t cpu_logic;
    bool has_won;
} CPU;

// Every init
/*
    Note down the basic Heirarchy between the structures
    ------------------------------------------------------------
    More_Dependent_Struct --> More_Independent_Struct (Not actual stucts)

    Player/CPU --> Board --> Ships --> Ship --> Ship_attributes
            |       |            
            |        --> Grids
            |
            v
        cpu_logic_t  (Specific to CPU)      
    ------------------------------------------------------------
    The more dependent structs rely on the existence of the independent structs
    As the structs become more independent, they tend to be standalone and specific
    cpu_logic_t is specific to CPU and is an enum or state-machine used to determine the CPU's game strategy
    PS: OOP would've made this easier
*/

Ship init_carrier(void);
Ship init_battleship(void);
Ship init_cruiser(void);
Ship init_submarine(void);
Ship init_destroyer(void);
Ships init_ships(void);
Board init_board(void);
Player init_player(const char name[50]);
CPU init_cpu(void);


// void functions
void edit_coordinate(int* row, int* column, int new_row, int new_column);
void get_name(char* name);
void init_empty_coordinates(int* coordinate, int size);
void random_place_ship(char hidden_grid[BOARD_SIZE][BOARD_SIZE], Ship* ship);
void random_place_ships(Board* board);
void reveal_sunk_ships(Board* board);
void update_sunk_status(Ships* ships);
void register_hit(Board* board, int row, int column);
void update_winner(CPU* cpu, Player* player);
void display_winnners_message(CPU cpu, Player player);
void set_board(char grid[BOARD_SIZE][BOARD_SIZE]);
void display_board(char grid[BOARD_SIZE][BOARD_SIZE]);
void attack_board(Board* board);
void random_attack_board(char grid[BOARD_SIZE][BOARD_SIZE]);
void play_turn(Player* player, int round);
void run(void);
void clear_screen(void);
void print_menu_choices(void);
void print_table(void);
void player_turn(Board* board);


int get_user_int(void);
int decode_character(char character);
int menu_choice(void);

bool is_won(CPU cpu, Player player);

char get_user_char(void);




#endif
