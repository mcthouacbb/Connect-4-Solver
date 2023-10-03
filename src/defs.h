#pragma once

#include <cassert>
#include <cstdint>
#include "bitboard.h"

enum class Color
{
    RED,
    YELLOW
};

constexpr Color flip(Color c)
{
    return static_cast<Color>(static_cast<int>(c) ^ 1);
}

struct Move
{
    uint16_t sqIdx;
    Move() = default;
    Move(uint16_t sqIdx);

    constexpr bool operator==(const Move& other) const = default;
    constexpr bool operator!=(const Move& other) const = default;
};

inline Move::Move(uint16_t sqIdx)
    : sqIdx(sqIdx)
{
    assert(sqIdx < 64 && ((1ull << sqIdx) & IN_BOARD));
}

constexpr Move MOVE_NULL = Move();

constexpr int sqColumn(int sq)
{
    return sq / 8;
}

constexpr int sqRow(int sq)
{
    return sq % 8;
}

constexpr int SCORE_WIN = 1000;
constexpr int SCORE_NONE = 1001;
constexpr bool isWinScore(int score)
{
    return SCORE_WIN - (score < 0 ? -score : score) < 50;
}
