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
};

constexpr Move MOVE_NULL = Move();

constexpr int sqColumn(int sq)
{
    return sq / 8;
}

constexpr int sqRow(int sq)
{
    return sq % 8;
}