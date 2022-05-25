#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <C:\Users\mateo\Documents\Coding Projects\Languages\C\tictactoe\tictactoe.h>
#include <C:\Users\mateo\Documents\Coding Projects\Languages\C\tictactoe\tictactoe.test.c>

/**
 * @brief Entrypoint to the program
 */
int main(int argc, const char * argv[]) {
    test_winner_function();
    tictactoe(&grid);
    return 0;
}

/**
 * @brief build a grid from a string, helpful for testing.
 * 
 * @param string an input string
 * @param return_code allows users to check for errors: good (0), wrong string length (1), bad char (2).
 * @return struct Grid a grid containing the values provided in the string.
 */
struct Grid grid_from_string(const char * string, int * return_code) {
    if (strlen(string) != 9) {
        *return_code = 1;
        return (struct Grid) { .content = {{BLANK_SPACE, BLANK_SPACE, BLANK_SPACE}, {BLANK_SPACE, BLANK_SPACE, BLANK_SPACE}, {BLANK_SPACE, BLANK_SPACE, BLANK_SPACE}} };
    }

    static struct Grid result;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char temp = string[i * 3 + j];
            if (is_player(temp) || temp == BLANK_SPACE) {
                result.content[i][j] = temp;
            } else {
                *return_code = 2;
                return (struct Grid) EMPTY_GRID;
            }
        }
    }

    *return_code = 0;
    return result;
}

struct Grid grid_from_string0(const char * string) {
    int _return_code;
    return grid_from_string(string, &_return_code);
}

/**
 * @brief Whether or not a number fits within a range.
 * 
 * @param minIncl the minimum value to the range, inclusive
 * @param maxIncl the maximum value to the range, inclusive
 * @param val the number in question
 * @return true if the number falls within the range
 * @return false otherwise
 */
bool fits_range(int minIncl, int maxIncl, int val) {
    return val >= minIncl && val <= maxIncl;
}

void init_grid(struct Grid * g) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            g->content[i][j] = BLANK_SPACE;
        }
    }
}

/**
 * @brief symbol == PLAYER_X || symbol == PLAYER_O
 */
bool is_player(char symbol) {
    return symbol == PLAYER_X || symbol == PLAYER_O;
}

int set_grid_at(struct Grid * g, int x, int y, char symbol) {
    if (fits_range(0, 2, x) && fits_range(0, 2, y) && is_player(symbol)) {
        g->content[x][y] = symbol;
        return 1;
    }
    return 0;
}

void print_grid(struct Grid * g) {
    printf("%s\n", LINE_SEP);
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%c ", g->content[i][j]);
        }
        printf("|\n");
    }
    printf("%s\n", LINE_SEP);
}

char get_current_player() {
    return __turn_count % 2 == 0 ? PLAYER_X : PLAYER_O;
}

/**
 * @brief Use scanf to read user input
 * 
 * @param destination to where the input is copied
 * @return int code whether or not the operation was successful (0), 
 * or ran into a problem: out of bounds reading column (1), 
 * out of bounds reading row (2),
 * selection is already full (3)
 * @todo CURRENTLY BREAKS ON NON-NUMERIC INPUT!!! Make sure to fix it. (think sscanf_s + aoti)
 */
int read_player_input0(struct Grid * g, int destination[2]) {
    int x, y;
    printf("\tEnter ROW number (1-3): ");
    scanf("%d", &x);
    
    if (!fits_range(1, 3, x)) {
        return 1;
    }

    printf("\tEnter COLUMN number (1-3): ");
    scanf("%d", &y);

    if (!fits_range(1, 3, y)) {
        return 2;
    }

    if (g->content[x - 1][y - 1] != BLANK_SPACE) {
        return 3;
    }

    destination[0] = x;
    destination[1] = y;

    return 0;
}

/**
 * @brief Get the player input
 * 
 * @param destination into which the player's choices are inserted.
 */
void read_player_input(struct Grid * g, int destination[2]) {
    int result[2] = {0, 0};
    printf("It is %c's turn...\n", get_current_player());

    int x, y;
    while (true) {
        int code = read_player_input0(g, result);
        switch (code) {
            case 1:
                printf("\n\nThat row does not fit into the range 1-3!\n\n\nPlease try again...\n");
                continue;
            case 2:
                printf("\n\nThat column does not fit into the range 1-3!\n\n\nPlease try again...\n");
                continue;
            case 3:
                printf("\n\nThat slot is already full!\n\n\nPlease try again...\n");
                continue;
            default:
                x = result[0];
                y = result[1];
                goto exit_getting_input;
        }
    }

    exit_getting_input:

    printf("\nSubmitting move at (%d, %d) ...\n\n", x, y);

    // to convert the values from human-accesible to array indexes. 
    destination[0] = x - 1;
    destination[1] = y - 1;
}

/**
 * @brief Are the winners the same
 */
bool winner_equality(struct Win * win1, struct Win * win2) {
    return win1->symbol	== win2->symbol;
}

/**
 * @brief Strict equality comparison of two wins (all fields must be the same)
 */
bool strict_win_equality(struct Win * win1, struct Win * win2) {
    return win1->symbol == win2->symbol && win1->code == win2->code;
}

/**
 * @brief Visualize a Win struct in the format "{1} won with code {2}"
 */
char * win_to_string(struct Win * win) {
    static char result[127];
    snprintf(result, 127, "%c won with code %d", win->symbol, win->code);
    return result;
}

struct Win get_winner(struct Grid * g) {
    char tg[3][3];
    
    memcpy(tg, g->content, sizeof(g->content));

    //Straights
    for (int i = 0; i < 3; i++) {
        if (tg[i][0] == tg[i][1] && tg[i][1] == tg[i][2] && tg[i][1] != BLANK_SPACE) {
            return (struct Win) { .symbol = tg[i][1], .code = HORIZONTAL_WIN };
        }

        if (tg[0][i] == tg[1][i] && tg[1][i] == tg[2][i] && tg[1][i] != BLANK_SPACE) {
            return (struct Win) { .symbol = tg[1][i], .code = VERTICAL_WIN };
        }
    }

    //Diagonals
    if (tg[1][1] != BLANK_SPACE) {
        if (tg[0][0] == tg[1][1] && tg[1][1] == tg[2][2]) {
            return (struct Win) { .symbol = tg[1][1], .code = TL_BR_DIAGONAL_WIN };
        }

        if (tg[2][0] == tg[1][1] && tg[1][1] == tg[0][2]) {
            return (struct Win) { .symbol = tg[1][1], .code = BL_TR_DIAGONAL_WIN };
        }
    }

    // Is the Game still active?
    if (__unit_testing) {
        for (int i = 0; i < 3; i++) {
           for (int j = 0; j < 3; j++) {
                if (tg[i][j] == BLANK_SPACE) {
                    return (struct Win) { .symbol = '\0', .code = STILL_PLAYING };
                }
            }
        }
    } else if (__turn_count < 9) {
        return (struct Win) { .symbol = '\0', .code = STILL_PLAYING };
    }

    return (struct Win) { .symbol = '\0', .code = TIE };
}


void tictactoe(struct Grid * g) {
    init_grid(g);

    printf("Welcome to Tic Tac Toe!\n\n- Here's the grid for you to get started.\n");
    print_grid(g);
    printf("\n");

    struct Win winner;
    while (true) {
        int destination[2];
        read_player_input(g, destination);
        set_grid_at(g, destination[0], destination[1], get_current_player());
        print_grid(g);

        __turn_count++;
        
        winner = get_winner(g);
        if (winner.code != STILL_PLAYING) {
            break;
        }
    }
    
    char winmsg[127];
    const char strsymbol[2] = { winner.symbol, '\0' };
    snprintf(winmsg, 127, "%s wins%s", (winner.code != TIE ? strsymbol : "No one"), (winner.code == TIE ? " (It's a tie)" : ""));

    printf("\nGAME OVER!\n\t- %s\n\n%s\n\n", winmsg, LINE_SEP);
}