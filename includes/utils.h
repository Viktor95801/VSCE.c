#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdint.h>

#define VSCE_ASSERT(x) for ( ; !(x) ; assert(x) ) 
#define u64 uint64_t

#define A_FILE            0x0101010101010101
#define H_FILE            0x8080808080808080
#define FIRST_RANK        0x00000000000000FF
#define EIGHTH_RANK       0xFF00000000000000
#define A1H8_DIAGONAL     0x8040201008040201
#define H1A8_ANTIDIAGONAL 0x0102040810204080
#define LIGHT_SQUARES     0x55AA55AA55AA55AA
#define DARK_SQUARES      0xAA55AA55AA55AA55

// helper methods
static inline u64 shiftEast(u64 b)      {return (b << 1) & ~A_FILE;}
static inline u64 shiftNortheast(u64 b) {return (b << 9) & ~A_FILE;}
static inline u64 shiftSoutheast(u64 b) {return (b >> 7) & ~A_FILE;}
static inline u64 shiftWest(u64 b)      {return (b >> 1) & ~H_FILE;}
static inline u64 shiftSouthwest(u64 b) {return (b >> 9) & ~H_FILE;}
static inline u64 shiftNorthwest(u64 b) {return (b << 7) & ~H_FILE;}

static inline u64 shiftNorth(u64 b)     {return (b << 8);}
static inline u64 shiftSouth(u64 b)     {return (b >> 8);}

#endif // CONSTANT_H