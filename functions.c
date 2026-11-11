#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>   
#include "functions.h"

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
    ships.ships[0] = init_carrier();
    ships.ships[1] = init_battleship();
    ships.ships[2] = init_cruiser();
    ships.ships[3] = init_submarine();
    ships.ships[4] = init_destroyer();
    return ships;

}
 Board init_board(void){
    Board board = {0};
    set_board(board.visible_grid);
    set_board(board.hidden_grid);
    board.ships = init_ships();
    return board;
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
    case 'A':
        return 0;
    case 'B':
        return 1;
    case 'C':
        return 2;
    case 'D':
        return 3;
    case 'E':
        return 4;
    case 'F':
        return 5;
    case 'G':
        return 6;
    case 'H':
        return 7;
    case 'I':
        return 8;
    case 'J':
        return 9;
    
    default:
        return -1;
    }
}
void attack_board(char visible_grid[BOARD_SIZE][BOARD_SIZE], char hidden_grid[BOARD_SIZE][BOARD_SIZE]){
    int row = 0;
    bool is_valid_choice = false, is_row_valid = false, is_column_valid = false, is_repeated_attack = false;
    char column = '\0';
    printf("Attack your opponent by choosing a cell to attack (enter row then column; for example 4A): ");

    do{
        scanf("%d %c", &row, &column);
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




/*
//automatically adds players (was gonna be able to add 1-4)
void add_players(int amount_of_players, Player players[]) {
    for (int i = 0; i < amount_of_players; i++) {
        printf("Enter player %d's name (one word): ", i + 1);
        scanf("%20s", players[i].name);
        players[i].points = 0;

        players[i].table.ones = -1;
        players[i].table.twos = -1;
        players[i].table.threes = -1;
        players[i].table.fours = -1;
        players[i].table.fives = -1;
        players[i].table.sixes = -1;
        players[i].table.three_of_a_kind = -1;
        players[i].table.four_of_a_kind = -1;
        players[i].table.full_house = -1;
        players[i].table.small_straight = -1;
        players[i].table.large_straight = -1;
        players[i].table.yahtzee = -1;
        players[i].table.chance = -1;
    }
}

// gets a score from a section on the yahtzee table
int get_score(Player* player, int category) {
    switch (category) {
        case 1: return (*player).table.ones;
        case 2: return (*player).table.twos;
        case 3: return (*player).table.threes;
        case 4: return (*player).table.fours;
        case 5: return (*player).table.fives;
        case 6: return (*player).table.sixes;
        case 7: return (*player).table.three_of_a_kind;
        case 8: return (*player).table.four_of_a_kind;
        case 9: return (*player).table.full_house;
        case 10: return (*player).table.small_straight;
        case 11: return (*player).table.large_straight;
        case 12: return (*player).table.yahtzee;
        case 13: return (*player).table.chance;
    }
    return -1;
}

// sets scores on table
void set_score(Player* player, int category, int score) {
    switch (category) {
        case 1: (*player).table.ones = score; break;
        case 2: (*player).table.twos = score; break;
        case 3: (*player).table.threes = score; break;
        case 4: (*player).table.fours = score; break;
        case 5: (*player).table.fives = score; break;
        case 6: (*player).table.sixes = score; break;
        case 7: (*player).table.three_of_a_kind = score; break;
        case 8: (*player).table.four_of_a_kind = score; break;
        case 9: (*player).table.full_house = score; break;
        case 10:(*player).table.small_straight = score; break;
        case 11: (*player).table.large_straight = score; break;
        case 12: (*player).table.yahtzee = score; break;
        case 13: (*player).table.chance = score; break;
    }
}
// calculates total scores
int calculate_score(int dice[], int category) {
    int count[7] = {0};
    int total = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int pair = 0;
    int triple = 0;

    for (int i = 0; i < 5; i++) {
        count[dice[i]]++;
        total += dice[i];
    }

    if (category >= 1 && category <= 6) {
        return count[category] * category;
    }

    for (int i = 1; i <= 6; i++) {
        if (count[i] >= 3) {
        three = 1;
    }

    if (count[i] >= 4) {
        four = 1;
    }

    if (count[i] == 5) {
        five = 1;
    }

    if (count[i] == 2) {
        pair = 1;
    }

    if (count[i] == 3) {
        triple = 1;
    }
    }

    if (category == 7) {
        if (three == 1) {
            return total;
        }
    }
     else if (category == 8) {
        if(four == 1){ 
            return total;
        }
     }
    
    else if (category == 9) {
        if (pair == 1 && triple == 1){ return 25;
        }
    } 
    else if (category == 10) {
        if (count[1] && count[2] && count[3] && count[4]){
            return 30;
        }
        if (count[2] && count[3] && count[4] && count[5]){
            return 30;
        }
        if (count[3] && count[4] && count[5] && count[6]){
            return 30;
        }
    } 
    else if (category == 11) {
        if (count[1] && count[2] && count[3] && count[4] && count[5]){
            return 40;
        }
        if (count[2] && count[3] && count[4] && count[5] && count[6]){
             return 40;
        }
    } 
    else if (category == 12) {
        if (five == 1) return 50;
    } 
    else if (category == 13) {
        return total;
    }
    return 0;
}
// calculates number-related scores
int upper_total(Player* player) {
    int total = 0;
    for (int category = 1; category <= 6; category++) {
        if (get_score(player, category) > 0) {
            total += get_score(player, category);
        }
    }
    return total;
}
//plays one turn in the game
void play_turn(Player* player, int round) {
    int dice[5];
    int selected[5];
    int roll = 1;
    int amount;
    int die_number;
    int category;
    int score;
    char choice;

    printf("ROUND %d - %s's turn\n", round, player->name);
    printf("Press ENTER to roll the five dice...");
    getchar();

    roll_dice(dice);
    printf("Roll %d of 3\n", roll);
    show_dice(dice);

    while (roll < 3) {
        printf("Do you want to SCORE this roll? (Y/N): ");
        choice = get_user_char();
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
            printf("Please type Y or N: ");
            choice = get_user_char();
        }

        if (choice == 'Y' || choice == 'y') {
            break;
        }

        printf("How many dice do you want to reroll (1-5)? ");
        amount = get_user_int();
        while (amount < 1 || amount > 5) {
            printf("Enter a number from 1 to 5: ");
            amount = get_user_int();
        }

        for (int i = 0; i < 5; i++) {
            selected[i] = 0;
        }
        for (int i = 0; i < amount; i++) {
            printf("Enter die number %d to reroll (1-5): ", i + 1);
            die_number = get_user_int();
            while (die_number < 1 || die_number > 5 || selected[die_number - 1] == 1) {
                printf("Invalid or already chosen. Enter a different die (1-5): ");
                die_number = get_user_int();
            }
            selected[die_number - 1] = 1;
        }

        clear_screen();
        for (int i = 0; i < 5; i++) {
            if (selected[i] == 1) {
                dice[i] = roll_die();
            }
        }
        roll++;
        printf("Round %d - %s: Roll %d of 3\n", round, player->name, roll);
        show_dice(dice);
    }

    if (roll == 3) {
        printf("Three rolls used. You must choose a category.\n");
    }

    print_table();
    printf("\n%s's scoring categories:\n", player->name);
    for (int i = 1; i <= 13; i++) {
        if (get_score(player, i) == -1) {
            printf("%2d: Available  ", i);
        } 
        else {
            printf("%2d: Used (%d)  ", i, get_score(player, i));
        }
        if (i % 2 == 0) {
            printf("\n");
        }
    }
    printf("\n\nChoose a category (1-13): ");
    category = get_user_int();
    while (category < 1 || category > 13 || get_score(player, category) != -1) {
        printf("Invalid or already used. Choose an UNUSED category (1-13): ");
        category = get_user_int();
    }

    score = calculate_score(dice, category);
    set_score(player, category, score);
    player->points += score;

    printf("\n%s scored %d points in category %d.\n", player->name, score, category);
    if (score == 0) {
        printf("This category earned 0 points, and cannot be chosen again.\n");
    }
    printf("Current total: %d points\n", player->points);
    printf("Press ENTER to continue...");
    getchar();
    clear_screen();
}
//runs game
void run(void) {
    Player players[2];
    int round = 1;

    add_players(2, players);
    clear_screen();

    while (round < 14) {
        play_turn(&players[0], round);
        play_turn(&players[1], round);
        round++;
    }

    for (int i = 0; i < 2; i++) {
        if (upper_total(&players[i]) >= 63) {
            players[i].points += 35;
        }
    }

    printf("FINAL SCORES\n\n");
    for (int i = 0; i < 2; i++) {
        printf("%s: %d points (upper section: %d", players[i].name,
               players[i].points, upper_total(&players[i]));
        if (upper_total(&players[i]) >= 63) {
            printf(" + 35 bonus");
        }
        printf(")\n");
    }

    if (players[0].points > players[1].points) {
        printf("\nWinner: %s!\n", players[0].name);
    } 
    else if (players[1].points > players[0].points) {
        printf("\nWinner: %s!\n", players[1].name);
    } 
    else {
        printf("\nIt is a tie!\n");
    }

    printf("\nPress ENTER to return to the main menu...");
    getchar();
    clear_screen();
}
*/
