#include "bitboard.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// const

const char piece_symbols[] = "PpRrHhBbQqKk";

// helper

char char_from_square(const Board *b, int sq)
{
    for (int i = 0; i < 12; i++)
    {
        if (get_bit(&b->iter[i], sq))
        {
            return piece_symbols[i];
        }
    }
    return '.';
}


/**
 * Converts a character to a piece structure.
 *
 * The following characters are recognized and their corresponding piece
 * structure is returned.
 *
 * - 'P': PAWN
 * - 'R': ROOK
 * - 'H': HORSE
 * - 'B': BISHOP
 * - 'Q': QUEEN
 * - 'K': KING
 *
 * If the character is 'a' to 'z', the same piece structure is returned
 * as if the character was uppercase, but with the color set to BLACK.
 *
 * If the character is '.', a special piece structure is returned with
 * type -2, color -2, and square -1.
 *
 * If the character is not recognized, a special piece structure is
 * returned with type -1, color -1, and square -1.
 */
struct piece piece_from_char(char c)
{
    struct piece out = {0, 0, -1};
    if (c == '.') {
        return (struct piece){-2, -2, -1};
    }
    if (c >= 'a' && c <= 'z') {
        c += 'A' - 'a';
        out.color = BLACK;
    }
    switch (c)
    {
        case 'P':
            out.type = PAWN;
            break;
        case 'R':
            out.type = ROOK;
            break;
        case 'N':
            out.type = HORSE;
            break;
        case 'B':
            out.type = BISHOP;
            break;
        case 'Q':
            out.type = QUEEN;
            break;
        case 'K':
            out.type = KING;
            break;
        default:
            return (struct piece){-1, -1, -1};
            break;
    }

    return out;
}

void load_piece_on_board(struct piece p, Board* b) {
    VSCE_ASSERT(p.type != -1) {
        fprintf(stderr, "Invalid piece type: %d\n", p.type);
    }
    if (p.type == -2) {
        return;
    }
    set_bit(&b->iter[p.type + p.color], p.square);
}

// impl

void print_board(const Board *b)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        printf("%c | ", '1' + rank);
        for (int file = 0; file < 8; file++)
        {
            printf("%c ", char_from_square(b, rank * 8 + file));
        }
        printf("\n");
    }
    printf("  -----------------\n    A B C D E F G H\n");
}

void print_bitboard(const u64 *bitboard)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        printf("%c ", '1' + rank);
        for (int file = 0; file < 8; file++)
        {
            printf("%lld ", (*bitboard >> (rank * 8 + file)) & 1);
        }
        printf("\n");
    }
    printf("  A B C D E F G H\n");
}

void initFEN_board(Board *b, const char *FEN)
{
    // example: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    *b = (Board){0};

    int rank = 7;
    int file = 0;

    char c;
    while ((c = *FEN++) != ' ') {
        if (c == '/') {
            rank--;
            file = 0;
            continue;
        } else if (c >= '0' && c <= '9') {
            file += c - '0';
            continue;
        } else {
            int sq = rank * 8 + file;
            struct piece p = piece_from_char(c);
            VSCE_ASSERT(p.type != -1 || p.type != -2) {
                fprintf(stderr, "Invalid character on FEN string: %c\n", c);
            }
            p.square = sq;
            printf("%c -> %d %d %d\n", c, p.type, p.color, p.square);
            load_piece_on_board(p, b);
            file++;
            continue;
        }
    }
}
void init_board(Board *board)
{
    memset(board, 0, sizeof(*board));
    for (int i = 8; i < 16; i++)
    {
        set_bit(&(board->data.pawn[WHITE]), i);
    }
    for (int i = 48; i < 56; i++)
    {
        set_bit(&(board->data.pawn[BLACK]), i);
    }

    set_bit(&(board->data.rook[WHITE]), A1);
    set_bit(&(board->data.rook[WHITE]), H1);
    set_bit(&(board->data.horse[WHITE]), B1);
    set_bit(&(board->data.horse[WHITE]), G1);
    set_bit(&(board->data.bishop[WHITE]), C1);
    set_bit(&(board->data.bishop[WHITE]), F1);
    set_bit(&(board->data.queen[WHITE]), D1);
    set_bit(&(board->data.king[WHITE]), E1);

    set_bit(&(board->data.rook[BLACK]), A8);
    set_bit(&(board->data.rook[BLACK]), H8);
    set_bit(&(board->data.horse[BLACK]), B8);
    set_bit(&(board->data.horse[BLACK]), G8);
    set_bit(&(board->data.bishop[BLACK]), C8);
    set_bit(&(board->data.bishop[BLACK]), F8);
    set_bit(&(board->data.queen[BLACK]), D8);
    set_bit(&(board->data.king[BLACK]), E8);
}

// masks

u64 make_rook_mask(u64 sq)
{
    u64 original_sq = sq;
    u64 mask = 0;
    for (int i = 0; i < 8; i++)
    {
        sq = shiftWest(sq);
        mask |= sq;
    }
    sq = original_sq;
    for (int i = 0; i < 8; i++)
    {
        sq = shiftEast(sq);
        mask |= sq;
    }
    sq = original_sq;
    for (int i = 0; i < 8; i++)
    {
        sq = shiftNorth(sq);
        mask |= sq;
    }
    sq = original_sq;
    for (int i = 0; i < 8; i++)
    {
        sq = shiftSouth(sq);
        mask |= sq;
    }
    return mask;
}

u64 make_bishop_mask(u64 sq)
{
    u64 original_sq = sq;
    u64 mask = 0;
    for (int i = 0; i < 8; i++)
    {
        sq = shiftNorthwest(sq);
        mask |= sq;
    }
    sq = original_sq;
    for (int i = 0; i < 8; i++)
    {
        sq = shiftSoutheast(sq);
        mask |= sq;
    }
    sq = original_sq;    
    for (int i = 0; i < 8; i++)
    {
        sq = shiftNortheast(sq);
        mask |= sq;
    }
    sq = original_sq;    
    for (int i = 0; i < 8; i++)
    {
        sq = shiftSouthwest(sq);
        mask |= sq;
    }
    return mask;
}

u64 make_queen_mask(u64 sq)
{
    return make_rook_mask(sq) | make_bishop_mask(sq);
}

u64 make_horse_mask(u64 sq)
{
    u64 diagonals[4] = {
        shiftNorthwest(sq),
        shiftNortheast(sq),
        shiftSouthwest(sq),
        shiftSoutheast(sq)
    };
    return shiftWest(diagonals[0]) | shiftNorth(diagonals[0])
        | shiftEast(diagonals[1]) | shiftNorth(diagonals[1])
        | shiftWest(diagonals[2]) | shiftSouth(diagonals[2])
        | shiftEast(diagonals[3]) | shiftSouth(diagonals[3]);
}

u64 make_king_mask(u64 sq)
{
    return shiftNorth(sq) | shiftSouth(sq) | shiftWest(sq) | shiftEast(sq)
        | shiftNorthwest(sq) | shiftNortheast(sq) | shiftSouthwest(sq) | shiftSoutheast(sq);
}
