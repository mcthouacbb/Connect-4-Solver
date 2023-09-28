#pragma once

#include <cassert>

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