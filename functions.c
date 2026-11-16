#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>   
#include <stdlib.h>
#include "functions.h"
#include <string.h>


// Initializes carrier ship
Ship init_carrier(void){
    Ship carrier = {0};
    carrier.ship_type = CARRIER;
    carrier.size = CARRIER_SIZE;
    carrier.hits = 0;
    init_empty_coordinates(carrier.rows, carrier.size);
    init_empty_coordinates(carrier.columns, carrier.size);
    carrier.symbol = 'C';
    carrier.sunk = false;
    return carrier;

}

Ship init_battleship(void){
    Ship battleship = {0};
    battleship.ship_type = BATTLESHIP;
    battleship.size = BATTLESHIP_SIZE;
    battleship.hits = 0;
    init_empty_coordinates(battleship.rows, battleship.size);
    init_empty_coordinates(battleship.columns, battleship.size);
    battleship.symbol = 'B';
    battleship.sunk = false;
    return battleship;

}

Ship init_cruiser(void){
    Ship cruiser = {0};
    cruiser.ship_type = CRUISER;
    cruiser.size = CRUISER_SIZE;
    cruiser.hits = 0;
    init_empty_coordinates(cruiser.rows, cruiser.size);
    init_empty_coordinates(cruiser.columns, cruiser.size);
    cruiser.symbol = 'c';
    cruiser.sunk = false;
    return cruiser;

}

Ship init_submarine(void){
    Ship submarine = {0};
    submarine.ship_type = SUBMARINE;
    submarine.size = SUBMARINE_SIZE;
    submarine.hits = 0;
    init_empty_coordinates(submarine.rows, submarine.size);
    init_empty_coordinates(submarine.columns, submarine.size);
    submarine.symbol = 's';
    submarine.sunk = false;
    return submarine;

}
Ship init_destroyer(void){
    Ship destroyer = {0};
    destroyer.ship_type = DESTROYER;
    destroyer.size = DESTROYER_SIZE;
    destroyer.hits = 0;
    init_empty_coordinates(destroyer.rows, destroyer.size);
    init_empty_coordinates(destroyer.columns, destroyer.size);
    destroyer.symbol = 'd';
    destroyer.sunk = false;
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
    random_place_ships(&player.board);
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
void play_turns(Player* player, CPU* cpu, whose_turn_t* turn){
    int player_turn_counter = 1, cpu_turn_counter = 1;
    while(!((*cpu).has_won || (*player).has_won)){
    switch(*turn){
        case PLAYER_TURN:
        printf(UNDERLINE"Player turn %d:\n\n"RESET, player_turn_counter);
        player_turn(&(*cpu).board);
        update_winner(cpu, player);
        printf("\nPress enter to continue...");
        getchar();
        clear_screen();
        player_turn_counter++;
        *turn = CPU_TURN;
        break;

        case CPU_TURN:
        printf(UNDERLINE"CPU turn %d:\n\n"RESET, cpu_turn_counter);
        cpu_turn(&(*player).board);
        update_winner(cpu, player);

        printf("\nPress enter to continue...");
        getchar();
        clear_screen();
        cpu_turn_counter++;
        *turn = PLAYER_TURN;
        break;
    }
}
}
void player_turn(Board* board){
    display_board((*board).visible_grid);
    attack_board((board));
    display_board((*board).visible_grid);
}
void cpu_turn(Board* board){
    random_attack_board(board);
    display_board((*board).visible_grid);
}
void reveal_sunk_ships(Board* board){
    for(int i = 0; i < MAX_SHIPS; i++){
        if((*board).ships.ship[i].sunk){
            int ship_size = (*board).ships.ship[i].size;
            for(int j = 0; j < ship_size; j++){
                int row = (*board).ships.ship[i].rows[j], column = (*board).ships.ship[i].columns[j];
                (*board).visible_grid[row][column] = (*board).hidden_grid[row][column];
            }
        }
    }
}
void update_sunk_status(Ships* ships){
    for(int i = 0; i < MAX_SHIPS; i++){
        int hits = (*ships).ship[i].hits;
        int size = (*ships).ship[i].size;
        bool ship_sunk = hits == size;
        if(ship_sunk){
            (*ships).ship[i].sunk = true;
        }
    }
}
void register_hit(Board* board, int row, int column){
    char cell = (*board).hidden_grid[row][column];
    if(cell == '~'){
        return;
    }
    
    switch(cell){
        case 'C':
        (*board).ships.ship[CARRIER].hits++;
        break;

        case 'B':
        (*board).ships.ship[BATTLESHIP].hits++;
        break;

        case 'c':
        (*board).ships.ship[CRUISER].hits++;
        break;

        case 's':
        (*board).ships.ship[SUBMARINE].hits++;
        break;

        case 'd':
        (*board).ships.ship[DESTROYER].hits++;
        break;
        
        default:
        break;
    }
}
void init_empty_coordinates(int* coordinate, int size){
    for(int i = 0; i < size; i ++){
        coordinate[i] = -1;
    }
}
void get_name(char* name){
    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        return;
    }

    name[strcspn(name, "\n")] = '\0';
}
void update_winner(CPU* cpu, Player* player){
    bool cpu_winner = true, player_winner = true;
    for(int i = 0; i < MAX_SHIPS; i++){
        bool ship_sunk = (*player).board.ships.ship[i].sunk;
        if(!ship_sunk){
            cpu_winner = false;
            break;
        }
    }
    if(cpu_winner){
        (*cpu).has_won = true;
        return;
    }

    for(int i = 0; i < MAX_SHIPS; i++){
        bool ship_sunk = (*cpu).board.ships.ship[i].sunk;
        if(!ship_sunk){
            player_winner = false;
            break;
        }
    }
    if(player_winner){
        (*player).has_won = true;
    }
}
bool is_won(CPU cpu, Player player){
    return cpu.has_won || player.has_won;

}
void set_board(char grid[BOARD_SIZE][BOARD_SIZE]){
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            grid[i][j] = WATER_CHARACTER;
        }
    }
    
}
int decode_character(char character){
    character = (character > 'Z') ? character - 32 : character;
    return character - 'A';
    
}
void attack_board(Board* board){
    int row = 0, column = 0;
    bool is_valid_choice = false, is_row_valid = false, is_column_valid = false, is_repeated_attack = false;
    char encoded_column = '\0', water = WATER_CHARACTER;
    char unknown_hit = UNKNOWN_HIT_CHARACTER;
    char miss = MISS_CHARACTER;
    char buffer[100] = "";
    printf("Attack your opponent by choosing a cell to attack (enter row then column; for example 4A): ");

    do{
        if(fgets(buffer, sizeof(buffer),stdin) == NULL){
            return;
        }
        char extra = '\0';
        if(sscanf(buffer,"%d %c %c", &row, &encoded_column, &extra) != 2){
                printf("\nInvalid cell, enter the coordinates in the proper format: ");
                continue;
            }
        is_row_valid =  (row > 0 && row <= BOARD_SIZE);
        is_column_valid = (encoded_column >= 'A' && encoded_column <= 'J') || (encoded_column >= 'a' && encoded_column <= 'j');
        if(!(is_column_valid && is_row_valid)){
            printf("Invalid cell, enter an apropiate number and letter: ");
            continue;
        }
        column = decode_character(encoded_column);
        row--;
        is_repeated_attack = (*board).visible_grid[row][column] != WATER_CHARACTER;
        is_valid_choice = is_row_valid &&  is_column_valid && !is_repeated_attack;
        if(!is_valid_choice){
            printf("You already attacked this cell, enter a different one: ");
            continue;
        }
        clear_screen();
        
    }while(!is_valid_choice);

    char hidden_grid_cell_character = (*board).hidden_grid[row][column];

    (*board).visible_grid[row][column] = (hidden_grid_cell_character != water) 
    && hidden_grid_cell_character != miss ? unknown_hit : miss;

    register_hit(board, row, column);
    update_sunk_status(&(*board).ships);
    reveal_sunk_ships(board);

}
void display_board(char grid[BOARD_SIZE][BOARD_SIZE]){
    char water = WATER_CHARACTER;
    char unknown_hit = UNKNOWN_HIT_CHARACTER;
    char miss = MISS_CHARACTER;
    printf("    ");
    for(int i = 0; i < BOARD_SIZE; i++){
        printf(BOLD"%c  ", (char)((int)'A' + i));
    }
    printf(RESET"\n");
    for(int i = 0; i < BOARD_SIZE; i++){
        if(i + 1 < 10){
            printf(BOLD" %d "RESET, i + 1);

        }
        else{
            printf(BOLD"%d "RESET, i + 1);
        }
        for(int j = 0; j < BOARD_SIZE; j++){
            char board_character = grid[i][j];
            bool is_water = board_character == water, 
            is_unknown_hit = board_character == UNKNOWN_HIT_CHARACTER,
            is_miss = board_character == MISS_CHARACTER;
            if(is_water){
                printf(BLUE" %c "RESET, board_character);
            }
            else if(is_unknown_hit){
                printf(RED" %c "RESET, board_character);
            }
            else if(is_miss){
                printf(GRAY" %c "RESET, board_character);
            }
            else {
                printf(RED " %c "RESET, grid[i][j]);
            }
        }
        printf("\n");
    }
}
void random_attack_board(Board* board){
    char water = WATER_CHARACTER;
    char unknown_hit = UNKNOWN_HIT_CHARACTER;
    char miss = MISS_CHARACTER;
    int row = 0, column = 0;
    char (*hidden_grid)[BOARD_SIZE] = (*board).hidden_grid;
    char (*visible_grid)[BOARD_SIZE] = (*board).visible_grid;


        do{
            row = rand() % BOARD_SIZE;
            column = rand() % BOARD_SIZE;

        } while(visible_grid[row][column] != water);

        
    visible_grid[row][column] = (hidden_grid[row][column] == water) ? miss : unknown_hit;

    register_hit(board, row, column);
    update_sunk_status(&(*board).ships);
    reveal_sunk_ships(board);
}
void edit_coordinate(int* row, int* column, int new_row, int new_column){
    *row = new_row;
    *column = new_column;
}
void random_place_ship(char hidden_grid[BOARD_SIZE][BOARD_SIZE], Ship* ship) {
    int row = 0, column = 0, direction = 0;
    bool ship_placed = false;
    bool collision = false;
    char water = WATER_CHARACTER;

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
                        if(hidden_grid[row][column + i] != water) {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row][column + i] = (*ship).symbol;
                            edit_coordinate(&(*ship).rows[i],&(*ship).columns[i], row, column + i);
                        }
                        ship_placed = true;
                    }
                }
                break;

            // down
            case 2:
                if(row + (*ship).size <= BOARD_SIZE) {

                    for(int i = 0; i < (*ship).size; i++) {
                        if(hidden_grid[row + i][column] != water) {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row + i][column] = (*ship).symbol;
                            edit_coordinate(&(*ship).rows[i],&(*ship).columns[i], row + i, column);
                        }
                        ship_placed = true;
                    }
                }
                break;

            // left
            case 3:
                if(column - ((*ship).size - 1) >= 0) {

                    for(int i = 0; i < (*ship).size; i++) {
                        if(hidden_grid[row][column - i] != water) {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row][column - i] = (*ship).symbol;
                            edit_coordinate(&(*ship).rows[i],&(*ship).columns[i], row, column - i);
                        }
                        ship_placed = true;
                    }
                }
                break;

            // right
            case 4:
                if(row - ((*ship).size - 1) >= 0) {

                    for(int i = 0; i < (*ship).size; i++) {
                        if(hidden_grid[row - i][column] != water) {
                            collision = true;
                            break;
                        }
                    }

                    if(!collision) {
                        for(int i = 0; i < (*ship).size; i++) {
                            hidden_grid[row - i][column] = (*ship).symbol;
                            edit_coordinate(&(*ship).rows[i],&(*ship).columns[i], row - i, column);
                        }
                        ship_placed = true;
                    }
                }
                break;

            default:
                break;
        }

    } while(!ship_placed);
    
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



