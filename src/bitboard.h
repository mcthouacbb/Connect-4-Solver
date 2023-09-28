#pragma once

#include <cstdint>
#include <bit>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

using Bitboard = uint64_t;

constexpr Bitboard BOTTOM_ROW = 0x40810204081ull;

inline uint32_t getLSB(Bitboard bb)
{
#if defined(__GNUC__) || __has_builtin(__builtin_ctzll)
	return __builtin_ctzll(bb);
#elif defined(_MSC_VER)
	unsigned long idx;
	_BitScanForward64(&idx, bb);
	return idx;
#else
    return std::countr_zero(bb);
#endif
}

inline uint32_t getMSB(Bitboard bb)
{
#if defined(__GNUC__) || __has_builtin(__builtin_clzll)
	return 63 - __builtin_clzll(bb);
#elif defined(_MSC_VER)
	unsigned long idx;
	_BitScanReverse64(&idx, bb);
	return idx;
#else
    return 63 - std::countl_zero(bb);
#endif
}

inline uint32_t popLSB(Bitboard& bb)
{
    uint32_t lsb = getLSB(bb);
    bb &= bb - 1;
    return lsb;
}

inline uint32_t popcount(Bitboard bb)
{
    return std::popcount(bb);
}
