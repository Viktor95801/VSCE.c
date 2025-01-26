#include "bitboard.h"
#include <stdio.h>

uint64_t set_bit(uint64_t bb, int square) {
    return bb | (1ULL << square);
}
uint64_t clear_bit(uint64_t bb, int square) {
    return bb & ~(1ULL << square);
}
bool get_bit(uint64_t bb, int square) {
    return bb & (1ULL << (square));
}
#include "bitboard.h"
#include <stdio.h>

void print_board(const Board *board) {
    char piece_symbols[] = "PRNBQKprnbqk."; // Piece symbols + empty square

    for (int rank = 7; rank >= 0; --rank) {
        printf("%d ", rank + 1); // Print rank number at the beginning of the line

        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            char piece = piece_symbols[12]; // Initialize to empty square '.'

            for (int piece_type = 0; piece_type < 6; ++piece_type) {
                if (get_bit(board->i_B[piece_type], square)) {  //Check each piece type using the array
                   piece = piece_symbols[piece_type + (board->B.pawns != board->i_B[piece_type] ? 6:0)]; //adjust the index of pices_symbol for correct char
                    break; //piece assigned, exit the inner loop
                }
            }

            printf("%c ", piece);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}


void init_board_white(Board *board) {
    // pawns
    for (int file = A2; file < H2; file++) {
        board->B.pawns = set_bit(board->B.pawns, file);
    }
    // rooks
    board->B.rooks = set_bit(board->B.rooks, A1);
    board->B.rooks = set_bit(board->B.rooks, H1);
    // knights
    board->B.knights = set_bit(board->B.knights, B1);
    board->B.knights = set_bit(board->B.knights, G1);
    // bishops
    board->B.bishops = set_bit(board->B.bishops, C1);
    board->B.bishops = set_bit(board->B.bishops, F1);
    // queen
    board->B.queen = set_bit(board->B.queen, D1);
    // king
    board->B.king = set_bit(board->B.king, E1);
}
void init_board_black(Board *board) {
    // pawns
    for (int file = A7; file < H7; file++) {
        board->B.pawns = set_bit(board->B.pawns, file);
    }
    // rooks
    board->B.rooks = set_bit(board->B.rooks, A8);
    board->B.rooks = set_bit(board->B.rooks, H8);
    // knights
    board->B.knights = set_bit(board->B.knights, B8);
    board->B.knights = set_bit(board->B.knights, G8);
    // bishops
    board->B.bishops = set_bit(board->B.bishops, C8);
    board->B.bishops = set_bit(board->B.bishops, F8);
    // queen
    board->B.queen = set_bit(board->B.queen, D8);
    // king
    board->B.king = set_bit(board->B.king, E8);
}