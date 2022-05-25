#pragma once

#include <stdbool.h>
#include <stdlib.h>

#ifndef TIC_TAC_TOE_H
    #define TIC_TAC_TOE_H

    // Game End Codes
    #ifndef STILL_PLAYING
        #define STILL_PLAYING      -1
    #endif
    #ifndef TIE
        #define TIE                 0
    #endif
    #ifndef HORIZONTAL_WIN
        #define HORIZONTAL_WIN      1
    #endif
    #ifndef VERTICAL_WIN
        #define VERTICAL_WIN        2
    #endif
    #ifndef BL_TR_DIAGONAL_WIN
        #define BL_TR_DIAGONAL_WIN  3
    #endif
    #ifndef TL_BR_DIAGONAL_WIN
        #define TL_BR_DIAGONAL_WIN  4
    #endif

    // Grid Constants
    #ifndef PLAYER_X
        #define PLAYER_X           'X'
    #endif
    #ifndef PLAYER_O    
        #define PLAYER_O           'O'
    #endif
    #ifndef BLANK_SPACE    
        #define BLANK_SPACE        '_'
    #endif    

    // Misc. Constants
    #ifndef EMPTY_GRID
        #define EMPTY_GRID { .content = {                   \
            {BLANK_SPACE, BLANK_SPACE, BLANK_SPACE},        \
            {BLANK_SPACE, BLANK_SPACE, BLANK_SPACE},        \
            {BLANK_SPACE, BLANK_SPACE, BLANK_SPACE}         \
        }}
    #endif
    #ifndef LINE_SEP
        #define LINE_SEP   "---------"
    #endif

    bool is_player(char symbol);
    struct Grid grid_from_string(const char * string, int * return_code);
    struct Grid grid_from_string0(const char * string);
    bool fits_range(int minIncl, int maxIncl, int val);
    void init_grid(struct Grid * g);
    bool is_player(char symbol);
    int set_grid_at(struct Grid * g, int x, int y, char symbol);
    void print_grid(struct Grid * g);
    char get_current_player();
    int read_player_input0(struct Grid * g, int destination[2]);
    void read_player_input(struct Grid * g, int destination[2]);
    bool winner_equality(struct Win * win1, struct Win * win2);
    bool strict_win_equality(struct Win * win1, struct Win * win2);
    char * win_to_string(struct Win * win);
    struct Win get_winner(struct Grid * g);
    void tictactoe(struct Grid * g);
    void test_winner_function();

    
    struct Win {
        char symbol;
        int code;
    };
    
    struct Grid {
        char content[3][3];
    };

    static bool __unit_testing = false;
    static unsigned short __turn_count = 0;
    static struct Grid grid;
#endif