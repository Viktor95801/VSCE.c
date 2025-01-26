#include <stdio.h>
#include <assert.h>
#include "bitboard.h"

int main() {
    Board board;
    init_board_white(&board);
    init_board_black(&board);
    print_board(&board);

    return 0;
}