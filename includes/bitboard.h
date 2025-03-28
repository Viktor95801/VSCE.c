#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdbool.h>
#include <stdint.h>
#include "utils.h"

#define u64 uint64_t

enum piece_index
{
    PAWN,
    ROOK,
    HORSE,
    BISHOP,
    QUEEN,
    KING,

    WHITE = 0,
    BLACK = 1,

    BOARD_LEN = 12,
};

// Square indices (0-63)
enum square_index
{
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

typedef union Board
{
    struct {
        u64 pawn[2]; // typ 0 + BLACK = 1
        u64 rook[2]; // 1
        u64 horse[2]; // 2
        u64 bishop[2]; // 3
        u64 queen[2]; // 4
        u64 king[2]; // 5
    } data;
    u64 iter[12];
} Board;

struct piece {
    int type;
    bool color;
    int square;
};

// helper methods

static inline u64 bb_from_square(int sq) { return 1ULL << sq; }

static inline void set_bit(u64 *bb, int sq) { *bb |= (1ULL << sq); }
static inline bool get_bit(const u64 *bb, int sq) { return *bb & (1ULL << sq); }
static inline void clear_bit(u64 *bb, int sq) { *bb &= ~(1ULL << sq); }
static inline bool pop_bit(u64 *bb, int sq)
{
    bool val = get_bit(bb, sq);
    clear_bit(bb, sq);
    return val;
}

extern const char piece_symbols[12]; // "PpRrHhBbQqKk"
char char_from_square(const Board *board, int square);

struct piece piece_from_char(char c);
void load_piece_on_board(struct piece piece, Board* board);

// functions

void init_board(Board *board);
void initFEN_board(Board *board, const char *FEN);

void print_board(const Board *board);
void print_bitboard(const u64 *bitboard);

// masks

u64 make_rook_mask(u64 sq);
u64 make_bishop_mask(u64 sq);
u64 make_queen_mask(u64 sq);
u64 make_horse_mask(u64 sq);
u64 make_king_mask(u64 sq);

#endif