#include <stdio.h>
#include <assert.h>
#include "bitboard.h"

int main() {
    Board board;
    init_board(&board);

    u64 ronk_mask = make_rook_mask(bb_from_square(E2));
    print_bitboard(&ronk_mask);
    u64 bishop_mask = make_bishop_mask(bb_from_square(E2));
    print_bitboard(&bishop_mask);
    u64 queen_mask = make_queen_mask(bb_from_square(E2));
    print_bitboard(&queen_mask);
    u64 knight_mask = make_horse_mask(bb_from_square(E2));
    print_bitboard(&knight_mask);

    Board test_fen;
    initFEN_board(&test_fen, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    print_board(&test_fen);
    return 0;
}