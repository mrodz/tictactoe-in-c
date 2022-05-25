#include <C:\Users\mateo\Documents\Coding Projects\Languages\C\tictactoe\tictactoe.h>

/**
 * @brief Unit Testing for the `get_winner(Grid *)` function
 */
void test_winner_function() {
    __unit_testing = true;

    struct TestPair {
        struct Grid grid;
        struct Win expected_win;
    };

    struct TestPair test_pairs[] = { 
        { .grid = grid_from_string0("X___X___X"), .expected_win = { .symbol = 'X', .code = TL_BR_DIAGONAL_WIN } },
        { .grid = grid_from_string0("O___O___O"), .expected_win = { .symbol = 'O', .code = TL_BR_DIAGONAL_WIN } },
        { .grid = grid_from_string0("_________"), .expected_win = { .symbol = '\0', .code = STILL_PLAYING } },
        { .grid = grid_from_string0("XOOOXXXXO"), .expected_win = { .symbol = '\0', .code = TIE } },
        { .grid = grid_from_string0("O_X_XOXOX"), .expected_win = { .symbol = 'X', .code = BL_TR_DIAGONAL_WIN } }
    };

    unsigned short test_count = sizeof(test_pairs) / sizeof(struct TestPair);
    unsigned short passes = 0, fails = 0;

    printf("$ Commencing Unit Tests...\n");

    for (int i = 0; i < test_count; i++) {
        struct TestPair this_pair = test_pairs[i];
        struct Win calcualted = get_winner(&(test_pairs[i].grid));

        bool success = strict_win_equality(&this_pair.expected_win, &calcualted);

        if (success) {
            passes++;
        } else {
            fails++;
        }

        printf("\tTest #%i :: %s :: { expected winner '%c', found '%c' with game code %i }\n", i + 1, 
                (success ? "PASS" : "FAIL"),
                this_pair.expected_win.symbol, 
                calcualted.symbol,
                calcualted.code);
    }

    printf("\n$ RESULTS:\n\t- %ix Passes\n\t- %ix Fails\n", passes, fails);
    __unit_testing = false;
}