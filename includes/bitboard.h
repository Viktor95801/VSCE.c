#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
// Square indices (0-63)
enum {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

typedef union {
    struct {
        uint64_t pawns;
        uint64_t rooks;
        uint64_t knights;
        uint64_t bishops;
        uint64_t queen;
        uint64_t king;
    } B;
    uint64_t i_B[6];
} Board;
void print_board(const Board *board);

uint64_t set_bit(uint64_t bb, int square);
uint64_t clear_bit(uint64_t bb, int square);
bool get_bit(uint64_t bb, int square);

void init_board_white(Board *board);
void init_board_black(Board *board);

#endif