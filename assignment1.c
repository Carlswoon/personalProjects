// cs_flowers.
//
// This program was written by Carlson Perez (z5582492)
// on 16/03/2024.
//
// This is an interactive game in which the player is able to create their own 
// map but must attempt to kill all flowers. These flowers can attack and  
// defend. If the player fails to kill all the flowers before they are 
// eliminated they lose. However, if the player is able to kill all the flowers 
// without being eliminated they win the game.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//------------------------------------------------------------------------------
// Constants.
//------------------------------------------------------------------------------

// Logic.
//------------------------------------------------------------------------------
#define ODD 1
#define ODD_NUMBERS 2
#define TRUE 1
#define FALSE 0

// Movement.
//------------------------------------------------------------------------------
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define CUT 'c'
#define MOVE_LEFT -1
#define MOVE_RIGHT 1
#define MOVE_UP -1
#define MOVE_DOWN 1

// For flowers.
//------------------------------------------------------------------------------
#define MAX_FLOWERS 25
#define RANGE 5

// Flower turns
#define READY 2
#define BUFFER 1
#define RESET 0
#define NONE 0

// Flower ammo
#define MAX_ROW 11

// Flower root
#define SAVE_ROOT 3
#define BONUS_ROOT 6

// For map.
//------------------------------------------------------------------------------
#define MAX_ROW 11
#define MAX_COL 11
#define BOTTOM_BOUNDARY 10
#define RIGHT_BOUNDARY 10
#define UPPER_BOUNDARY 0
#define LEFT_BOUNDARY 0
#define GLOBAL_ROW 0
#define GLOBAL_COL 0

// For foiliage.
//------------------------------------------------------------------------------
#define FOLIAGE_BUSH 'u'
#define FOLIAGE_BRANCH 'b'

//------------------------------------------------------------------------------
// Struct & Enum.
//------------------------------------------------------------------------------

enum flower_state {
    DORMANT,
    DISTURBED,
    AWAKENED,
    ANXIOUS,
    ENERGETIC,
};

enum game_status {
    CONTINUE_PLAYING,
    WIN,
    END
};

struct flower {
    enum flower_state state;
    enum game_status status;
    int turn;
    int ammo;
    int waiting;
    int toxic_clouds_turn;
    int seedling_birth;
    int hiding;
    int underworld_counter;
    int underworld_counter_02;
};

enum tile_type {
    EMPTY,
    BUSH,
    BRANCH,
    DANGER,
    ROOT,
    POLLEN,
    SEEDLING,
    FLOWER,
};

enum player_tile {
    PRESENT,
    ABSENT
};

enum player_life {
    ALIVE,
    DEAD,
    NEITHER
};

enum world {
    OVERWORLD,
    UNDERWORLD
};

enum underworld_tile_type {
    U_EMPTY,
    U_DANGER,
    U_ROOT,
    U_FLOWER,
    U_BRANCH
};

enum saved_tile {
    U_SAVED_ROOT,
    SAVED_EMPTY
};

struct tile {
    enum tile_type type;
    struct flower flower;
    enum player_tile is_player_on_tile;
    enum player_life player_is;
    enum world world_type;
    enum underworld_tile_type u_type;
    enum saved_tile s_type;
};

struct position {
    int row;
    int col;
};

//------------------------------------------------------------------------------
// Game prototype functions.
//------------------------------------------------------------------------------

void begin_game(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
);
void begin_underworld(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

void transport_over(struct tile map[MAX_ROW][MAX_COL]);

void transport_under(struct tile map[MAX_ROW][MAX_COL]);

//------------------------------------------------------------------------------
// Prototype functions for player.
//------------------------------------------------------------------------------

void spawn_player(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
);

void control_cut(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
);

void control_move(
    struct tile map[MAX_ROW][MAX_COL],
    char command, 
    int *player_row, 
    int *player_col
);

void is_player_alive(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void cutting_flower (
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

void cutting_root(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

//------------------------------------------------------------------------------
// Prototype functions for foliage.
//------------------------------------------------------------------------------

void add_foliage(struct tile map[MAX_ROW][MAX_COL]);

void add_bush(
    struct tile map[MAX_ROW][MAX_COL], 
    struct position foliage
);
void add_branch(
    struct tile map[MAX_ROW][MAX_COL], 
    struct position foliage
);

void spawn_bush(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void spawn_bush_by_cases(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void spawn_bush_case_branch(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void spawn_bush_case_empty(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

//------------------------------------------------------------------------------
// Prototype functions for flowers.
//------------------------------------------------------------------------------

void add_flowers(struct tile map[MAX_ROW][MAX_COL]);

void alert_flowers(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

void alert_flowers_cases(
    struct tile map[MAX_ROW][MAX_COL],
    int alert_row,
    int alert_col,
    int row,
    int col
);

void max_flowers(struct tile map[MAX_ROW][MAX_COL]);

void flowers_turn(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

void defending_flower(
    struct tile map[MAX_ROW][MAX_COL], 
    int row,
    int col
);

void danger(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col,
    int player_row,
    int player_col
);

void root(struct tile map[MAX_ROW][MAX_COL]);

void special_buffer_case (
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

void flower_action(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col,
    int player_row,
    int player_col
);

void anxious_flower_action(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void toxic_clouds(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void spawn_seedlings(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void seedlings_action(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void energetic_transition(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

void underworld_energetic_flower(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

//------------------------------------------------------------------------------
// Prototype Functions for logic. These return TRUE or FALSE.
//------------------------------------------------------------------------------

int spawn_boundary(
    struct tile map[MAX_ROW][MAX_COL], 
    int row, 
    int column
);

int blocked(
    struct tile map[MAX_ROW][MAX_COL], 
    int row, 
    int column
);

int is_game_won(struct tile map[MAX_ROW][MAX_COL]);

int is_game_lost(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

int is_flower_attacking(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col,
    int player_row,
    int player_col
);

int is_flowers_turn(struct tile map[MAX_ROW][MAX_COL]);

int are_adjacent_tiles_full(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

int becoming_anxious(
    struct tile map[MAX_ROW][MAX_COL],
    int alert_row,
    int alert_col
);

int is_underworld(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

int within_array_boundary (
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
);

//------------------------------------------------------------------------------
// Provided Function Prototypes.
//------------------------------------------------------------------------------

void initialise_map(struct tile map[MAX_ROW][MAX_COL]);

void print_map(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
);

void print_tile(struct tile tile);

void print_flower(struct flower flower);

void initialise_underworld_map(struct tile map[MAX_ROW][MAX_COL]);

void print_underworld_map(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
);
void print_u_tile(struct tile tile);

void clear_3x3_square (
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
);

//------------------------------------------------------------------------------
// Main Function.
//------------------------------------------------------------------------------

// The game commences and the player can interact with the map.
int main(void) {
    struct tile map[MAX_ROW][MAX_COL];
    struct position player;

    initialise_map(map);

    initialise_underworld_map(map);

    printf(
        "Welcome to CS Flowers!\n"
        "Player's starting position: "
    );
    scanf(" %d %d", &player.row, &player.col);

    spawn_player(map, player.row, player.col);

    add_foliage(map);
    print_map(map, player.row, player.col);
    
    add_flowers(map);
    print_map(map, player.row, player.col);

    begin_game(map, player.row, player.col);
    
    return 0;
    
}

//------------------------------------------------------------------------------
// Game Function.
//------------------------------------------------------------------------------

// Funtion that initiates the game. It combines both player functions and 
// flower functions to make it a turn based game. The player first starts in the
// overworld then can be transported by flowers to the underworld.
void begin_game(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
) {
    printf("Game Started!\n");
    char command;
    printf("Enter command: ");
    while (scanf(" %c", &command) == TRUE) {
        // Player's turn.
        if (command == CUT ) {
            control_cut(map, player_row, player_col);
        } else {
            control_move(map, command, &player_row, &player_col);
        }

        // "flower.status = WIN" is used to let the computer know that the
        // flowers have landed a successful attack and thus the player has lost.
        if (map[player_row][player_col].type == DANGER) {
            map[player_row][player_col].flower.status = WIN;
        } else {
            map[player_row][player_col].type = EMPTY;
        }

        root(map);
        if (is_underworld(map, player_row, player_col) == TRUE) {
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter += 1;
            begin_underworld(map, player_row, player_col);
            if (is_game_lost(map, player_row, player_col) == TRUE) {
                break;
            }
        } else if (is_flowers_turn(map) == TRUE) {
            flowers_turn(map, player_row, player_col);
        }

        if (map[player_row][player_col].type == POLLEN) {
            map[player_row][player_col].flower.status = WIN;
        }
        
        if (is_game_lost(map, player_row, player_col) == TRUE) {
            if (map[player_row][player_col].type == POLLEN) {
                map[player_row][player_col].type = POLLEN;
            } else {
                map[player_row][player_col].type = ROOT;
            }
            print_map(map, player_row, player_col);
            printf("The flowers have beaten us, and UNSW is lost forever!\n");
            break;
        }
        if (is_game_won(map) == TRUE) {
            print_map(map, player_row, player_col);
            printf("All flowers are eradicated and UNSW has been saved!\n");
            break;
        }
        // This if statement is for when ctrl+d is pressed in the underworld. 
        // It prevents printing the overworld map.
        if (map[GLOBAL_ROW][GLOBAL_COL].flower.status != END) {
            print_map(map, player_row, player_col);
            printf("Enter command: ");
        }
    }  
}

// The player is transported into the underworld. This function has similar 
// pieces of code with the overworld.
void begin_underworld(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {
    int original_player_row = player_row;
    int original_player_col = player_col;

    initialise_underworld_map(map);
    transport_under(map);
    underworld_energetic_flower(map, player_row, player_col);
    print_underworld_map(map, player_row, player_col);

    char command;
    printf("Enter command: ");
    while (scanf(" %c", &command) == TRUE) {
        if (command == CUT ) {
            control_cut(map, player_row, player_col);
        } else {
            control_move(map, command, &player_row, &player_col);
        }          

        if (map[player_row][player_col].u_type == U_DANGER) {
            map[player_row][player_col].flower.status = WIN;
        } else {
            map[player_row][player_col].u_type = U_EMPTY;
        }

        root(map);
        map[player_row][player_col].u_type = U_DANGER;

        if (
            map[UPPER_BOUNDARY][LEFT_BOUNDARY].u_type != U_FLOWER && 
            map[UPPER_BOUNDARY][RIGHT_BOUNDARY].u_type != U_FLOWER &&
            map[BOTTOM_BOUNDARY][LEFT_BOUNDARY].u_type != U_FLOWER && 
            map[BOTTOM_BOUNDARY][RIGHT_BOUNDARY].u_type != U_FLOWER
        ) {
            if (
                map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter_02 == 
                SAVE_ROOT
            ) {
                map[player_row][player_col].s_type = U_SAVED_ROOT;
            }
            transport_over(map);
            map[player_row][player_col].flower.status = CONTINUE_PLAYING;
            break;
        } 
        if (is_game_lost(map, player_row, player_col) == TRUE) {
            map[player_row][player_col].u_type = U_ROOT;
            map[original_player_row][original_player_col].flower.status = WIN;
            print_underworld_map(map, player_row, player_col);
            printf("The flowers have beaten us, and UNSW is lost forever!\n");
            break;
        } 

        print_underworld_map(map, player_row, player_col);
        printf("Enter command: ");
        map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter += 1;
        map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter_02 += 1;
    }
    // This if statement is for when ctrl+d is pressed in the underworld. 
    // It prevents printing the overworld map.
    if (
        is_game_lost(map, player_row, player_col) == FALSE && 
        (map[UPPER_BOUNDARY][LEFT_BOUNDARY].u_type == U_FLOWER || 
        map[UPPER_BOUNDARY][RIGHT_BOUNDARY].u_type == U_FLOWER ||
        map[BOTTOM_BOUNDARY][LEFT_BOUNDARY].u_type == U_FLOWER || 
        map[BOTTOM_BOUNDARY][RIGHT_BOUNDARY].u_type == U_FLOWER)
    ) {
        map[GLOBAL_ROW][GLOBAL_COL].flower.status = END;
    }   
}

// Transforms the underworld into the overworld.
void transport_over(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            map[row][col].world_type = OVERWORLD;
        }
    }
    map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter = RESET;
    map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter_02 = RESET;
}

//Transforms the overworld into the underworld.
void transport_under(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            map[row][col].world_type = UNDERWORLD;
        }
    }
}


//------------------------------------------------------------------------------
// Functions for player.
//------------------------------------------------------------------------------

// Spawns the player onto the map.
void spawn_player(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
) {
    while (
        spawn_boundary(map, player_row, player_col) == TRUE
    ) {
        printf(
            "Invalid starting position!\n"
            "Re-enter starting position: "
        );
        scanf("%d %d", &player_row, &player_col);
    }
    map[player_row][player_col].type = EMPTY;
    print_map(map, player_row, player_col);
}


// If there is an obstacle nearby the player, the player will cut it and 
// remove it from the map.
void control_cut(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
) {
    char directions;
    scanf(" %c", &directions);
    if (
        directions == LEFT && player_col + MOVE_LEFT >= LEFT_BOUNDARY &&
        blocked(map, player_row, player_col + MOVE_LEFT) == TRUE  
    ) {
        player_col--;
    } else if (
        directions == DOWN && player_row + MOVE_DOWN <= BOTTOM_BOUNDARY &&
        blocked(map, player_row + MOVE_DOWN, player_col) == TRUE  
    ) {
        player_row++;

    } else if (
        directions == RIGHT && player_col + MOVE_RIGHT <= RIGHT_BOUNDARY &&
        blocked(map, player_row, player_col + MOVE_RIGHT) == TRUE
    ) {
        player_col++;
    } else if (
        directions == UP && player_row + MOVE_UP >= UPPER_BOUNDARY &&
        blocked(map, player_row + MOVE_UP, player_col) == TRUE 
    ) {
        player_row--; 
    } else {
        return;
    }
    // Considers cutting anxious and energetic flowers
    cutting_flower(map, player_row, player_col);

    // The special_buffer_case function is implemented to remove the bug of when
    // the player cuts a bush and it appears that the bush has not been cut on 
    // the map.
    special_buffer_case(map, player_row, player_col);
    
    // Cutting a root leaves a branch and exits the function so that it does not
    // become an empty tile.
    cutting_root(map, player_row, player_col);
}

// Moves the player around the map based on the user's input.
void control_move(
    struct tile map[MAX_ROW][MAX_COL],
    char command, 
    int *player_row, 
    int *player_col
) {
    // The player is considered to be absent on the current tile first so that
    // when the player moves we do not have to declare the previous tile they 
    // were on is not absent.
    map[*player_row][*player_col].is_player_on_tile = ABSENT;

    if (map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter_02 == SAVE_ROOT) {
        map[*player_row][*player_col].s_type = U_SAVED_ROOT;
        map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter_02 = RESET;
    }
    if (
        command == LEFT && *player_col + MOVE_LEFT >= LEFT_BOUNDARY &&
        blocked(map, *player_row, *player_col + MOVE_LEFT) == FALSE
    ) {
        (*player_col) --;
        if (
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter == BONUS_ROOT
        ) {
            if (
                *player_col + MOVE_LEFT >= LEFT_BOUNDARY && 
                map[*player_row][*player_col + MOVE_LEFT].u_type == U_EMPTY
            ) {
                map[*player_row][*player_col + MOVE_LEFT].u_type = U_ROOT;
            }
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter = RESET;
        }
    } else if (
        command == DOWN && *player_row + MOVE_DOWN <= BOTTOM_BOUNDARY &&
        blocked(map, *player_row + MOVE_DOWN, *player_col) == FALSE
    ) {
        (*player_row) ++;
        if (
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter == BONUS_ROOT
        ) {
            if (
                *player_row + MOVE_DOWN <= BOTTOM_BOUNDARY && 
                map[*player_row + MOVE_DOWN][*player_col].u_type == U_EMPTY
            ) {
                map[*player_row + MOVE_DOWN][*player_col].u_type = U_ROOT;
            }
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter = RESET;
        }
        
    } else if (
        command == RIGHT && *player_col + MOVE_RIGHT <= RIGHT_BOUNDARY && 
        blocked(map, *player_row, *player_col + MOVE_RIGHT) == FALSE
    ) {
        (*player_col) ++;
        if (
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter == BONUS_ROOT
        ) {
            if (
                MOVE_RIGHT <= RIGHT_BOUNDARY && 
                map[*player_row][*player_col + MOVE_RIGHT].u_type == U_EMPTY
            ) {
                map[*player_row][*player_col + MOVE_RIGHT].u_type = U_ROOT;
            }
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter = RESET;
        }
    } else if (
        command == UP && *player_row + MOVE_UP >= UPPER_BOUNDARY &&
        blocked(map, *player_row + MOVE_UP, *player_col) == FALSE
    ) {
        (*player_row) --;
        if (
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter == BONUS_ROOT
        ) {
            if (
                *player_row + MOVE_UP >= UPPER_BOUNDARY && 
                map[*player_row + MOVE_UP][*player_col].u_type == U_EMPTY
            ) {
                map[*player_row + MOVE_UP][*player_col].u_type = U_ROOT;
            }
            map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter = RESET;
        }
    }
    map[*player_row][*player_col].is_player_on_tile = PRESENT;

    if (map[*player_row][*player_col].type == BRANCH) {
        alert_flowers(map, *player_row, *player_col);
    }
}

// Verifies if the player is alive. When the player is dead, the player loses.
void is_player_alive(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (map[row][col].player_is != DEAD) {
        map[row][col].player_is = ALIVE;
    } else {
        map[row][col].flower.status = WIN;
    }
}

// For cutting a flower.
void cutting_flower (
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {
    if (map[player_row][player_col].type == FLOWER) {
        if (map[player_row][player_col].flower.state == ENERGETIC) {
            if (player_col + MOVE_RIGHT <= RIGHT_BOUNDARY) {
                map[player_row][player_col + MOVE_RIGHT].
                world_type = UNDERWORLD;
            }
            if (player_row + MOVE_DOWN <= BOTTOM_BOUNDARY) {
                map[player_row + MOVE_DOWN][player_col].world_type = UNDERWORLD;
            }
            if (player_col + MOVE_LEFT >= LEFT_BOUNDARY) {
                map[player_row][player_col + MOVE_LEFT].world_type = UNDERWORLD;
            }
            if (player_row + MOVE_UP >= UPPER_BOUNDARY) {
                map[player_row + MOVE_UP][player_col].world_type = UNDERWORLD;
            }
            map[player_row][player_col].type = EMPTY;
            return;
        }
        alert_flowers(map, player_row, player_col);
        if (map[player_row][player_col].flower.state == ANXIOUS) {
            clear_3x3_square(map, player_row, player_col);
            map[player_row][player_col].flower.toxic_clouds_turn = RESET;
        }
        map[player_row][player_col].flower.state = DORMANT;
        map[player_row][player_col].flower.ammo = NONE;
    } 
}

// For cutting a root.
void cutting_root(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {
    if (is_underworld(map, player_row, player_col) == TRUE) {
        if (
            map[player_row][player_col].u_type == U_ROOT || 
            map[player_row][player_col].s_type == U_SAVED_ROOT
        ) {
            map[player_row][player_col].u_type = U_BRANCH;
            return;
        }
        map[player_row][player_col].u_type = U_EMPTY;
    } else {
        if (map[player_row][player_col].type == ROOT) {
            map[player_row][player_col].type = BRANCH;
            return;
        }
        map[player_row][player_col].type = EMPTY; 
    }
}

//------------------------------------------------------------------------------
// Functions for foliage.
//------------------------------------------------------------------------------

// Adds foliage onto the map.
void add_foliage(struct tile map[MAX_ROW][MAX_COL]) {
    struct position foliage;
    char foliage_type;
    int counter;

    printf("How many tiles of foliage: ");
    scanf(" %d", &counter);
    
    for (int i = 0; i < counter; i++) {
        scanf(" %c %d %d", &foliage_type, &foliage.row, &foliage.col);
        if (foliage_type == FOLIAGE_BUSH) {
            add_bush (map, foliage);
        } else if (foliage_type == FOLIAGE_BRANCH) {
            add_branch (map, foliage);
        }
    }
}

// Adds bush(es) to the map.
void add_bush(
    struct tile map[MAX_ROW][MAX_COL], 
    struct position foliage
) {
    char direction;
    int replicate;
    scanf(" %c %d", &direction, &replicate);
    if (spawn_boundary(map, foliage.row, foliage.col) == TRUE) {
        printf("Bush added!\n");
        for (int i = 0; i < replicate; i++) {
            if (direction == 'v') {
                map[foliage.row + i][foliage.col].type = BUSH;
            } else if (direction == 'h') {
                map[foliage.row][foliage.col + i].type = BUSH;
            } 
        }
    } else {
        printf("Invalid foliage position!\n");
    }  
}

// Adds branch(es) to the map.
void add_branch(
    struct tile map[MAX_ROW][MAX_COL], 
    struct position foliage
) {
    if (spawn_boundary(map, foliage.row, foliage.col) == TRUE) {
        printf("Branch added!\n");
        map[foliage.row][foliage.col].type = BRANCH;
    } else {
        printf("Invalid foliage position!\n");
    } 
}

// Flowers will spawn bushes when they are not in a DORMANT state.
void spawn_bush(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (
        map[row][col].type == FLOWER &&
        map[row][col].flower.state != DORMANT &&
        map[row][col].flower.turn >= READY
    ) {
        spawn_bush_by_cases(map, row, col);
    } else if (map[row][col].flower.state == DORMANT) {
        map[row][col].flower.turn = RESET;
    }
}

// This function determines how the flower should spawn their bush by 
// considering exhaustive cases.
void spawn_bush_by_cases(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (
        map[row + MOVE_DOWN][col].type == BRANCH 
    ) {
        spawn_bush_case_branch(map, row, col);
    } else if (
        map[row + MOVE_DOWN][col].type == EMPTY &&
        map[row + MOVE_DOWN][col].is_player_on_tile == ABSENT
    ) {
        spawn_bush_case_empty(map, row, col);
    } else if (
         map[row][col + MOVE_RIGHT].type == BRANCH 
    ) {
        spawn_bush_case_branch(map, row, col);
    } else if (
        map[row][col + MOVE_RIGHT].type == EMPTY &&
        map[row][col + MOVE_RIGHT].is_player_on_tile == ABSENT
    ) {
        spawn_bush_case_empty(map, row, col);
    } else if (
         map[row + MOVE_UP][col].type == BRANCH
    ) {
        spawn_bush_case_branch(map, row, col);
    } else if (
        map[row + MOVE_UP][col].type == EMPTY &&
        map[row + MOVE_UP][col].is_player_on_tile == ABSENT
    ) {
        spawn_bush_case_empty(map, row, col);
    } else if (
       map[row][col + MOVE_LEFT].type == BRANCH
    ) {
        spawn_bush_case_branch(map, row, col);
    } else {
        spawn_bush_case_empty(map, row, col);
    }
}

// This case considers when a branch has been replaced by a bush such that
// the flower will spawn another bush until it cannot and will rest for 1 turn.
void spawn_bush_case_branch(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    map[row + MOVE_DOWN][col].type = BUSH;
    map[row][col].flower.turn = RESET;
    if (
        map[row][col + MOVE_RIGHT].type == BRANCH ||
        map[row][col + MOVE_RIGHT].type == BUSH
    ) {
        map[row][col + MOVE_RIGHT].type = BUSH;
        if (
            map[row + MOVE_UP][col].type == BRANCH ||
            map[row + MOVE_UP][col].type == BUSH
        ) {
            map[row + MOVE_UP][col].type = BUSH;
            if (
                map[row][col + MOVE_LEFT].type == BRANCH ||
                map[row][col + MOVE_LEFT].type == BUSH
            ) {
                map[row][col + MOVE_LEFT].type = BUSH;
            }
            map[row][col + MOVE_LEFT].type = BUSH;
        }
        map[row + MOVE_UP][col].type = BUSH;
    }
    map[row][col + MOVE_RIGHT].type = BUSH;
}

// This case considers when an empty square has been replaced by a bush such 
// that the flower will rest for 1 turn.
void spawn_bush_case_empty(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (
        map[row + MOVE_DOWN][col].is_player_on_tile == ABSENT &&
        map[row + MOVE_DOWN][col].type == EMPTY
    ) {
        map[row + MOVE_DOWN][col].type = BUSH;
        map[row][col].flower.turn = RESET;
    } else if (
        map[row][col + MOVE_RIGHT].is_player_on_tile == ABSENT &&
        map[row][col + MOVE_RIGHT].type == EMPTY 
    ) {
        map[row][col + MOVE_RIGHT].type = BUSH;
        map[row][col].flower.turn = RESET;
    } else if (
        map[row + MOVE_UP][col].is_player_on_tile == ABSENT &&
        map[row + MOVE_UP][col].type == EMPTY 
    ) {
        map[row + MOVE_UP][col].type = BUSH;
        map[row][col].flower.turn = RESET;
    } else if (
        map[row][col + MOVE_LEFT].is_player_on_tile == ABSENT &&
        map[row][col + MOVE_LEFT].type == EMPTY 
    ) {
        map[row][col + MOVE_LEFT].type = BUSH;
        map[row][col].flower.turn = RESET;
    } else {
        map[row][col].flower.turn += BUFFER;
    } 
}

//------------------------------------------------------------------------------
// Functions for flowers
//------------------------------------------------------------------------------

// Adds flower(s) to the map with odd coordinates.
void add_flowers(struct tile map[MAX_ROW][MAX_COL]) {
    struct position flower;
    int counter;

    printf("How many flowers: ");
    scanf(" %d", &counter);
    if (counter < MAX_FLOWERS) {
        for (int i = 0; i < counter; i++) {
            scanf(" %d %d", &flower.row, &flower.col);
            if (
                spawn_boundary(map, flower.row, flower.col) == TRUE &&
                flower.row % 2 == ODD && flower.col % 2 == ODD && 
                map[flower.row][flower.col].type == EMPTY
            ) {
                map[flower.row][flower.col].type = FLOWER;
            } else {
                printf("Invalid flower position!\n");
            }
        }
    } else if (counter >= MAX_FLOWERS) {
        max_flowers(map);
    }
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            map[row][col].flower.turn = BUFFER;
        }
    }
}

// Flowers transition into a DISTURBED state when they are effected.
// The alert trigger's range is a 5 x 5 square originating from the centre
// of the trigger cause.
void alert_flowers(
    struct tile map[MAX_ROW][MAX_COL],
    int alert_row,
    int alert_col
) {
    int max_row = RANGE;
    int max_col = RANGE;
    for (int row = UPPER_BOUNDARY; row < max_row; row++) {
        for (int col = LEFT_BOUNDARY; col < max_col; col++) {
            alert_flowers_cases(map, alert_row, alert_col, row, col);
        }
    }
    
}

// This function considers the state of the flower that is alerted.
void alert_flowers_cases(
    struct tile map[MAX_ROW][MAX_COL],
    int alert_row,
    int alert_col,
    int row,
    int col
) {
    // RANGE / 2 means 2. i.e a radius of 2 rows/cols.
    int i = alert_row - (RANGE / 2) + row;
    int j = alert_col - (RANGE / 2) + col; 
    
    if (within_array_boundary(map, i, j) == TRUE) {
        if (
            map[i][j].type == FLOWER && 
            map[i][j].flower.state == DORMANT
        ) {
            map[i][j].flower.state = DISTURBED;
            map[i][j].flower.ammo += 1;
        } else if (
            map[i][j].type == FLOWER && 
            map[i][j].flower.state == DISTURBED
        ) {
            map[i][j].flower.state = AWAKENED;
            map[i][j].flower.ammo += 2;
            if (are_adjacent_tiles_full(map, i, j) == TRUE) {
                map[i][j].flower.hiding += 1;
            }
        } else if (
            map[i][j].type == FLOWER && 
            map[i][j].flower.state == AWAKENED  
        ) {
            map[i][j].flower.ammo += 2;
        }
    }
}

// When the user wants to print 25 or more flowers.
void max_flowers(struct tile map[MAX_ROW][MAX_COL]) {
    for (int i = ODD; i < MAX_COL; i += ODD_NUMBERS) {
        for (int j = ODD; j < MAX_ROW; j += ODD_NUMBERS) {
            if (map[i][j].type == EMPTY) {
                map[i][j].type = FLOWER;
            }
        }
    }
}

// The flowers will perform an action: attack or defend.
void flowers_turn(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {

    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            flower_action(map, row, col, player_row, player_col);
        }
    }
}

// The flower will enter defense mode and will start to spawn bushes.
void defending_flower(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    spawn_bush(map, row, col);
    map[row][col].flower.turn++;
}

// The flower will create danger tiles.
void danger(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col,
    int player_row,
    int player_col
) {
    if (map[player_row][player_col].type == EMPTY ) {
        map[player_row][player_col].type = DANGER;
        map[row][col].flower.ammo--; 
    }
}

// The flower changes the danger tiles into root tiles.
void root(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            if (map[row][col].type == DANGER) {
                map[row][col].type = ROOT;
            } else if (map[row][col].u_type == U_DANGER) {
                map[row][col].u_type = U_ROOT;
            }
        }
    }
}

// This function removes the bug of when the player cuts a bush but it appears
// on the map that the player has performed no actions since the flower spawned 
// a bush during that time. 
void special_buffer_case (
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {
    if (
        map[player_row][player_col].type == BUSH || 
        map[player_row][player_col].type == ROOT 
    ) {

        if (player_col + MOVE_RIGHT <= RIGHT_BOUNDARY && 
            map[player_row][player_col + MOVE_RIGHT].type == FLOWER 
        ) {
            player_col = player_col + MOVE_RIGHT;
            if (are_adjacent_tiles_full(map, player_row, player_col) == TRUE) {
                map[player_row][player_col].flower.turn = BUFFER;
            }
        } else if (
            player_row + MOVE_DOWN <= BOTTOM_BOUNDARY && 
            map[player_row + MOVE_DOWN][player_col].type == FLOWER 
        ) {
            player_row = player_row + MOVE_DOWN;
            if (are_adjacent_tiles_full(map, player_row, player_col) == TRUE) {
                map[player_row][player_col].flower.turn = BUFFER;
            }
        } else if (
            player_row + MOVE_UP >= UPPER_BOUNDARY && 
            map[player_row + MOVE_UP][player_col].type == FLOWER 
        ) {
            player_row = player_row + MOVE_UP;
            if (are_adjacent_tiles_full(map, player_row, player_col) == TRUE) {
                map[player_row][player_col].flower.turn = BUFFER;
            }
        } else if (
            player_col + MOVE_LEFT >= LEFT_BOUNDARY && 
            map[player_row][player_col + MOVE_LEFT].type == FLOWER 
        ) {
            player_col = player_col + MOVE_LEFT;
            if (are_adjacent_tiles_full(map, player_row, player_col) == TRUE) {
                map[player_row][player_col].flower.turn = BUFFER;
            }
        }
    }
}

// The flower will attack the player or spawn a bush.
void flower_action(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col,
    int player_row,
    int player_col
) {
    
    if (map[row][col].type == FLOWER) {
        
        if (map[row][col].flower.state == ANXIOUS) {
            anxious_flower_action(map, row, col);
        } else if (
            is_flower_attacking(map, row, col, player_row, player_col) == TRUE
        ) {
            danger(map, row, col, player_row, player_col);
        } else {
            defending_flower(map, row, col);
        }
        if (map[row][col].flower.state == AWAKENED) {
            if (becoming_anxious(map, row, col) == TRUE) {
                map[row][col].flower.state = ANXIOUS;
                anxious_flower_action(map, row, col);
            }
        }
        energetic_transition(map, row, col);
    }
}

// Actions that can only be made by anxious flowers.
void anxious_flower_action(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (map[row][col].flower.toxic_clouds_turn == RESET) {
        spawn_seedlings(map, row, col);
    }
    toxic_clouds(map, row, col);
    
}

// Toxic clouds will spawn around the anxious flower and will start to rotate 
// based on how long the flower has been anxious for. 
void toxic_clouds(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (map[row][col].flower.toxic_clouds_turn == RESET) {
        map[row + MOVE_UP][col + MOVE_RIGHT].type = POLLEN;
        map[row][col + MOVE_RIGHT].type = POLLEN;
        map[row + MOVE_DOWN][col + MOVE_RIGHT].type = POLLEN;
        map[row + MOVE_DOWN][col].type = POLLEN;
        map[row + MOVE_DOWN][col + MOVE_LEFT].type = POLLEN;
        map[row][col + MOVE_LEFT].type = POLLEN;
        map[row + MOVE_UP][col + MOVE_LEFT].type = EMPTY;
        map[row + MOVE_UP][col].type = EMPTY;
    } else if (map[row][col].flower.toxic_clouds_turn == 1) {
        map[row + MOVE_UP][col + MOVE_RIGHT].type = EMPTY;
        map[row + MOVE_UP][col + MOVE_LEFT].type = POLLEN;
    } else if (map[row][col].flower.toxic_clouds_turn == 2) {
        map[row][col + MOVE_RIGHT].type = EMPTY;
        map[row + MOVE_UP][col].type = POLLEN;
    } else if (map[row][col].flower.toxic_clouds_turn == 3) {
        map[row + MOVE_DOWN][col + MOVE_RIGHT].type = EMPTY;
        map[row + MOVE_UP][col + MOVE_RIGHT].type = POLLEN;
    } else if (map[row][col].flower.toxic_clouds_turn == 4) {
        map[row + MOVE_DOWN][col].type = EMPTY;
        map[row][col + MOVE_RIGHT].type = POLLEN;
    } else if (map[row][col].flower.toxic_clouds_turn == 5) {
        map[row + MOVE_DOWN][col + MOVE_LEFT].type = EMPTY;
        map[row + MOVE_DOWN][col + MOVE_RIGHT].type = POLLEN;
    } else if (map[row][col].flower.toxic_clouds_turn == 6) {
        map[row][col + MOVE_LEFT].type = EMPTY;
        map[row + MOVE_DOWN][col].type = POLLEN;
    } else if (map[row][col].flower.toxic_clouds_turn == 7) {
        map[row + MOVE_UP][col + MOVE_LEFT].type = EMPTY;
        map[row + MOVE_DOWN][col + MOVE_LEFT].type = POLLEN;
    } else if (map[row][col].flower.toxic_clouds_turn == 8) {
        map[row][col].flower.state = AWAKENED;
        map[row][col].flower.ammo += 2;
        clear_3x3_square(map, row, col);
        seedlings_action(map, row, col);
        map[row][col].flower.toxic_clouds_turn = -1;
        map[row][col].flower.turn = READY;
    }
    map[row][col].flower.toxic_clouds_turn += 1;
}

// This will spawn seedlings on orthogonal adjacent tiles that have radius 2.
void spawn_seedlings(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    // Arrays are used to avoid excessive if statements.
    int seeds_row[8] = {
        row + (2 * MOVE_UP), row + (2 * MOVE_UP), row + (2 * MOVE_UP), 
        row, row, row + (2 * MOVE_DOWN), row + (2 * MOVE_DOWN), 
        row + (2 * MOVE_DOWN)
    };
    int seeds_col[8] = {
        col + (2 * MOVE_LEFT), col, col + (2 * MOVE_RIGHT), 
        col + (2 * MOVE_LEFT), col + (2 * MOVE_RIGHT), 
        col + (2 * MOVE_LEFT), col, col + (2 * MOVE_RIGHT)
    };
    
    for (int i = 0; i < 8; i++) {
        int seed_row = seeds_row[i];
        int seed_col = seeds_col[i];
        if (within_array_boundary(map, seed_row, seed_col) == TRUE) {
            if (map[seed_row][seed_col].is_player_on_tile == ABSENT) {
                map[seed_row][seed_col].type = SEEDLING;  
            }
            
        }
    }

}

// The seedlings will awaken into dormant flowers.
void seedlings_action(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    // Arrays are used to avoid excessive if statements.
    int seeds_row[8] = {
        row + (2 * MOVE_UP), row + (2 * MOVE_UP), 
        row + (2 * MOVE_UP), row, row, row + (2 * MOVE_DOWN), 
        row + (2 * MOVE_DOWN), row + (2 * MOVE_DOWN)
    };
    int seeds_col[8] = {
        col + (2 * MOVE_LEFT), col, col + (2 * MOVE_RIGHT), 
        col + (2 * MOVE_LEFT), col + (2 * MOVE_RIGHT), 
        col + (2 * MOVE_LEFT), col, col + (2 * MOVE_RIGHT)
    };
    
    for (int i = 0; i < 8; i++) {
        int seed_row = seeds_row[i];
        int seed_col = seeds_col[i];
        if (within_array_boundary(map, seed_row, seed_col) == TRUE) {
            if (map[seed_row][seed_col].is_player_on_tile == ABSENT) {
                map[seed_row][seed_col].type = FLOWER;  
            }
            
        }
    }
}

// The flower will transition to become an energetic flower.
void energetic_transition (
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (becoming_anxious(map, row, col) == FALSE) {
        if (
            map[row][col].flower.state == AWAKENED &&
            are_adjacent_tiles_full(map, row, col) == TRUE
        ) {
            if (map[row][col].flower.hiding > READY) {
                map[row][col].flower.state = ENERGETIC;
                map[row][col].flower.turn = RESET;
                map[row][col].flower.ammo = NONE;
            } else {
                map[row][col].flower.hiding += 1;
            }
        } else if (map[row][col].flower.state == ENERGETIC) {
            map[row][col].flower.turn = RESET;
            map[row][col].flower.ammo = NONE;
        }
    }
}

// This calculates which corner the energetic flower should spawn in so that
// it is the furthest away from the player.
void underworld_energetic_flower(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {
    double a = sqrt(
        (player_row * player_row) + (player_col * player_col)
        );
    double b = sqrt(
        (player_row * player_row) + ((10 - player_col) * (10 - player_col))
        );
    double c = sqrt(
        ((10 - player_row) * (10 - player_row)) + (player_col * player_col)
        );
    double d = sqrt(
        ((10 - player_row) * (10 - player_row)) + 
        ((10 - player_col) * (10 - player_col))
        );
    
    if (a >= b && a >= c && a >= d) {
        map[UPPER_BOUNDARY][LEFT_BOUNDARY].u_type = U_FLOWER;
        map[UPPER_BOUNDARY][LEFT_BOUNDARY].flower.state = ENERGETIC;
    } else if (b >= a && b >= c && b >= d) {
        map[UPPER_BOUNDARY][RIGHT_BOUNDARY].u_type = U_FLOWER;
        map[UPPER_BOUNDARY][RIGHT_BOUNDARY].flower.state = ENERGETIC;
    } else if (c >= a && c >= b && c >= d) {
        map[BOTTOM_BOUNDARY][LEFT_BOUNDARY].u_type = U_FLOWER;
        map[BOTTOM_BOUNDARY][LEFT_BOUNDARY].flower.state = ENERGETIC;
    } else {
        map[BOTTOM_BOUNDARY][RIGHT_BOUNDARY].u_type = U_FLOWER;
        map[BOTTOM_BOUNDARY][RIGHT_BOUNDARY].flower.state = ENERGETIC;
    }
}

//------------------------------------------------------------------------------
// Functions for logic. These return TRUE or FALSE.
//------------------------------------------------------------------------------

// Checks whether or not the item to be spawned fulfils the spawning criteria.
// Returns FALSE if on the border.
// Returns TRUE if not on the border.
int spawn_boundary(
    struct tile map[MAX_ROW][MAX_COL], 
    int row, 
    int column
) {
    if (
        row > UPPER_BOUNDARY && column > LEFT_BOUNDARY
        && row < BOTTOM_BOUNDARY && column <  RIGHT_BOUNDARY
    ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Checks whether or not the player can move in the input direction.
// returns TRUE when there is something blocking the player.
// returns FALSE when there is nothing blocking the player.
int blocked(
    struct tile map[MAX_ROW][MAX_COL], 
    int row, 
    int column
) {
    if (map[row][column].world_type == OVERWORLD) {
        if (
            map[row][column].type == FLOWER || 
            map[row][column].type == BUSH ||
            map[row][column].type == ROOT ||
            map[row][column].type == SEEDLING 
        ) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        if (
        map[row][column].u_type == U_FLOWER || 
        map[row][column].u_type == U_ROOT ||
        map[row][column].s_type == U_SAVED_ROOT
        ) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

// Verifies if there exists flowers on the map.
// Returns FALSE when there is a flower(s).
// Returns TRUE when there are no more flowers.
int is_game_won(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            if (
                map[row][col].type == FLOWER || 
                map[row][col].u_type == U_FLOWER
            ) {
                return FALSE;
            } 
        }
    }
    return TRUE;
}

// Verifies if the player is eliminated.
// Returns TRUE when the player is eliminated.
// Returns FALSE when the player has not been eliminated yet.
int is_game_lost (
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {
    if (map[player_row][player_col].flower.status == WIN) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Verifies if there exists a flower on the map that is not in DORMANT state.
// Returns TRUE if there is.
// Returns FALSE if there is not.
int is_flowers_turn(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            if (
                map[row][col].type == FLOWER &&
                map[row][col].flower.state != DORMANT
            ) {
                return TRUE;
            } 
        }
    }
    return FALSE;
}

// Ensures that only one flower will attack the tile the player is on.
int is_flower_attacking(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col,
    int player_row,
    int player_col
) {
    if (
        map[row][col].flower.ammo > NONE 
    ) {
        if (row + MOVE_UP == player_row && col == player_col) {
            return TRUE;
        } else if (row + MOVE_DOWN == player_row && col == player_col) {
            return TRUE;
        } else if (col + MOVE_LEFT == player_col && row == player_row) {
            return TRUE;
        } else if (col + MOVE_RIGHT == player_col && row == player_row) {
            return TRUE;
        } else if (
            row + MOVE_UP == player_row && col + MOVE_LEFT == player_col
        ) {
            return TRUE;
        } else if (
            row + MOVE_DOWN == player_row && col + MOVE_RIGHT == player_col
        ) {
            return TRUE;
        } else if (
            col + MOVE_RIGHT == player_col && row + MOVE_UP == player_row
        ) {
            return TRUE;
        } else if (
            col + MOVE_LEFT == player_col && row + MOVE_DOWN == player_row
        ) {
            return TRUE;
        }
    } 
    return FALSE;
}

// Verifies whether or not a flower's adjacent tiles (+) are full with bushes. 
// Returns TRUE when the adjacent tiles are full.
// Returns FALSE when the adjeacnet tiles are not full. 
int are_adjacent_tiles_full(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (
        (map[row][col + MOVE_RIGHT].type == BUSH || 
        map[row][col + MOVE_RIGHT].type == ROOT) &&
        (map[row][col + MOVE_LEFT].type == BUSH ||
        map[row][col + MOVE_LEFT].type == ROOT) &&
        (map[row + MOVE_DOWN][col].type == BUSH ||
        map[row + MOVE_DOWN][col].type == ROOT) && 
        (map[row + MOVE_UP][col].type == BUSH || 
        map[row + MOVE_UP][col].type == ROOT)
    ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Verifies if the flower meets the criteria to become anxious.
// Returns TRUE if it does meet the criteria.
// Returns FALSE if it does not.
int becoming_anxious(
    struct tile map[MAX_ROW][MAX_COL],
    int alert_row,
    int alert_col
) {
    
    for (int row = UPPER_BOUNDARY; row < RANGE; row++) {
        for (int col = LEFT_BOUNDARY; col < RANGE; col++) {
            int i = alert_row - (RANGE / 2) + row;
            int j = alert_col - (RANGE / 2) + col;
            if (
                within_array_boundary(map, i, j) == TRUE &&
                (i != alert_row || j != alert_col) && 
                map[i][j].type == FLOWER
            ) { 
                return FALSE; 
            }
        }
    }
    return TRUE;
}

// Determines whether or not the player is in the underworld.
// Returns TRUE if the player is in the underworld.
// Retruns FALSE if the player is in the overworld.
int is_underworld(
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (map[row][col].world_type == UNDERWORLD) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// This function ensures that the array index is within the boundary.
// Returns TRUE if the index is within boundary.
// Returns FALSE if the index is not within boundary.
int within_array_boundary (
    struct tile map[MAX_ROW][MAX_COL],
    int row,
    int col
) {
    if (row >= UPPER_BOUNDARY && row < MAX_ROW ) {
        if (col >= LEFT_BOUNDARY && col < MAX_COL) {
            return TRUE;
        }
    }
    return FALSE;
}
//------------------------------------------------------------------------------
// Provided Functions
//------------------------------------------------------------------------------

// This function initialises the overworld map.
void initialise_map(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            map[row][col].type = EMPTY;
            map[row][col].flower.state = DORMANT;
            map[row][col].flower.ammo = NONE;
            map[row][col].player_is = NEITHER;
            map[row][col].flower.status = CONTINUE_PLAYING;
            map[row][col].world_type = OVERWORLD;
            map[row][col].u_type = U_EMPTY;
            map[row][col].s_type = SAVED_EMPTY;
            map[row][col].flower.toxic_clouds_turn = RESET;
            map[row][col].flower.seedling_birth = RESET;
            map[row][col].flower.hiding = RESET;
        }
    }
    map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter = RESET;
    map[GLOBAL_ROW][GLOBAL_COL].flower.underworld_counter_02 = RESET;
}

// This function prints the overworld map.
void print_map(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
) {
    for (int i = UPPER_BOUNDARY; i < MAX_ROW; i++) {
        for (int j = LEFT_BOUNDARY; j < MAX_COL; j++) {
            map[i][j].is_player_on_tile = ABSENT;
        }
    }

    for (int i = UPPER_BOUNDARY; i < MAX_ROW; i++) {
        for (int j = LEFT_BOUNDARY; j < MAX_COL; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = LEFT_BOUNDARY; j < MAX_COL; j++) {
            printf("|");
            if (player_row != i || player_col != j) {
                print_tile(map[i][j]);
            } else if (map[i][j].type == EMPTY) {
                printf(" P ");
                map[i][j].is_player_on_tile = PRESENT;
                is_player_alive(map, i, j);
            } else if (map[i][j].type == DANGER) {
                printf("<P>");
            } else if (map[i][j].type == ROOT) {
                printf("<^>");
            } else if (map[i][j].type == POLLEN) {
                printf(":::");
            }
        }
        printf("|\n");
    }
    for (int j = LEFT_BOUNDARY; j < MAX_COL; j++) {
        printf("+---");
    }
    printf("+\n");
}

// This function prints tiles in the overworld.
void print_tile(struct tile tile) {
    if (tile.type == EMPTY) {
        printf("   ");
    } else if (tile.type == BUSH) {
        printf("###");
    } else if (tile.type == BRANCH) {
        printf("_/-");
    } else if (tile.type == DANGER) {
        printf("< >");
    } else if (tile.type == ROOT) {
        printf("<^>");
    } else if (tile.type == POLLEN) {
        printf(":::");
    } else if (tile.type == SEEDLING) {
        printf(".w.");
    } else if (tile.type == FLOWER) {
        print_flower(tile.flower);
    }
}

// This functions prints flowers based on its state.
void print_flower(struct flower flower) {
    if (flower.state == DORMANT) {
        printf("uwu");
    } else if (flower.state == DISTURBED) {
        printf("uwo");
    } else if (flower.state == AWAKENED) {
        printf("owo");
    } else if (flower.state == ANXIOUS) {
        printf("o~o");
    } else if (flower.state == ENERGETIC) {
        printf("*w*");
    }
}

// This function is used so that the underworld tiles will not override the 
// overworld tiles.
void initialise_underworld_map(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = UPPER_BOUNDARY; row < MAX_ROW; row++) {
        for (int col = LEFT_BOUNDARY; col < MAX_COL; col++) {
            if (map[row][col].s_type == U_SAVED_ROOT) {
                map[row][col].s_type = U_SAVED_ROOT;
            } else {
                map[row][col].u_type = U_EMPTY;
            }
        }
    }
}

// This function is used so that the underworld tiles will not override the 
// overworld tiles.
void print_underworld_map(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
) {
    for (int i = UPPER_BOUNDARY; i < MAX_ROW; i++) {
        for (int j = LEFT_BOUNDARY; j < MAX_COL; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = LEFT_BOUNDARY; j < MAX_COL;j++) {
            printf("|");
            if (player_row != i || player_col != j) {
                print_u_tile(map[i][j]);
            } else if (map[i][j].u_type == U_EMPTY) {
                printf(" P ");
                is_player_alive(map, i, j);
            } else if (map[i][j].u_type == U_DANGER) {
                printf("<P>");
            } else if (
                map[i][j].u_type == U_ROOT || 
                map[i][j].s_type == U_SAVED_ROOT
            ) {
                printf("<^>");
            } 
        }
        printf("|\n");
    }

    for (int j = LEFT_BOUNDARY; j < MAX_COL; j++) {
        printf("+---");
    }
    printf("+\n");
}

// This function is used so that the underworld tiles will not override the 
// overworld tiles.
void print_u_tile(struct tile tile) {
    if (tile.u_type == U_EMPTY) {
        printf("   ");
    } else if (tile.u_type == U_ROOT || tile.s_type == U_SAVED_ROOT) {
        printf("<^>");
    } else if (tile.u_type == U_DANGER) {
        printf("< >");
    } else if (tile.u_type == U_FLOWER) {
        print_flower(tile.flower);
    } else if (tile.u_type == U_BRANCH) {
        printf("_/-");
    }
}

// For clearing a 3x3 square excluding the centre of the square.
void clear_3x3_square (
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col
) {
    map[player_row + MOVE_UP][player_col + MOVE_RIGHT].type = EMPTY;
    map[player_row][player_col + MOVE_RIGHT].type = EMPTY;
    map[player_row + MOVE_DOWN][player_col + MOVE_RIGHT].type = EMPTY;
    map[player_row + MOVE_DOWN][player_col].type = EMPTY;
    map[player_row + MOVE_DOWN][player_col + MOVE_LEFT].type = EMPTY;
    map[player_row][player_col + MOVE_LEFT].type = EMPTY;
    map[player_row + MOVE_UP][player_col + MOVE_LEFT].type = EMPTY;
    map[player_row + MOVE_UP][player_col].type = EMPTY;
}


